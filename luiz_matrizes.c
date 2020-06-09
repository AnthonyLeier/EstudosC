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

Matrix* identidade(int tam){
    double **mat;
    int i ,j;
    mat=(double**)malloc(tam*sizeof(double*));
	for(i=0;i<tam;i++){
		mat[i]=(double*)malloc(tam*sizeof(double));
		for(j=0;j<tam;j++){
			 if(i==j){
                mat[i][j]=1;
            }else{
                mat[i][j]=0;
            }
		}
	}
	Matrix *b;
	b = (Matrix*)malloc(sizeof(Matrix));
	b->matr=mat;
	b->linha=tam;
	b->coluna=tam;
	return b;
}

void imprimir(Matrix* M1){
	int i,j;
	for(i=0;i<M1->linha;i++){
		for(j=0;j<M1->coluna;j++){
			printf("%lf ",M1->matr[i][j]);
		}
		printf("\n");
	}
	return;
}

Matrix* preenche(Matrix* M1){
	int i,j;
	double valor;

	Matrix *resultado;
	resultado=(Matrix*)malloc(sizeof(Matrix));

	resultado = criar(M1->linha, M1->coluna);
	resultado->linha=M1->linha;
	resultado->coluna=M1->coluna;

	for(i=0;i<M1->linha;i++){
		for(j=0;j<M1->coluna;j++){
			scanf("%lf", &valor);
			M1->matr[i][j] = valor;
		}
	}
	return;
}

Matrix* soma(Matrix* M1, Matrix* M2){
	int i,j;

	Matrix *resultado = (Matrix*)malloc(sizeof(Matrix));

	resultado = criar(M1->linha, M1->coluna);
	resultado->linha=M1->linha;
	resultado->coluna=M1->coluna;

	for(i=0;i<M1->linha;i++){
		for(j=0;j<M1->coluna;j++){
			resultado->matr[i][j] = M1->matr[i][j] + M2->matr[i][j];
		}
	}
	return resultado;
}

Matrix* subtracao(Matrix* M1, Matrix* M2){
	int i,j;

	Matrix *resultado = (Matrix*)malloc(sizeof(Matrix));

	resultado = criar(M1->linha, M1->coluna);
	resultado->linha=M1->linha;
	resultado->coluna=M1->coluna;

	for(i=0;i<M1->linha;i++){
		for(j=0;j<M1->coluna;j++){
			resultado->matr[i][j] = M1->matr[i][j] - M2->matr[i][j];
		}
	}

	return resultado;
}

double determinante(Matrix *M1){
    int linha,coluna;
    linha = M1->linha;
    coluna = M1->coluna;
    int i,j;
    double a;
    double Mat[linha][coluna];
    for(i=0;i<linha;i++){
        for(j=0;j<coluna;j++){
            Mat[i][j]=M1->matr[i][j];
        }
    }
    int k, p=1;
    double aux;
    for(k=0;k<coluna-1;k++){
        if(Mat[k][k]==0){
           for(i= k+1;i<linha;i++){
                if(Mat[i][k]!= 0){
                   for(j=k;j<coluna;j++){
                        aux = Mat[i][j];
                        Mat[i][j]= Mat[k][j];
                        Mat[k][j]=aux;
                   }
                   p = p *(-1);
                   break;
                }
            }
        }
        if(Mat[k][k]==0)return 0;
        for(i = k + 1;i<linha;i++){
           a = Mat[i][k]/Mat[k][k];
           for(j = k;j<coluna;j++){
                Mat[i][j]=Mat[i][j] - Mat[k][j]*a;
           }
        }
        for(i=0;i<linha;i++){
            for(j=0;j<coluna;j++){
                printf("%lf ",Mat[i][j]);
            }printf("\n");
        }printf("\n");
    }
    double total=1;
    for(i=0;i<linha;i++){
        total = total * Mat[i][i];

    }
    //printf("%lf",total*p);
    return total*p;
}
Matrix* multiplicacao(Matrix *M1, Matrix *M2){
    if(M1->coluna == M2->linha){
        Matrix *resultado = (Matrix*)malloc(sizeof(Matrix));
        resultado = criar(M1->linha,M2->coluna);
        int i,j,b;
        double somaprod;
        for(j=0; j<M1->linha; j++){
            for(b=0; b<M2->coluna; b++){
              somaprod=0;
              for(i=0; i<M1->coluna; i++) {
                    somaprod=somaprod+(M1->matr[j][i]* M2->matr[i][b]);
              }
              resultado->matr[j][b]=somaprod;
            }
        }
        return resultado;
    }else{
        return NULL;
    }
  }
int main(){
	//Matrix *M, *M1, *M2, *R1, *R2;
	//M1 = criar(3,3);
	//M2 = criar(3,3);
	//R1 = criar(3,3);
	//R2 = criar(3,3);
	//preenche(M1);
	//preenche(M2);
	//R1 = soma(M1,M2);
	//R2 = subtracao(M1,M2);
	//imprimir(R1);
	//printf("\n");
	//imprimir(R2);
	//printf("\n");
	//Matrix *M3;
	//M3 = identidade(4);
	//imprimir(M3);
	/*Matrix *Det;
	double D;
	Det = criar(3,3);
	preenche(Det);
	imprimir(Det);
	printf("\n");
	D = determinante(Det);
	printf("\n");
    imprimir(Det);
    printf("O determinante eh: %lf",D);*/
    Matrix *M3,*M4,*R3;
    M3 = criar(3,2);
    M4 = criar(2,3);
    preenche(M3);
    preenche(M4);
    R3 = multiplicacao(M3,M4);
    imprimir(R3);
    return 0;
}
