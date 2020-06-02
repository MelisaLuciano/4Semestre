#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include "funciones.h"
#include "ARP.h"
#include "Eco.h"
#include "Tracer.h"

int main(int argc, char *argv[]){
	
    char charIP[30],nom_interfaz[20];
	Datos misDatos,destDatos,GATEWAYDatos;
	IP ruta[30],IPOrigen,IPMissed;
    Estadistica t_trace;

    memset(IPMissed,0x00,sizeof(IP));
	memset(&t_trace,0x00,sizeof(Estadistica));
    memset(ruta,0x00,sizeof(ruta));
    memset(&misDatos,0x00,sizeof(misDatos));
    memset(&destDatos,0x00,sizeof(destDatos));

	/*Copiamos la IP que nos pasaron desde la consola y la convertimos*/
	strcpy(charIP,argv[1]);
	IP_aton(charIP,destDatos.miIP);

	misDatos.packet_socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

  	if(misDatos.packet_socket == -1){
    	perror("Error al abrir el socket.\n");
    	return -1;
    }
    else{
    	printf("Exito al abrir el socket.\n");

      	if (fcntl(misDatos.packet_socket, F_SETFL, O_NONBLOCK) == -1){
        	perror("Socket no se puede poner en modo no bloqueante.");
        	return -1;
      	}

    	printf("Da el nombre de la interfaz: ");
    	scanf(" %s",nom_interfaz);
    	strcpy(misDatos.nom_interfaz,nom_interfaz);

    	if(obtenParametros(&misDatos) == -1)
    		return -1;

        imprimeIP(misDatos.miGATEWAY);

    	//Preguntamos por la MAC de la GATEWAY
    	memcpy(GATEWAYDatos.miIP,misDatos.miGATEWAY,GATEWAYLEN);
    	ARP(&misDatos,&GATEWAYDatos);

    	//Checamos si la ip introducida esta en nuestra red, si si preguntamos su MAC, sino usamos la GATEWAY
    	if(((misDatos.miNETMASK[0] & misDatos.miIP[0]) == (misDatos.miNETMASK[0] & destDatos.miIP[0])) &&
    		((misDatos.miNETMASK[1] & misDatos.miIP[1]) == (misDatos.miNETMASK[1] & destDatos.miIP[1])) &&
    		((misDatos.miNETMASK[2] & misDatos.miIP[2]) == (misDatos.miNETMASK[2] & destDatos.miIP[2])))
    		ARP(&misDatos,&destDatos);
    	else
    		memcpy(destDatos.miMAC,GATEWAYDatos.miMAC,MACLEN);

        int nodos = Tracer(misDatos,destDatos,ruta,&t_trace,0);
        int i,j,retorno,secuencia = 0,recibidos_min[30],recibidos_max[30];
        float tiempi;

        memset(recibidos_max,0x00,sizeof(int)*30);
        memset(recibidos_min,0x00,sizeof(int)*30);

        //sleep(3);
        printf("\nComenzando barridos a la correspondiente traza ...\n");

        for(j = 0;j < 100;j++){
            for(i = 0;i < nodos; i++){
                usleep(10000);
                secuencia++;
                if(memcmp(ruta[i],IPMissed,IPLEN)){
                    memcpy(destDatos.miIP,ruta[i],IPLEN);
                    retorno = ICMP_ECO(misDatos,destDatos,&IPOrigen,i + 1,secuencia,&tiempi);
                    if(retorno == 1)
                        recibidos_min[i] += 1;
                }
            }
        }
        printf("Barrido con TTL minimo terminado.\n");
        //sleep(3);

        secuencia = 0;
        for(j = 0;j < 100;j++){
            for(i = 0;i < nodos; i++){
                usleep(10000);
                secuencia++;
                if(memcmp(ruta[i],IPMissed,IPLEN)){
                    memcpy(destDatos.miIP,ruta[i],IPLEN);
                    retorno = ICMP_ECO(misDatos,destDatos,&IPOrigen,255,secuencia,&tiempi);
                    if(retorno == 1)
                        recibidos_max[i] += 1;
                }
            }
        }
        printf("Barrido con TTL maximo terminado.\n\n");

        printf("Estadisticas ...\n");
        printf("Salto \t\t IP \t\t TTL MIN    TTL MAX \n\n");
        for (i = 0; i < nodos; ++i){
            printf("%d \t ",i + 1);
            if(memcmp(ruta[i],IPMissed,IPLEN)){
                imprimeIP(ruta[i]);
                printf("       \t (%d/100) \t (%d/100) \n",recibidos_min[i],recibidos_max[i]);
            }
            else{
                printf("-- \t         \t -- \t -- \n");
            }
        }
        printf("\n");
	}
    close(misDatos.packet_socket);
	return 0;
}
