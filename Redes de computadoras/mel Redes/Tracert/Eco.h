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

typedef struct estadistica{
	int enviados;
	int recibidos;
	float maximo;
	float minimo;
	float total;
}Estadistica;

void armaICMP(ICMP *,int *);
void armaIP(ENCIP *,Datos,Datos,int);
void armaENCMAC(ENCMAC *,Datos,Datos);
void ChecksumICMP(ICMP *);
void ChecksumENCIP(ENCIP *);
void estadisticas();
int ICMP_ECO(Datos,Datos,IP*,int,int,float*);

int ICMP_ECO(Datos misDatos,Datos destDatos,IP *IPOrigen,int TTL,int secuencia,float *latencia){

	ICMP encICMP,recvICMP,recv_timeoutICMP;
	ENCIP encaIP,recvIP;
	ENCMAC encaMAC,recvMAC;
	TRAMA PING,recvTRAMA;
	int num_sec = secuencia;

	/*Solo para comparar*/ 
	int pid = (int)getpid();
	unsigned char resp_eco = 0x00,identi[2],numsec[2];
	memcpy(identi,&pid,2);
	/*Solo para comparar*/

	memset(&PING,0x00,sizeof(PING));
	memset(&recv_timeoutICMP,0x00,sizeof(ICMP));
	memset(&encICMP,0x00,sizeof(ICMP));
	memset(&encaIP,0x00,sizeof(ENCIP));
	memset(&encaMAC,0x00,sizeof(ENCMAC));

    int bytesrecv;
    tiempo tiempo1,tiempo2;
  	memset(&tiempo1,0x00,sizeof(tiempo1));
 	memset(&tiempo2,0x00,sizeof(tiempo1));


    //Armando encabezado MAC
    armaENCMAC(&encaMAC,misDatos,destDatos);
    memcpy(PING,&encaMAC,14);

    //Armando encabezado IP
    armaIP(&encaIP,misDatos,destDatos,TTL);
    memcpy(PING + 14,&encaIP,20);

    //printf("Haciendo ping a [] con 32 bytes de datos: \n\n");

    //Armando encabezado ICMP
    armaICMP(&encICMP,&num_sec);
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

    		memcpy(IPOrigen,recvIP.origen,IPLEN);	
        	*latencia = obtentiempo(tiempo1,tiempo2);

      		if(recvICMP.tipo == 0x0b && !memcmp(recvIP.destino,encaIP.origen,IPLEN)){

      			//Copiamos el mensaje destruido para ver el id y la secuencia
      			memcpy(&recv_timeoutICMP,recvTRAMA + 62,40);

      			if(!memcmp(recv_timeoutICMP.identificador,encICMP.identificador,2) 
      			&& !memcmp(recv_timeoutICMP.numsecuencia,encICMP.numsecuencia,2)){
      				//Paquete Eliminado
        			//imprimeTRAMA(recvTRAMA,bytesrecv);       		
        			return 0;
      			}
        		
      		}
      		else if(recvICMP.tipo == 0x00
      		&& !memcmp(recvICMP.identificador,encICMP.identificador,2) 
      		&& !memcmp(recvICMP.numsecuencia,encICMP.numsecuencia,2)
      		&& !memcmp(recvIP.origen,encaIP.destino,IPLEN)
      		&& !memcmp(recvIP.destino,encaIP.origen,IPLEN)){

      			//Respuesta de ECO 
      			//imprimeTRAMA(recvTRAMA,bytesrecv); 
        		return 1;
      		}

    	}
  	}
  	if(obtentiempo(tiempo1,tiempo2) >= 1)
  		return 2;
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

void armaIP(ENCIP *encaIP,Datos misDatos,Datos destDatos,int TTL){
	memset(encaIP,0x00,sizeof(ENCIP));
	unsigned char aux;
	int pid = (int)getpid();
	encaIP -> version_encIPLen += 0x40;
	encaIP -> version_encIPLen += 0x05;
	encaIP -> tipoServicio = 0x00;
	encaIP -> datagramaIPLen[1] = 0x3C;
	memcpy(encaIP -> identificador,&pid,2);
	encaIP -> TTL = TTL;
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
	acarreo = suma >> 16;
	suma += acarreo;
	suma = suma & 0x0FFFF;
	suma = complemento - suma;
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
	memcpy(aux,&suma,2);
	encaIP -> checksum[0] = aux[1];
	encaIP -> checksum[1] = aux[0];
}




