#include <stdio.h>
#include<stdlib.h>
#include<string.h>
struct datos
{
	int dato[10][10];
	char nombredato[10][10];
	char nombrerelacion[10];
};
int ingresadatos(struct datos *x, int *comodin, int *grado);
int unioon(struct datos *x,int *comodin, int *grado);
void diferencia(struct datos *x, int *comodin, int *grado);

int main()
{
	struct datos x[10];
	int comodin[25],grado[10];
	diferencia(x,comodin,grado);
	
	/*int i;
	for(i=0;i<10;i++){
	printf("ingresa el nombre del dato\n");
	scanf("%s",x[i].nombredato);
	}
	printf("%s",x[].nombredato);*/
}
int ingresadatos(struct datos *x,int *comodin,int *grado)//aqui es donde se almacenan todos los datos de la tabla
{ 
	int num,i,cancel,k;
	printf("ingresa cuantas relaciones vas a usar\n");
	scanf("%d",&num);
	system("cls");
	for(i=0;i<num;i++){
		printf("ingresa el nombre de las relaciones\n");
		scanf("%s",x[i].nombrerelacion);
	}
	system("cls");
	printf("\ningresa de que grado van a ser tus relaciones");//pide el numero del grado para saber cuantos datos va a haber en la relacion
	for(i=0;i<num;i++)
		scanf("%d",&grado[i]);
	system("cls");
	
	for(int j=0;j<num;j++)
	{
		printf("\ningresa los nombres de los atributos de la relacion %s",x[j].nombrerelacion);
		
	
		for(i=0;i<grado[j];i++)//ingresa los nombres de los atributos de cada relacion
			{
				scanf("%s",&x[j].nombredato[i][0]);
	        }
	}
	system("cls");
	
		for( int j=0;j<num;j++)
	{
				
		for(i=0;i<grado[j];i++){
			printf("\ningresa los datos del atributo %s\n",&x[j].nombredato[i][0]);
k=0;
		for(cancel=0;cancel==0;){//ingresa datos de los atributos de cada relacion
		
		
			scanf("%d",&x[j].dato[j][k]);
			printf("deseas ingresar otro dato a %s\n\n0)si\n1)no\n",&x[j].nombredato[i][0]);
			scanf("%d",&cancel);
			k++;
			
			
		}
		comodin[i]=k;
	}
	}
		return num;
	
}
int unioon(struct datos *x,int *comodin, int *grado)
{
	int num=ingresadatos(x,comodin,grado),dif1,dif2;
	char A[10],B[10];
	printf("que relaciones deseas hacer union\n");
	scanf("%s%s",&A,&B);
	system("cls");
	

	for(int i=0;i<num;i++){
		
		dif1=strcmp(x[i].nombrerelacion,A);
        dif2=strcmp(x[i].nombrerelacion,B);
	}
	
	
	
	if(dif2!=0&&dif1!=0){
		printf("no existe al menos una relacion\n");
	}
		else{
	for( int j=0;j<num;j++)
	{
		
		for(int i=0;i<grado[j];i++){
			printf("\n %s\n",&x[j].nombredato[i][0]);
			
			for(int k=0;k<comodin[i];k++){
				
				
				printf("\n%d",x[j].dato[j][k]);
				
				
				
				
			}
		}
	}
	}
	return num;
	
}
void diferencia(struct datos *x, int *comodin, int *grado)
{
	int num=unioon(x,comodin,grado),dif1,dif2,rel1,rel2,k,C[10],D[10],E[10][10],F[10][10];
	char A[10],B[10];
	printf("que relaciones deseas hacer diferencia\n");
	scanf("%s%s",&A,&B);
	system("cls");
	
	
	for(int i=0;i<num;i++){
		
	    dif1=strcmp(x[i].nombrerelacion,A);
		if(dif1==0)
		{
			rel1=i;
		}
		dif2=strcmp(x[i].nombrerelacion,B);
		if(dif2==0)
		   {
		rel2=i;	
		}
	}
	k=0;
	if(dif2!=0&&dif1!=0){
		printf("no existe al menos una relacion\n");
	}
	else{
		
		for(int i=0;i<grado[rel1];i++){
			//C[i][0]=x[rel1].nombredato[i][0];
			for(int j=0;j<grado[rel2];j++)
			{
				//D[j][0]=x[rel2].nombredato[j][0];
			
			if(strcmp(x[rel1].nombredato[i],x[rel2].nombredato[j])==0)
			{
				for(int k=0;k<comodin[j];k++)
				{
					for(int l=0;l<comodin[j];l++)
					{
					if(x[rel1].dato[j][k]==x[rel2].dato[j][l])
					{
						x[rel1].dato[j][k]=0;
						
					}
					printf("%d\n",x[rel1].dato[j][k]);
				
				}
					
			}
				/*C[k]=i;
				D[k]=j;
				
				for(int l=0;l<comodin[i];l++)
				{
					for(int m=0;m<comodin[j];m++)
					{
						if(x[rel1].dato[k][l]!=x[rel2].dato[k][m])
							{
						E[k][l]=x[rel1].dato[k][l];
						F[k][m]=x[rel2].dato[k][m];
						}
						printf("%d,%d",E[k][l],F[k][m]);
						
						
					}
				}*/
			
				
			}
		
			}
		}
	}
	

}
/*#include <stdio.h>
#include <stdlib.h>

int main()
{
	char nom[20];
	int x;
	typedef char cadenaCaracteres [50]; //Definimos el tipo cadenaCaracteres
	cadenaCaracteres arrayCadenas[5]; //Creamos un vector de cadenas
	
	
	for(x=0;x<5;x++){
		printf("Ingrese nombre: ");
		scanf("%s",arrayCadenas[x]);
	}
	printf("\n");
	for(x=0;x<5;x++){
		printf("Elemento %d es %s \n", x, arrayCadenas[x]);
	}
	
	system("PAUSE");
	return 0;
}
*/

