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
	return ;
} 




int main(){
	Matrix *M;
	M=criar(3,3);
	imprimir(M);
	return 0;
}



