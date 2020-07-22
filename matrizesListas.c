#include<stdio.h>
#include<stdlib.h>


struct no{
	double valor;
	int line;
	int column;
	struct no *linha;
	struct no *coluna;

};
typedef struct no matrix;


matrix* CriarN0(int l,int c){
	matrix *N=(matrix*)malloc(sizeof(matrix));
	N->valor=0;
	N->line=l;
	N->column=c;
	N->linha=NULL;
	N->coluna=NULL;
	return N;
}




matrix *zeros(int n,int m){
	matrix *M;
	M=(matrix*)malloc(sizeof(matrix));
	M->line=n;
	M->column=m;
	M->linha=M;
	M->coluna=M;
	int i;
	matrix* aux;
	for(i=n;i>0;i--){
		aux=CriarN0(i,-1);
		aux->linha=M->linha;
		M->linha=aux;
		aux->coluna=aux;
	}
	for(i=m;i>0;i--){
		aux=CriarN0(-1,i);
		aux->coluna=M->coluna;
		M->coluna=aux;
		aux->linha=aux;
	}
	return M;
}


matrix* inserir(matrix *M,matrix *no){



}


void imprimir(matrix *M){




}



void main(){

	matrix *M;
	M=zeros(3,4);
	
	
	matrix *aux;
	for(aux=M->linha;aux!=M;aux=aux->linha){
		printf("%lf %d %d \n",aux->valor,aux->line,aux->column);
	}
	for(aux=M->coluna;aux!=M;aux=aux->coluna){
		printf("%lf %d %d \n",aux->valor,aux->line,aux->column);
	}

	return;
}


