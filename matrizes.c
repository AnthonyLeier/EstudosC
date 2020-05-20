#include<stdio.h>
#include<stdlib.h>

struct MATRIX{
	int linha;
	int coluna;
	double **matr;
};

typedef struct MATRIX Matrix;

Matrix* criar(int lin, int col){
	int i,j;
	double **mat;
	mat=(double**)malloc(lin*sizeof(double*));
	for(i=0;i<lin;i++){
		mat[i]=(double*)malloc(col*sizeof(double));
		for(j=0;j<col;j++){
			mat[i][j]=0;
		}			
	}
	
	Matrix *A;
	A=(Matrix*)malloc(sizeof(Matrix));
	A->matr=mat;
	A->linha=lin;
	A->coluna=col;
	return A;
} 

void imprimir(Matrix* M){
	int i,j;
	for(i=0;i<M->linha;i++){
		for(j=0;j<M->coluna;j++){
			printf("%lf ",M->matr[i][j]);
		}	
		printf("\n");
	}
	return;
}

Matrix* preenche(Matrix* M){
	int i,j;
	double valor;
	
	Matrix *resultado;
	resultado=(Matrix*)malloc(sizeof(Matrix));
	
	resultado = criar(M->linha, M->coluna);
	resultado->linha=M->linha;
	resultado->coluna=M->coluna;
	
	for(i=0;i<M->linha;i++){
		for(j=0;j<M->coluna;j++){
			scanf("%lf", &valor);
			M->matr[i][j] = valor;
		}
	}
	return;
}

Matrix* soma(Matrix* M, Matrix* M2){
	int i,j;
	
	Matrix *resultado = (Matrix*)malloc(sizeof(Matrix));
	
	resultado = criar(M->linha, M->coluna);
	resultado->linha=M->linha;
	resultado->coluna=M->coluna;	
	
	for(i=0;i<M->linha;i++){
		for(j=0;j<M->coluna;j++){
			resultado->matr[i][j] = M->matr[i][j] + M2->matr[i][j];			
		}
	}	
	
	return resultado;
}

Matrix* subtracao(Matrix* M, Matrix* M2){
	int i,j;
	
	Matrix *resultado = (Matrix*)malloc(sizeof(Matrix));
	
	resultado = criar(M->linha, M->coluna);
	resultado->linha=M->linha;
	resultado->coluna=M->coluna;	
	
	for(i=0;i<M->linha;i++){
		for(j=0;j<M->coluna;j++){
			resultado->matr[i][j] = M->matr[i][j] - M2->matr[i][j];			
		}
	}	
	
	return resultado;
}

int main(){
	Matrix *M, *M1, *M2, *R1, *R2;
	M1 = criar(3,3);	
	M2 = criar(3,3);
	R1 = criar(3,3);	
	R2 = criar(3,3);
	preenche(M1);	
	preenche(M2);	
	R1 = soma(M1,M2);			
	R2 = subtracao(M1,M2);		
	imprimir(R1);
	printf("\n");
	imprimir(R2);
	return 0;
}



