typedef struct data{
  /*conteo y porcentajes*/
  int enviados;
  int recibidos;
  int perdidos;
  float p_lost;
  float p_recived;
  /*tiempos max min prom*/
  float t_total;
  float t_max;
  float t_min;
  float t_medio;
} Estadistica;

int Tracer(Datos misDatos,Datos destDatos,IP *ruta,Estadistica *t_trace,int show_estatistic){

    int i = 0,j = 0,flag = 0,secuencia = 0,retorno,guardada = 0;
    float tiempi;
    IP IPOrigen,IPMissed,IPGuardada;

    memset(IPMissed,0x00,sizeof(IP));

	system("clear");
    printf("\nTraza para [");
    imprimeIP(destDatos.miIP);
    printf("] con un maximo de 30 saltos ... \n\n");

    if(show_estatistic)
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
                    if(show_estatistic)
    					printf("\t %0.2f ms",tiempi*1000);
                    t_trace -> recibidos += 1;
                    t_trace -> t_total += tiempi;
                    if(guardada == 0){
                        memcpy(IPGuardada,IPOrigen,IPLEN);
                        guardada = 1;
                    }
    				break;
    			case 1:
    				//Respuesta del destino
                    if(show_estatistic)
    					printf("\t %0.2f ms",tiempi*1000);
                    t_trace -> recibidos += 1;
                    t_trace -> t_total += tiempi; 
                    flag = 1;
                    if(guardada == 0){
                        memcpy(IPGuardada,IPOrigen,IPLEN);
                        guardada = 1;
                    }
    				break;
    			case 2:
    				//Tiempo excedido
                    if(show_estatistic)
    					printf("\t\t*");
                    t_trace -> perdidos += 1;
    				break;
    			default:
    				printf("DESCONOCIDO\n");
    		}

            if (t_trace -> recibidos == 1 && retorno != 2)
                t_trace -> t_min = t_trace -> t_max = tiempi;
            else if(retorno != 2){
                if(tiempi > t_trace -> t_max)
                    t_trace -> t_max = tiempi;
                if(tiempi < t_trace -> t_min)
                    t_trace -> t_min = tiempi;
            }
    	}

        if(retorno != 2 || guardada == 1){
            printf("\t[");
            imprimeIP(IPGuardada);
            printf("]\n");
            memcpy(ruta[i - 1],IPGuardada,IPLEN);
            guardada = 0;
        }else{
            memcpy(ruta[i -1],IPMissed,IPLEN);
            printf("\n");
        }
	}

	if(flag != 1){
		printf("No se puede llegar al host con 30 saltos\n");
	}
	else{

        t_trace -> enviados = t_trace -> recibidos + t_trace -> perdidos;
        t_trace -> p_lost = (((float)t_trace -> perdidos)/((float)t_trace -> enviados))*100;
        t_trace -> p_recived = (((float)t_trace -> recibidos)/((float)t_trace -> enviados))*100;
        t_trace -> t_medio = t_trace -> t_total/((float)t_trace -> recibidos);

        if(show_estatistic){
            printf("\nEstadisticas ...\n\n");
            printf("Enviados =       %d\n",t_trace -> enviados);
            printf("Recibidos =      %d (%0.2f %%)\n",t_trace -> recibidos,t_trace -> p_recived);
            printf("Perdidos =       %d (%0.2f %%)\n",t_trace -> perdidos,t_trace -> p_lost);
            printf("Tiempo Maximo =  %0.2f ms\n",t_trace -> t_max*1000);
            printf("Tiempo Minimo =  %0.2f ms\n",t_trace -> t_min*1000);
            printf("Tiempo Medio =   %0.2f ms\n",t_trace -> t_medio*1000);
        }
	}
    return i - 1;
}
