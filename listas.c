#include<stdio.h>
#include<stdlib.h>


struct no{
	int valor;
	struct no *prox;

};
struct lista{
	int tam;	
	struct no *inicio;

};

typedef struct no NO; 
typedef struct lista LISTA; 


LISTA* inicializar(){
	LISTA *L;
	L=(LISTA*)malloc( sizeof(LISTA) );
	L->tam=0;
	L->inicio=NULL;
	return L;
}
NO* CriarNo(int valor){
	NO *N;
	N=(NO*)malloc( sizeof(NO) );
	N->valor=valor;
	N->prox=NULL;
	return N;
	
}
void InserirInicio(LISTA *L, NO *N){
	N->prox=L->inicio;
	L->inicio=N;
	return;	

}
void InserirFim(LISTA *L, NO *N){
	NO *aux;
	if(L->inicio==NULL) L->inicio=N;
	else{
		for(aux=L->inicio;aux->prox!=NULL ;aux=aux->prox);
		aux->prox=N;
		
	}
	return;	
}
void InserirOrdenado(LISTA *L, NO *N){
	NO *aux;
	if(L->inicio==NULL) L->inicio=N;
	else{
		for(aux=L->inicio;aux->prox!=NULL ;aux=aux->prox);
		aux->prox=N;
		
	}
	return;	
}
void retirar(int val){

}

void RetirarInicio(int val){

}
void RetirarFim(int val){

}

void imprimir(LISTA *L){

	printf("NOSSA LISTA\n");
	NO *aux;
	for(aux=L->inicio;aux!=NULL;aux=aux->prox){
		printf("%d ",aux->valor);
	}
	return;
	
}



void main(){

	LISTA *L;
	NO *N;
	L=inicializar();

	N=CriarNo(10);
	InserirInicio(L,N);

	N=CriarNo(3);
	InserirInicio(L,N);
	
	N=CriarNo(5);
	InserirInicio(L,N);
	
	N=CriarNo(6);
	InserirInicio(L,N);
	
	imprimir(L);
	
	return;
}
