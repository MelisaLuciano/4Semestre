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
#include  <signal.h>
#include "funciones.h"
#include "ARP.h"

typedef struct icmp{
	unsigned char tipo;
	unsigned char codigo;
	unsigned char checksum[2];
	unsigned char identificador[2];
	unsigned char numsecuencia[2];
	unsigned char datos[32];
}ICMP;

typedef struct encip{
	unsigned char version_encIPLen;
	unsigned char tipoServicio;
	unsigned char datagramaIPLen[2];
	unsigned char identificador[2];
	unsigned char banderas_offset[2];
	unsigned char TTL;
	unsigned char protocol;
	unsigned char checksum[2];
	IP origen;
	IP destino;
}ENCIP;

typedef struct encmac{
	MAC destino;
	MAC origen;
	ETHTYPE ethertype;
}ENCMAC;

void armaICMP(ICMP *,int *);
void armaIP(ENCIP *,Datos,Datos);
void armaENCMAC(ENCMAC *,Datos,Datos);
void ChecksumICMP(ICMP *);
void ChecksumENCIP(ENCIP *);
void estadisticas();

int enviados = 0,recibidos = 0;
float total = 0,maximo = 0,minimo = 0;

int main(int argc, char *argv[]){

	signal(SIGINT, estadisticas);

	char charIP[30],nom_interfaz[20];
	Datos misDatos,destDatos,GATEWAYDatos;
	ICMP encICMP,recvICMP;
	ENCIP encaIP,recvIP;
	ENCMAC encaMAC,recvMAC;
	TRAMA PING,recvTRAMA;

	/*Solo para comparar*/ 
	int pid = (int)getpid();
	unsigned char resp_eco = 0x00,identi[2],numsec[2];
	memcpy(identi,&pid,2);
	/*Solo para comparar*/ 

	memset(&PING,0x00,sizeof(PING));
	
	
	memset(&encICMP,0x00,sizeof(encICMP));
	memset(&misDatos,0x00,sizeof(misDatos));
    memset(&destDatos,0x00,sizeof(destDatos));

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

    	if(((misDatos.miNETMASK[0] & misDatos.miIP[0]) == (misDatos.miNETMASK[0] & destDatos.miIP[0])) &&
    		((misDatos.miNETMASK[1] & misDatos.miIP[1]) == (misDatos.miNETMASK[1] & destDatos.miIP[1])) &&
    		((misDatos.miNETMASK[2] & misDatos.miIP[2]) == (misDatos.miNETMASK[2] & destDatos.miIP[2])))
    		ARP(&misDatos,&destDatos);
    	else
    		memcpy(destDatos.miMAC,GATEWAYDatos.miMAC,MACLEN);

    	
    	int bytesrecv;
    	tiempo tiempo1,tiempo2;
  		memset(&tiempo1,0x00,sizeof(tiempo1));
 		memset(&tiempo2,0x00,sizeof(tiempo1));


    	//Armando encabezado MAC
    	armaENCMAC(&encaMAC,misDatos,destDatos);
    	memcpy(PING,&encaMAC,14);
    	//Armando encabezado IP
    	armaIP(&encaIP,misDatos,destDatos);
    	memcpy(PING + 14,&encaIP,20);

    	system("clear");
    	printf("Haciendo ping a [%s] con 32 bytes de datos: \n\n",charIP);

    	for (enviados = 1; ; ++enviados){
    		//Armando encabezado ICMP
    		armaICMP(&encICMP,&enviados);
    		memcpy(PING + 34,&encICMP,40);
    		//imprimeTRAMA(PING,74);
    		enviaTRAMA(misDatos.packet_socket,PING,74,misDatos.indice);

    		clock_gettime(CLOCK_REALTIME,&tiempo1);
  			while(obtentiempo(tiempo1,tiempo2) < 1){
    			bytesrecv = recibeTRAMA(misDatos.packet_socket,recvTRAMA);
    			clock_gettime(CLOCK_REALTIME,&tiempo2);
    			if( bytesrecv != -1){
    				memcpy(&recvMAC,recvTRAMA,14);
    				memcpy(&recvIP,recvTRAMA + 14,20);
    				memcpy(&recvICMP,recvTRAMA + 34,40);
      				if(recvICMP.tipo == 0x00
      					&& !memcmp(recvICMP.identificador,encICMP.identificador,2) 
      					&& !memcmp(recvICMP.numsecuencia,encICMP.numsecuencia,2)
      					&& !memcmp(recvIP.origen,encaIP.destino,IPLEN)
      					&& !memcmp(recvIP.destino,encaIP.origen,IPLEN)){

        				printf("Respuesta desde %s: bytes = 32 tiempo = %.2f ms TTL = %d\n",charIP,obtentiempo(tiempo1,tiempo2) * 1000,recvIP.TTL);   
        				
        				if(enviados == 1){
        					minimo = maximo = obtentiempo(tiempo1,tiempo2);
        				}else{
        					if(obtentiempo(tiempo1,tiempo2) > maximo)
        						maximo = obtentiempo(tiempo1,tiempo2);
        					if(obtentiempo(tiempo1,tiempo2) < minimo)
        						minimo = obtentiempo(tiempo1,tiempo2);
        				}
        				
        				total += obtentiempo(tiempo1,tiempo2);
        				recibidos++;
        				break;
      				} 
    			}
  			}
  			if(obtentiempo(tiempo1,tiempo2) >= 1)
  				printf("Sin respuesta ...\n");
  			sleep(1);
    	}
    }
	return 0;
}

void armaICMP(ICMP *encICMP,int *numsecuencia){
	memset(encICMP,0x00,sizeof(ICMP));
	int pid = (int)getpid();
	unsigned char datos[33] = "Luis Daniel Alducin AcevedoESCOM";
	encICMP -> tipo = 0x08;
	encICMP -> codigo = 0x00;
	memcpy(encICMP -> identificador,&pid,2);
	memcpy(encICMP -> numsecuencia,numsecuencia,2);
	memcpy(encICMP -> datos,datos,32);
	ChecksumICMP(encICMP);
}

void armaIP(ENCIP *encaIP,Datos misDatos,Datos destDatos){
	memset(encaIP,0x00,sizeof(ENCIP));
	unsigned char aux;
	int pid = (int)getpid();
	encaIP -> version_encIPLen += 0x40;
	encaIP -> version_encIPLen += 0x05;
	encaIP -> tipoServicio = 0x00;
	encaIP -> datagramaIPLen[1] = 0x3C;
	memcpy(encaIP -> identificador,&pid,2);
	encaIP -> TTL = 0x40;
	encaIP -> protocol = 0x01;
	memcpy(encaIP -> origen,misDatos.miIP,IPLEN);
	memcpy(encaIP -> destino,destDatos.miIP,IPLEN);
	ChecksumENCIP(encaIP);
}

void armaENCMAC(ENCMAC *encaMAC,Datos misDatos,Datos destDatos){
	memset(encaMAC,0x00,sizeof(ENCMAC));
	unsigned char eth[2] = {0x08,0x00};
	memcpy(encaMAC -> destino,destDatos.miMAC,MACLEN);
	memcpy(encaMAC -> origen,misDatos.miMAC,MACLEN);
	memcpy(encaMAC -> ethertype,eth,2);
}

void ChecksumICMP(ICMP *encICMP){
	int i;
	unsigned int suma = 0,dato = 0,complemento = 0,acarreo = 0;
	unsigned char datos[40],comp[2] = {0xFF,0xFF},aux[2];
	memcpy(datos,encICMP,40);
	complemento = comp[0];
	complemento = complemento << 8;
	complemento += comp[1];
	for (i = 1; i < 41; ++i){
		if(i%2 == 0){
			dato = datos[i-2];
			dato = dato << 8;
			dato += datos[i-1];
			suma += dato;
		}
	}
	//printf("SUMA %02x\n",suma);
	acarreo = suma >> 16;
	//printf("ACARREO %x\n",acarreo);
	suma += acarreo;
	//printf("S+A %02x\n",suma);
	suma = suma & 0x0FFFF;
	//printf("SUMA %02x\n",suma);
	suma = complemento - suma;
	//printf("SUMA FINAL %02x\n",suma);
	memcpy(aux,&suma,2);
	encICMP -> checksum[0] = aux[1];
	encICMP -> checksum[1] = aux[0];
}

void ChecksumENCIP(ENCIP *encaIP){
	int i;
	unsigned int suma = 0,dato = 0,complemento = 0,acarreo = 0;
	unsigned char datos[40],comp[2] = {0xFF,0xFF},aux[2];
	memcpy(datos,encaIP,40);
	complemento = comp[0];
	complemento = complemento << 8;
	complemento += comp[1];
	for (i = 1; i < 21; ++i){
		if(i%2 == 0){
			dato = datos[i-2];
			dato = dato << 8;
			dato += datos[i-1];
			suma += dato;
		}
	}
	acarreo = suma >> 16;
	suma += acarreo;
	suma = suma & 0x0FFFF;
	suma = complemento - suma;
	//printf("%x\n",suma);
	memcpy(aux,&suma,2);
	encaIP -> checksum[0] = aux[1];
	encaIP -> checksum[1] = aux[0];
}

void estadisticas(){
	printf("\n\n");
	printf("Estadisticas de ping: \n");
	printf("	Paquetes: enviados = %d recibidos = %d perdidos = %d\n",enviados, recibidos, enviados - recibidos);
	//printf("	(%.2f %% perdidos)\n",(float)(((enviados - recibidos) / enviados) * 100));
	printf("Tiempos aproximados de ida y vuelta en milisegundos: \n");
	printf("	Maximo = %.2f Minimo = %.2f Promedio = %.2f\n",maximo * 1000,minimo *1000,(total/enviados) * 1000);
	printf("\n");
	exit(0);
}


