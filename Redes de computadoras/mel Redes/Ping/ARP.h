/*DECLARACION DE CONSTANTES*/
#define HWTPLEN 2
#define PROTPLEN 2
#define OPCODELEN 2
#define MENSAJE_ARPLEN 28
/*FIN DECLARACION DE CONSTANTES*/

/*TIPOS DE DATOS*/
typedef unsigned char HWTP[2];//Hardware Type
typedef unsigned char PROTP[2];//Protocol Type
typedef unsigned char OPCODE[2];//Solicitud (0x0001) o Respuesta(0x0002) de ARP

typedef struct MARP{
  HWTP MHWTP;
  PROTP MPROTP;
  int MMACLEN;
  int MIPLEN;
  OPCODE MOPCODE;
  MAC MAC_O;
  IP IP_O;
  MAC MAC_D;
  IP IP_D;
  unsigned char MSJ_ARP[29];
} M_ARP;

typedef struct timespec tiempo;
/*FIN DE TIPOS DE DATOS*/

/*PROTOTIPOS DE FUNCIONES*/
int ARP(Datos*,Datos*);
void creaMENSAJE_ARP(M_ARP*);
float obtentiempo(tiempo,tiempo);
void obtenDatosARP(TRAMA,M_ARP*);
/*FIN DE PROTOTIPOS DE FUNCIONES*/

/*DECLARACION DE FUNCIONES*/
int ARP(Datos *misDatos,Datos *destDatos){

  int bytesrecv;

  M_ARP MEN_ARP;
  MAC MAC_BC = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},MAC_Default = {0x77,0x77,0x77,0x77,0x77,0x77};
  ETHTYPE ARP_ETHTYPE = {0x08,0x06};
  TRAMA envTRAMA,recvTRAMA;
  OPCODE RESP_ARP = {0x00,0x02}; // USADA SOLO PARA COMPARAR EN LOS FILTROS

  /*ARMANDO MENSAJE ARP EN LA ESTRUCTURA M_ARP*/
  MEN_ARP.MHWTP[0] = 0x00;
  MEN_ARP.MHWTP[1] = 0x01;

  MEN_ARP.MPROTP[0] = 0x08;
  MEN_ARP.MPROTP[1] = 0x00;

  MEN_ARP.MMACLEN = MACLEN;
  MEN_ARP.MIPLEN = IPLEN;

  MEN_ARP.MOPCODE[0] = 0x00;
  MEN_ARP.MOPCODE[1] = 0x01;

  memcpy(MEN_ARP.MAC_O,misDatos->miMAC,MACLEN);
  memcpy(MEN_ARP.IP_O,misDatos->miIP,IPLEN);
  memcpy(MEN_ARP.MAC_D,destDatos->miMAC,MACLEN);
  memcpy(MEN_ARP.IP_D,destDatos->miIP,IPLEN);
  /*FIN DE ARMADO*/

  tiempo tiempo1,tiempo2;
  memset(&tiempo1,0x00,sizeof(tiempo1));
  memset(&tiempo2,0x00,sizeof(tiempo1));
  float temporizador;

  creaMENSAJE_ARP(&MEN_ARP);
  creaTRAMA(MAC_BC,misDatos->miMAC,ARP_ETHTYPE,MEN_ARP.MSJ_ARP,MENSAJE_ARPLEN,envTRAMA);
  //imprimeTRAMA(envTRAMA,HEADMACLEN + MENSAJE_ARPLEN);
  enviaTRAMA(misDatos->packet_socket,envTRAMA,HEADMACLEN + MENSAJE_ARPLEN,misDatos->indice);
  bytesrecv = recibeTRAMA(misDatos->packet_socket,recvTRAMA);

  clock_gettime(CLOCK_REALTIME,&tiempo1);
  while(obtentiempo(tiempo1,tiempo2) < 0.4){
    bytesrecv = recibeTRAMA(misDatos->packet_socket,recvTRAMA);
    clock_gettime(CLOCK_REALTIME,&tiempo2);
    if( bytesrecv != -1){

      if(!memcmp(recvTRAMA,misDatos->miMAC,MACLEN) 
        && !memcmp(recvTRAMA + 20,RESP_ARP,OPCODELEN) 
        && !memcmp(recvTRAMA + 12,ARP_ETHTYPE,ETHTYPELEN) 
        && !memcmp(recvTRAMA + 28,destDatos->miIP,IPLEN) 
        && !memcmp(recvTRAMA + 38,misDatos->miIP,IPLEN)){

        memcpy(destDatos->miMAC,recvTRAMA + HEADMACLEN + 8,MACLEN);    
        return bytesrecv;
      } 
    }
  }
  memcpy(destDatos->miMAC,MAC_Default,MACLEN);
  return bytesrecv;
}

void creaMENSAJE_ARP(M_ARP *MEN_ARP){
  memcpy(MEN_ARP->MSJ_ARP,MEN_ARP->MHWTP,HWTPLEN);
  memcpy(MEN_ARP->MSJ_ARP + 2,MEN_ARP->MPROTP,PROTPLEN);
  MEN_ARP->MSJ_ARP[4] = MEN_ARP->MMACLEN;
  MEN_ARP->MSJ_ARP[5] = MEN_ARP->MIPLEN;
  memcpy(MEN_ARP->MSJ_ARP + 6,MEN_ARP->MOPCODE,OPCODELEN);
  memcpy(MEN_ARP->MSJ_ARP + 8,MEN_ARP->MAC_O,MACLEN);
  memcpy(MEN_ARP->MSJ_ARP + 14,MEN_ARP->IP_O,IPLEN);
  memcpy(MEN_ARP->MSJ_ARP + 18,MEN_ARP->MAC_D,MACLEN);
  memcpy(MEN_ARP->MSJ_ARP + 24,MEN_ARP->IP_D,IPLEN);
}

float obtentiempo(tiempo tiempo1,tiempo tiempo2){

  long nano = 0;
  int secs = 0;
  char *cadena;
  float tiempototal;

  if(tiempo1.tv_nsec > tiempo2.tv_nsec){
    nano = tiempo1.tv_nsec - tiempo2.tv_nsec;
    secs = (int)(tiempo2.tv_sec - tiempo1.tv_sec -1);
  }else{
    nano = tiempo2.tv_nsec - tiempo1.tv_nsec;
    secs = (int)(tiempo2.tv_sec - tiempo1.tv_sec);
  }

  tiempototal = secs + (nano*pow(10,-9));

  return tiempototal;
}

void obtenDatosARP(TRAMA recvTRAMA,M_ARP *infractor){
  memcpy(infractor->MHWTP,recvTRAMA + 14,2);
  memcpy(infractor->MPROTP, recvTRAMA + 16,2);

  infractor->MMACLEN = *recvTRAMA + 18;
  infractor->MIPLEN = *recvTRAMA + 19;

  memcpy(infractor->MOPCODE, recvTRAMA + 20,2);
  memcpy(infractor->MAC_O,recvTRAMA + 22,6);
  memcpy(infractor->IP_O,recvTRAMA + 28,4);
  memcpy(infractor->MAC_D,recvTRAMA + 32,6);
  memcpy(infractor->IP_D,recvTRAMA + 38,4);
}
/*FIN DE DECLARACION DE FUNCIONES*/

//%50s \t %7d\t\t
