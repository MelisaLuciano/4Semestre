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
int escaneoDeRed(MYSQL *con);
void ARP_server(MYSQL*);
void obtenDatosARP(TRAMA,M_ARP*);
/*FIN DE PROTOTIPOS DE FUNCIONES*/

/*DECLARACION DE FUNCIONES*/
int ARP(Datos *misDatos,Datos *destDatos){

  int bytesrecv;

  M_ARP MEN_ARP;
  MAC MAC_BC = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
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
        break;
      }
    }
  }
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

int escaneoDeRed(MYSQL *con){

  int direcciones;
  char nom_interfaz[10],charIP[20],charMAC[20];

  Datos misDatos,destDatos;
  memset(&misDatos,0x00,sizeof(misDatos));
    memset(&destDatos,0x00,sizeof(destDatos));

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

      memcpy(destDatos.miIP,misDatos.miIP,IPLEN);
      destDatos.miIP[3] = 1;
      printf("IP              MAC\n");
      for (direcciones = 0; direcciones < 254; ++direcciones){

        if(ARP(&misDatos,&destDatos) != -1){
          imprimeIP(destDatos.miIP);printf("     ");imprimeMAC(destDatos.miMAC);printf("\n");
          charIP[0] = '\0';
          charMAC[0] = '\0';
          IP_ntoa(destDatos.miIP,charIP);
          MAC_ntoa(destDatos.miMAC,charMAC);
          addToDB(con,charIP,charMAC);
        }

        destDatos.miIP[3] += 1;
      }
    }
    printf("Terminado !!");
    close(misDatos.packet_socket);
    return 0;
}

void ARP_server(MYSQL *con){

  char nom_interfaz[10],IPbuscar[20],MACbuscada[18],MACinfractor[18];
  int bytesrecv;

  ETHTYPE ARP_ETHTYPE = {0x08,0x06};
  OPCODE SOL_ARP = {0x00,0x01};
  TRAMA recvTRAMA, envTRAMA;

  IP IPGRATUITA = {0x00,0x00,0x00,0x00};// SOLO CON FINES DE COMPARAR
  MAC MACNULA = {0x00,0x00,0x00,0x00,0x00,0x00},MAC_BC = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
  M_ARP infractor, defensor;

  Datos misDatos;

  /*ARMANDO MENSAJE ARP EN LA ESTRUCTURA M_ARP*/
  defensor.MHWTP[0] = 0x00;
  defensor.MHWTP[1] = 0x01;

  defensor.MPROTP[0] = 0x08;
  defensor.MPROTP[1] = 0x00;

  defensor.MMACLEN = MACLEN;
  defensor.MIPLEN = IPLEN;
  /*FIN DE ARMADO*/

  memset(&misDatos,0x00,sizeof(misDatos));

  misDatos.packet_socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

  if(misDatos.packet_socket == -1){
      perror("Error al abrir el socket.\n");
      exit(-1);
    }
    else{
      printf("Exito al abrir el socket.\n");

      if (fcntl(misDatos.packet_socket, F_SETFL, O_NONBLOCK) == -1){
        perror("Socket no se puede poner en modo no bloqueante.");
        exit(-1);
      }

      printf("Da el nombre de la interfaz: ");
      scanf(" %s",nom_interfaz);

      strcpy(misDatos.nom_interfaz,nom_interfaz);

      if(obtenParametros(&misDatos) == -1)
        exit(-1);

      while(1){
        bytesrecv = recibeTRAMA(misDatos.packet_socket,recvTRAMA);
        
        if( bytesrecv != -1){
          if(!memcmp(recvTRAMA + 12,ARP_ETHTYPE,ETHTYPELEN)
            && !memcmp(recvTRAMA + 20,SOL_ARP,OPCODELEN)){
            //Obtenemos datos de la trama

            //imprimeTRAMA(recvTRAMA,bytesrecv);
            //char ip_or[25],ip_de[25],mac_or[25],mac_de[25];
            //mac_de[0] = mac_or[0] = ip_de[0] = ip_or[0] = '\0';

            memset(&infractor,0x00,sizeof(infractor));
            MACbuscada[0] = IPbuscar[0] = MACinfractor[0] = '\0';

            obtenDatosARP(recvTRAMA,&infractor);

            /*IP_ntoa(infractor.IP_O,ip_or);
            IP_ntoa(infractor.IP_D,ip_de);
            MAC_ntoa(infractor.MAC_O,mac_or);
            MAC_ntoa(infractor.MAC_D,mac_de);

            printf("MAC Origen: %s\n",mac_or);
            printf("IP Origen: %s\n", ip_or);
            printf("MAC Destino: %s\n",mac_de);
            printf("IP Destino: %s\n", ip_de);
            printf("******************************************\n");*/

            
            MAC_ntoa(infractor.MAC_O,MACinfractor); //TOMO LA MAC ORIGEN (1)
            //Obtenemos la IP Origen y la buscamos en la base de datos
            if(!memcmp(infractor.IP_O,IPGRATUITA,IPLEN))
              IP_ntoa(infractor.IP_D,IPbuscar);
            else
              IP_ntoa(infractor.IP_O,IPbuscar);

            printf("MAC INFRACTORA: %s\n",MACinfractor);
            printf("IP INFRACTORA: %s\n", IPbuscar);

            searchIP(con,IPbuscar,MACbuscada);

            printf("IP A BUSCAR: %s\n",IPbuscar);
            printf("MAC ENCONTRADA: %s\n",MACbuscada);

            printf("*******************************\n");


            if (strcmp(MACbuscada,"NULL") && strcmp(MACbuscada,MACinfractor)){
              
              MAC_aton(MACbuscada,defensor.MAC_O);
              IP_aton(IPbuscar,defensor.IP_O);
              memcpy(defensor.MAC_D,infractor.MAC_O,MACLEN);
              IP_aton(IPbuscar,defensor.IP_D);

              /*CREANDO RESPUESTA DE ARP GRATUITO*/
              defensor.MOPCODE[0] = 0x00;
              defensor.MOPCODE[1] = 0x02;

              creaMENSAJE_ARP(&defensor);
              creaTRAMA(defensor.MAC_D,defensor.MAC_O,ARP_ETHTYPE,defensor.MSJ_ARP,MENSAJE_ARPLEN,envTRAMA);
              imprimeTRAMA(envTRAMA,HEADMACLEN + MENSAJE_ARPLEN);
              enviaTRAMA(misDatos.packet_socket,envTRAMA,HEADMACLEN + MENSAJE_ARPLEN,misDatos.indice);
              /*ENVIADA*/

              /*CREANDO SOLICITUD DE ARP GRATUITO*/
              defensor.MOPCODE[0] = 0x00;
              defensor.MOPCODE[1] = 0x01;

              memcpy(defensor.MAC_D,MACNULA,MACLEN);
              creaMENSAJE_ARP(&defensor);
              creaTRAMA(MAC_BC,defensor.MAC_O,ARP_ETHTYPE,defensor.MSJ_ARP,MENSAJE_ARPLEN,envTRAMA);
              imprimeTRAMA(envTRAMA,HEADMACLEN + MENSAJE_ARPLEN);
              enviaTRAMA(misDatos.packet_socket,envTRAMA,HEADMACLEN + MENSAJE_ARPLEN,misDatos.indice);
              /*ENVIADA*/
            }
          }
        }
      }
    close(misDatos.packet_socket);
  }  
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
