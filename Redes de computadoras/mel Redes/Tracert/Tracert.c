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

/*MODIFICAR PING DE MANERA QUE FUNCIONE PASANDOLE COMO PARAMETRO DATOS *MISDATOS , DATOS *DESTDATOS COMO EL ARP
Y TAMBIEN MODIFCAR DE MANERA QUE LAS Estadisticas FUNCIONEN CON LA NUEVA ESTRUCTURA ESTADISTICA.*/

int enviados = 0,recibidos = 0;
float total = 0,maximo = 0,minimo = 0;

void estadisticas();

int main(int argc, char *argv[]){

	//signal(SIGINT, estadisticas);

	char charIP[30],nom_interfaz[20];
	Datos misDatos,destDatos,GATEWAYDatos;
	IP ruta[30],IPOrigen,IPGuardada;

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

    	int i = 0,j = 0,flag = 0,secuencia = 0,retorno,recibidos = 0,enviados = 0,perdidos = 0,guardada = 0;
        float tiempi,t_total = 0,t_max,t_min,t_medio,p_lost,p_recived;

		system("clear");
        printf("\nTraza para [");
        imprimeIP(destDatos.miIP);
        printf("] con un maximo de 30 saltos ... \n\n");

        printf("Salto \t Tiempo1 \t Tiempo2 \t Tiempo3 \t IP \t\n\n");

        for(i = 1; i <= 30 && flag == 0 ; i++){
            printf("%d.-",i);
    		for(j = 1;j < 4; j++){
    			//Manda mensaje de eco int ICMP_ECO(misDatos,destDatos,TTL,id,secuencia,tiempo) retorna 
    			//0 si fue por respuesta de paquete eliminado, 1 si fue respuesta del destino,2 si fue tiempo excedido
    			secuencia ++;
                retorno = ICMP_ECO(misDatos,destDatos,&IPOrigen,i,secuencia,&tiempi);
                switch(retorno){
    				case 0:
    					//Paquete eliminado
    					printf("\t %0.2f ms",tiempi*1000);
                        recibidos++;
                        t_total += tiempi;
                        if(guardada == 0){
                            memcpy(IPGuardada,IPOrigen,IPLEN);
                            guardada = 1;
                        } 
    					break;
    				case 1:
    					//Respuesta del destino
    					printf("\t %0.2f ms",tiempi*1000);
                        recibidos++;
                        t_total += tiempi; 
                        flag = 1;
                        if(guardada == 0){
                            memcpy(IPGuardada,IPOrigen,IPLEN);
                            guardada = 1;
                        }
    					break;
    				case 2:
    					//Tiempo excedido
    					printf("\t\t*");
                        perdidos++;
    					break;
    				default:
    					printf("DESCONOCIDO\n");
    			}

                if (recibidos == 1 && retorno != 2)
                    t_min = t_max = tiempi;
                else if(retorno != 2){
                    if(tiempi > t_max)
                        t_max = tiempi;
                    if(tiempi < t_min)
                        t_min = tiempi;
                }
    		}

            if(retorno != 2 || guardada == 1){
                printf("\t[");
                imprimeIP(IPGuardada);
                printf("]\n");
                memcpy(ruta[i],IPGuardada,IPLEN);
                guardada = 0;
            }else
                printf("\n");
		}

		if(flag != 1){
			printf("No se puede llegar al host con 30 saltos\n");
		}
		else{
            enviados = recibidos + perdidos;
            p_lost = (((float)perdidos)/((float)enviados))*100;
            p_recived = (((float)recibidos)/((float)enviados))*100;
            t_medio = t_total/((float)recibidos);

            printf("\nEstadisticas ...\n\n");
            printf("Enviados =       %d\n",enviados);
            printf("Recibidos =      %d (%0.2f %%)\n",recibidos,p_recived);
            printf("Perdidos =       %d (%0.2f %%)\n",perdidos,p_lost);
            printf("Tiempo Maximo =  %0.2f ms\n",t_max*1000);
            printf("Tiempo Minimo =  %0.2f ms\n",t_min*1000);
			printf("Tiempo Medio =   %0.2f ms\n",t_medio*1000);
		}
    }

	return 0;
}

void estadisticas(){
	printf("\n\n");
	printf("Estadisticas de ping: \n");
	printf("	Paquetes: enviados = %d recibidos = %d perdidos = %d\n",enviados, recibidos, enviados - recibidos);
	printf("	(%.2f %% perdidos)\n",(float)(((enviados - recibidos) / enviados) * 100));
	printf("Tiempos aproximados de ida y vuelta en milisegundos: \n");
	printf("	Maximo = %.2f Minimo = %.2f Promedio = %.2f\n",maximo * 1000,minimo *1000,(total/enviados) * 1000);
	printf("\n");
	exit(0);
}