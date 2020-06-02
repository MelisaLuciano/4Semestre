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
#include <my_global.h>
#include <mysql.h>
#include "ARP_DB.h"
#include "funciones.h"
#include "ARP.h"

int main(){

	int op = 0;
	char salida = 'S';

    MYSQL *con = mysql_init(NULL);
	if(con == NULL){
      	fprintf(stderr, "%s\n", mysql_error(con));
      	exit(-1);
    }

    creaDB(con);

	while(salida != 'n' && salida != 'N'){
		system("clear");
		printf("\nBienvenido ... Escoge una opcion:\n\n");
		printf("1.- Escanear la Red.\n");
		printf("2.- Ver Registros de ARP.\n");
		printf("3.- Borrar Registros de ARP.\n");
        printf("4.- Poner en marcha el servidor de ARP\n");
		printf("Opcion: ");
		scanf("%d",&op);
		system("clear");

		switch(op){
			case 1:
				escaneoDeRed(con);
				break;
			case 2:
				verRegistros(con);
				break;
			case 3:
				borraDB(con);
				break;
            case 4:
                ARP_server(con);
                break;
			default:
				printf("Opcion no valida.\n");
		}

		printf("\n¿ Desea volver al menu ? S/N ");
		scanf(" %c",&salida);
	}
	mysql_close(con);
	return 0;
}



