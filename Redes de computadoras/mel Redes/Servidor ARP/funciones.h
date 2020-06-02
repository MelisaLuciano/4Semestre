/*DECLARACION DE CONSTANTES*/
#define IPLEN 4
#define MACLEN 6
#define NETMASKLEN 6
#define ETHTYPELEN 2
#define HEADMACLEN 14
/*FIN DECLARACION DE CONSTANTES*/

/* DECLARACION DE TIPOS DE DATOS */
typedef unsigned char NETMASK[6];
typedef unsigned char MAC[6];
typedef unsigned char IP[4];
typedef unsigned char ETHTYPE[2];
typedef unsigned char TRAMA[1514];

/*
typedef unsigned char SOLARP[2];//Solicitud ARP
typedef unsigned char RESPARP[2];//Respuesta ARP*/

typedef struct datos{
  int packet_socket;
  char nom_interfaz[10];
  int indice;
  struct ifreq interface;
  MAC miMAC;
  IP miIP;
  NETMASK miNETMASK;
} Datos;
/* FIN DECLARACION DE TIPOS DE DATOS */

/*PROTOTIPOS DE FUNCIONES */
//int obtenParametros(int,char*,struct ifreq*,int*,MAC,IP,NETMASK);
int obtenParametros(Datos*);
void obtenIndice(int,struct ifreq*,char*,int*);
void obtenMAC(int,struct ifreq*,MAC);
void obtenIP(int,struct ifreq*,IP);
void obtenNETMASK(int,struct ifreq*,NETMASK);
void creaTRAMA(MAC,MAC,ETHTYPE,char*,int,TRAMA);
void enviaTRAMA(int,TRAMA,int,int);
int recibeTRAMA(int,TRAMA);
void imprimeMAC(MAC);
void imprimeIP(IP);
void imprimeNETMASK(NETMASK);
void imprimeTRAMA(TRAMA,int);
void IP_aton(char*,IP);
void IP_ntoa(IP,char*);
void MAC_ntoa(MAC,char*);
void MAC_aton(char*,MAC);
void imprimeDatos(Datos );
/*FIN PROTOTIPOS DE FUNCIONES */

/*IMPLEMENTACION DE FUNCIONES*/
int obtenParametros(Datos *misDatos){

    strcpy(misDatos->interface.ifr_name,misDatos->nom_interfaz);

    obtenIndice(misDatos->packet_socket,&(misDatos->interface),misDatos->nom_interfaz,&(misDatos->indice));
    if(misDatos->indice == -1)
      return -1;

    obtenMAC(misDatos->packet_socket,&(misDatos->interface),misDatos->miMAC);
    if(misDatos->miMAC == NULL)
      return -1;
  
    obtenIP(misDatos->packet_socket,&(misDatos->interface),misDatos->miIP);
    if(misDatos->miIP == NULL)
      return -1;

    obtenNETMASK(misDatos->packet_socket,&(misDatos->interface),misDatos->miNETMASK);
    if(misDatos->miNETMASK == NULL)
      return -1;

    return 0;
}

void obtenIndice(int packet_socket,struct ifreq *interface,char *nom_interfaz,int *indice){  
  if(ioctl(packet_socket,SIOCGIFINDEX,interface) == -1){
    perror("Error al obtener el indice: ");
    *indice = -1;
  }else
    *indice = interface->ifr_ifindex;
}

void obtenMAC(int packet_socket,struct ifreq *interface,MAC miMAC){
  if (ioctl(packet_socket,SIOCGIFHWADDR,interface) == -1){
    perror("Error al obtener la MAC Adress: ");
    miMAC = NULL;
  }else
    memcpy(miMAC,interface->ifr_hwaddr.sa_data,MACLEN);
}

void obtenIP(int packet_socket,struct ifreq *interface,IP miIP){
  struct sockaddr_in sa;
  char str[INET_ADDRSTRLEN];
  if (ioctl(packet_socket,SIOCGIFADDR,interface) == -1){
        perror("Error al obtener la IP Adress: ");
        miIP = NULL;
  }else
    memcpy(miIP, interface->ifr_addr.sa_data + 2, IPLEN);
}

void obtenNETMASK(int packet_socket,struct ifreq *interface,NETMASK miNETMASK){
  if (ioctl(packet_socket,SIOCGIFNETMASK,interface) == -1) {
    perror("\nError al obtener la mascara de subred\n");
    miNETMASK = NULL;
  } else 
    memcpy(miNETMASK,interface->ifr_netmask.sa_data,NETMASKLEN);
}

void creaTRAMA(MAC destino,MAC origen,ETHTYPE miETHERTYPE,char *Datos,int tam,TRAMA miTrama){
  /*Encabezado MAC*/
	memcpy(miTrama,destino,MACLEN);
	memcpy(miTrama + MACLEN,origen,MACLEN);
	memcpy(miTrama + MACLEN + MACLEN,miETHERTYPE,ETHTYPELEN);
	/*DATOS*/
	if(tam > 1501)
		printf("ERROR: Mensaje demasiado grande.\n");
	else
		memcpy(miTrama + HEADMACLEN,Datos,tam);
}

void enviaTRAMA(int packet_socket,TRAMA envTRAMA,int tam,int indice){
  	struct sockaddr_ll nic;
  	//Inicializando el struct
 	memset(&nic,0x00,sizeof(nic));
	nic.sll_family = AF_PACKET;
 	nic.sll_protocol = htons(ETH_P_ALL);
  	nic.sll_ifindex = indice;
	if(sendto(packet_socket,envTRAMA,tam,0,(struct sockaddr *)&nic,sizeof(nic)) == -1)
    	perror("Envio Fallido: ");
}

int recibeTRAMA(int packet_socket,TRAMA recvTRAMA){
	//1514 porque es el maximo numero de datos que puedo recibir
	return recvfrom(packet_socket,recvTRAMA,1514,0,NULL,0);
}

void imprimeMAC(MAC imprMAC){
	int i;
  printf("%02x",imprMAC[0]);
    for (i = 1; i < MACLEN; ++i)
      printf(":%02x",imprMAC[i]);
}

void imprimeIP(IP imprIP){
	int i;
	for (i = 0; i < IPLEN; i++) {
		printf("%d",imprIP[i]);
		if (i < 3) 
			printf(".");
	}
}

void imprimeNETMASK(NETMASK imprNETMASK){
	int i;
	//inicia desde 2 porque los primeros 2 bytes
  //no son parte de la NETMASK para corregir
  //buscar el cast correspondiente
	for (i = 2; i < NETMASKLEN; i++) {
		printf("%d",imprNETMASK[i]);
		if (i < 5) 
			printf(".");
	}
}

void imprimeTRAMA(TRAMA imprTRAMA,int tam){
    int i;
    for(i = 0;i < tam;i++){
        if(i % 16 == 0)
            printf("\n");
        printf("%.2x ",imprTRAMA[i]);
    }
    printf("\n***********************************************\n");
}

void IP_aton(char *IPchar,IP bytesIP){
  int i = 0,j = 0,k = 0;
  char temp[4];
  while(IPchar[i] != '\0'){
    while((IPchar[i] != '.')&&(IPchar[i] != '\0')){
      temp[j] = IPchar[i];
      i++;j++;
    }
    temp[j] = '\0';
    bytesIP[k] = atoi(temp);
    i++;k++;
    j = 0;
  }
}

void IP_ntoa(IP bytesIP,char *IPchar){
  int i;
  char temp[4],punto[2] = ".";
  for (i = 0; i < IPLEN; ++i){
    sprintf(temp,"%d",bytesIP[i]);
    strcat(IPchar,temp);
    if(i < 3)
      strcat(IPchar,punto);
  }
}

void MAC_aton(char *MACchar,MAC bytesMAC){
  int i = 0,j = 0,k = 0;
  unsigned int byte;
  char temp[3];
  while(MACchar[i] != '\0'){
    while((MACchar[i] != ':')&&(MACchar[i] != '\0')){
      temp[j] = MACchar[i];
      i++;j++;
    }
    temp[j] = '\0';
    sscanf(temp, "%2x", &byte);
    bytesMAC[k] = byte;
    i++;k++;
    j = 0;
  }
}

void MAC_ntoa(MAC bytesMAC,char *MACchar){
  int i;
  char temp[4],punto[2] = ":";
  for (i = 0; i < MACLEN; ++i){
    sprintf(temp,"%.2x",bytesMAC[i]);
    strcat(MACchar,temp);
    if(i < 5)
      strcat(MACchar,punto);
  }
}

void imprimeDatos(Datos someDatos){
  printf("El nombre de la interfaz es: %s\n",someDatos.nom_interfaz);
  printf("El indice de la interfaz es: %d\n",someDatos.indice);
  printf("La IP es: ");imprimeIP(someDatos.miIP);printf("\n");
  printf("La MAC es: ");imprimeMAC(someDatos.miMAC);printf("\n");
  printf("La NETMASK es: ");imprimeNETMASK(someDatos.miNETMASK);printf("\n");
}
/*FIN IMPLEMENTACION DE FUNCIONES*/
