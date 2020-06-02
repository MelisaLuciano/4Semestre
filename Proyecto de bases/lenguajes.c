#include <stdio.h>
#include <stdlib.h>
struct lista{
	struct nodo * inicial;
	struct nodo * actual;
	struct nodo * aux;
};
struct nodo{
	int N;
	char cadena[50];
	struct nodo * sig;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////P
struct lista L1, L2, L3, L4, L5, L6, LI;
int strl(char * lol);
void strc(char * lol1, char * lol2);
int stre(char * lol1, char * lol2);
void agregar(struct lista * L, char * lol);
void inicializar(struct lista * L);
void imprimirL(struct lista * L);
void deleteL(struct lista * L);
int chequeo(char * lol);
void lenguajes(void);
void flush_in(void);
int lcheck(char * lol, struct lista * L);
void menu(void);
void lunion(struct lista * LP, struct lista * LS);
void Union(void);
void invertir(char * u);
void Reflexion(void);
void reflejar(struct lista * L);
void concatenar(char * u, char * v);
void Concatena(struct lista * LP, struct lista * LS);
void Concatenacion(void);
void Potencia(void);
void Lcopia(struct lista * LP, struct lista * LS);
void potenciar(struct lista * L, int p);
void reflejar2(struct lista * L);
void ClausuraPositiva(void);
void clpos(struct lista * L, int p);
void OperacionEstrella(void);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////M
void main(void){
	inicializar(&L1);inicializar(&L2);inicializar(&L3);inicializar(&L4);
	lenguajes();
	menu();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////F
void menu(void){
	int a = 0;
	while(a != 7){
		printf("\nL1: ");
		imprimirL(&L1);
		printf("L2: ");
		imprimirL(&L2);
		printf("\n1.- Union\n2.- Concatenacion\n3.- Potencia\n4.- Reflexion\n5.- Cierre o clausura positiva\n6.- Cierre u operacion de estrella\n7.- Salir\n\n");
		scanf("%d",&a);
		switch(a){
			case 1:
				Union();
				break;
			case 2:
				Concatenacion();
				break;
			case 3:
				Potencia();
				break;
			case 4:
				Reflexion();
				break;
			case 5:
				ClausuraPositiva();
				break;
			case 6:
				OperacionEstrella();
				break;
			case 7:
				break;
			default:
				printf("Opcion no valida\n");
				break;
		}
	}
}
void OperacionEstrella(void){
	int a, b;
	a = 0;b = 0;
	printf("Ingresa la potencia para L1\n");
	scanf("%d",&a);
	printf("Ingresa la potencia para L2\n");
	scanf("%d",&b);
	if(a < 0){
		printf("L1+(%d): ",a);
		a = a*(-1);
		reflejar2(&L1);
		agregar(&L5,"|0|");
		clpos(&LI,a);
		deleteL(&LI);
	}
	else{
		printf("L1+(%d): ",a);
		agregar(&L5,"|0|");
		clpos(&L1,a);
	}
	if(b < 0){
		printf("L2+(%d): ",b);
		b = b*(-1);
		reflejar2(&L2);
		agregar(&L5,"|0|");
		clpos(&LI,b);
		deleteL(&LI);
	}
	else{
		printf("L2+(%d): ",b);
		agregar(&L5,"|0|");
		clpos(&L2,b);
	}

}
void clpos(struct lista * L, int p){
	int a;
	a = 2;
	Lcopia(&L4,L);
	Lcopia(&L6,L);
	Concatena(L,&L4);
	deleteL(&L4);
	if(p == 0){
		printf("{}");
	}
	if(p == 1){
		imprimirL(L);
	}
	if(p >= 2){
		do{
			lunion(&L6,&L3);
			Lcopia(&L4,&L3);
			Lcopia(&L6,&L5);
			deleteL(&L3);
			Concatena(&L4,L);
			deleteL(&L4);
			a++;
			if(p==2)
				break;
		}while(a <= p);
		imprimirL(&L5);
		deleteL(&L3);
		deleteL(&L4);
		deleteL(&L5);
		deleteL(&L6);
	}
	deleteL(&L3);
	deleteL(&L4);
	deleteL(&L5);
	deleteL(&L6);
}
void ClausuraPositiva(void){
	int a, b;
	a = 0;b = 0;
	printf("Ingresa la potencia para L1\n");
	scanf("%d",&a);
	printf("Ingresa la potencia para L2\n");
	scanf("%d",&b);
	if(a < 0){
		printf("L1+(%d): ",a);
		a = a*(-1);
		reflejar2(&L1);
		clpos(&LI,a);
		deleteL(&LI);
	}
	else{
		printf("L1+(%d): ",a);
		clpos(&L1,a);
	}
	if(b < 0){
		printf("L2+(%d): ",b);
		b = b*(-1);
		reflejar2(&L2);
		clpos(&LI,b);
		deleteL(&LI);
	}
	else{
		printf("L2+(%d): ",b);
		clpos(&L2,b);
	}
}
void potenciar(struct lista * L, int p){
	int a;
	a = 2;
	Lcopia(&L4,L);
	Concatena(L,&L4);
	if(p == 0){
		deleteL(&L3);
		agregar(&L3,"|0|");
		imprimirL(&L3);
		deleteL(&L3);
	}
	if(p == 1){
		imprimirL(L);
	}
	if(p == 2){
		imprimirL(&L3);
		deleteL(&L3);
		deleteL(&L4);
	}
	if(p > 2){
		while(a < p){
			Lcopia(&L4,&L3);
			deleteL(&L3);
			Concatena(&L4,L);
			a++;
		}
		imprimirL(&L3);
		deleteL(&L3);
		deleteL(&L4);
	}
	deleteL(&L3);
	deleteL(&L4);
}
void Potencia(void){
	int a, b;
	a = 0;b = 0;
	printf("Ingresa la potencia para L1\n");
	scanf("%d",&a);
	printf("Ingresa la potencia para L2\n");
	scanf("%d",&b);
	if(a < 0){
		printf("L1(%d): ",a);
		a = a*(-1);
		reflejar2(&L1);
		potenciar(&LI,a);
		deleteL(&LI);
	}
	else{
		printf("L1(%d): ",a);
		potenciar(&L1,a);
	}
	if(b < 0){
		printf("L2(%d): ",b);
		b = b*(-1);
		reflejar2(&L2);
		potenciar(&LI,b);
		deleteL(&LI);
	}
	else{
		printf("L2(%d): ",b);
		potenciar(&L2,b);
	}
	
}
void reflejar2(struct lista * L){
	L->aux = L->inicial;
	while(L->aux->sig != NULL){
		invertir(L->aux->cadena);
		L->aux = L->aux->sig;
	}
	invertir(L->aux->cadena);
	Lcopia(&LI,&L3);
	deleteL(&L3);
}

void Lcopia(struct lista * LP, struct lista * LS){
	deleteL(LP);
	LS->aux = LS->inicial;
	while(LS->aux->sig != NULL){
		agregar(LP,LS->aux->cadena);
		LS->aux = LS->aux->sig;
	}
	agregar(LP,LS->aux->cadena);
}
void Concatenacion(void){
	Concatena(&L1,&L2);
	printf("L1L2: ");
	imprimirL(&L3);
	deleteL(&L3);
	Concatena(&L2,&L1);
	printf("L2L1: ");
	imprimirL(&L3);
	deleteL(&L3);
}
void Concatena(struct lista * LP, struct lista * LS){
	LP->aux = LP->inicial;
	LS->aux = LS->inicial;
	while(LP->aux->sig != NULL){
		while(LS->aux->sig != NULL){
			concatenar(LP->aux->cadena,LS->aux->cadena);
			LS->aux = LS->aux->sig;
		}
		concatenar(LP->aux->cadena,LS->aux->cadena);
		LS->aux = LS->inicial;
		LP->aux = LP->aux->sig;
	}
	while(LS->aux->sig != NULL){
			concatenar(LP->aux->cadena,LS->aux->cadena);
			LS->aux = LS->aux->sig;
	}
	concatenar(LP->aux->cadena,LS->aux->cadena);
}
void concatenar(char * u, char * v){
	int a=0,b=0,c=0;
	a=0;b=0;c=0;
	char * cadenaC;
	a = strl(u)+strl(v);
	cadenaC = (char *) malloc(a+1);
	for(b=0;b<=a;b++){
		if(*(u+c)=='\0'){
			break;
		}
			*(cadenaC+b) = *(u+c);
		c++;		
	}
	c=0;
	for(b=b;b<=a;b++){
		if(*(v+c)=='\0'){
			*(cadenaC+b) = '\0';
			break;
		}
		*(cadenaC+b) = *(v+c);
		c++;
	}
	if(lcheck(cadenaC,&L3)==0){
		agregar(&L3,cadenaC);
	}
	free(cadenaC);
}
void reflejar(struct lista * L){
	L->aux = L->inicial;
	while(L->aux->sig != NULL){
		invertir(L->aux->cadena);
		L->aux = L->aux->sig;
	}
	invertir(L->aux->cadena);
	imprimirL(&L3);
	Lcopia(&LI,&L3);
	deleteL(&L3);
}
void Reflexion(void){
	printf("L1(-1): ");
	reflejar(&L1);
	printf("L2(-1): ");
	reflejar(&L2);
	deleteL(&LI);
}
void invertir(char * u){
	char * cadenaI;
	int a=0,b=0;
	cadenaI = (char *)malloc(strl(u)+1);
	for(a=strl(u)-1;a>=0;a--){
		*(cadenaI+b)=*(u+a);
		b++;
	}
	*(cadenaI+b)='\0';
	agregar(&L3,cadenaI);
	free(cadenaI);
}	
void lunion(struct lista * LP, struct lista * LS){
	LP->aux = LP->inicial;
	LS->aux = LS->inicial;
	while(LP->aux->sig != NULL){
		if(lcheck(LP->aux->cadena,&L5)==0){
			agregar(&L5,LP->aux->cadena);
		}
		LP->aux = LP->aux->sig;
	}
	if(lcheck(LP->aux->cadena,&L5)==0){
			agregar(&L5,LP->aux->cadena);
	}
	////////////////////////////////////////
	while(LS->aux->sig != NULL){
		if(lcheck(LS->aux->cadena,&L5)==0){
			agregar(&L5,LS->aux->cadena);
		}
		LS->aux = LS->aux->sig;
	}
	if(lcheck(LS->aux->cadena,&L5)==0){
			agregar(&L5,LS->aux->cadena);
	}
}
void Union(void){
	printf("L1 U L2: ");
	lunion(&L1,&L2);
	imprimirL(&L5);
	deleteL(&L5);
}
int lcheck(char * lol, struct lista * L){
	if(L->inicial == NULL){return 0;}
	L->aux = L->inicial;
	while(L->aux->sig != NULL){
		if(stre(lol,L->aux->cadena)==1){
			return 1;
		}
		L->aux = L->aux->sig;
	}
	if(stre(lol,L->aux->cadena)==1){
		return 1;
	}
	else{
		return 0;
	}
}
void lenguajes(void){
	char * p = (char *)malloc(25);
	int a = 0, b = 0;
	printf("Lenguaje: 1\n");
	while(b != 1){
		while(a != 1){
			printf("Introducir elemento\n");
			scanf("%s",p);
			a = chequeo(p);
		}
		agregar(&L1,p);
		printf("¿Continuar?\n");
		scanf("%d",&b);
		a = 0; 
	}
	b = 0;
	printf("Lenguaje: 2\n");
	while(b != 1){
		while(a != 1){
			printf("Introducir elemento\n");
			scanf("%s",p);
			a = chequeo(p);
		}
		agregar(&L2,p);
		printf("¿Continuar?\n");
		scanf("%d",&b);
		a = 0; 
	}
	free(p);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////A
void flush_in(void){ 
	int ch; 
	while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){} 
}
int strl(char * lol){
	int a = 0;
	while(*(lol+a) != '\0'){
		a++;
	}
	return a;
}
void strc(char * lol1, char * lol2){
	int a = 0;
	while(*(lol2+a) != '\0'){
		*(lol1+a) = *(lol2+a);
		a++;
	}
	*(lol1+a) = '\0';
}
int stre(char * lol, char * lol2){
	int a,b;
	a = 0;b = 0;
	if(strl(lol) != strl(lol2)){return 0;}
	else{
		while(*(lol+a) != '\0'){
			if(*(lol+a) == *(lol2+a)){
				b++;
			}
			a++;
		}
	}
	if(a == b){return 1;}
	else{return 0;}
}
int chequeo(char * lol){
	int a,b;
	a = 0;b = 0;
	while(*(lol+a)!='\0'){
		if(*(lol+a)>=48 && *(lol+a)<=57 || *(lol+a)>=97 && *(lol+a)<=122){
			b++;
		}
		a++;
	}
	if(a == b){return 1;}
	else{return 0;}
}
void inicializar(struct lista * L){
	L->inicial = NULL;
	L->actual = NULL;
	L->aux = NULL;
}
void agregar(struct lista * L, char * lol){
	L->aux = (struct nodo *)malloc(sizeof(struct nodo));
	strc(L->aux->cadena,lol);
	if(L->inicial == NULL){
		L->aux->N = 1;
		L->inicial = L->aux;
		L->actual = L->aux;
		L->aux = NULL;
		L->inicial->sig = NULL;
	}
	else{
		L->aux->N = L->actual->N + 1;
		L->actual->sig = L->aux;
		L->aux->sig = NULL;
		L->actual = L->aux;
		L->aux = NULL;
	}
}
void imprimirL(struct lista * L){
	if(L->inicial == NULL){
		printf("Lista vacia\n");
	}
	else{
		L->aux = L->inicial;
		printf("{");
		while(L->aux->sig != NULL){
			printf("%s,", L->aux->cadena);
			L->aux = L->aux->sig;
		}
		printf("%s}\n", L->aux->cadena);		
	}
}
void deleteL(struct lista * L){
	L->aux = L->inicial;
	if(L->inicial == NULL){
		//
	}
	else{
		while(L->aux->sig != NULL){
			L->inicial = L->aux;
			L->aux = L->inicial->sig;
			free(L->inicial);
			L->inicial = L->aux;
		}
		free(L->inicial);
		L->inicial = NULL;
		L->actual = NULL;
		L->aux = NULL;
	}
}
