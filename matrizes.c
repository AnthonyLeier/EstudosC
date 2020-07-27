#include <stdio.h>
#include <stdlib.h>

struct MATRIX {
    int linha;
    int coluna;
    double **matr;
};
typedef struct MATRIX Matrix;

Matrix *criar(int lin, int col) {
    int i, j;
    double **mat;
    mat = (double **)malloc(lin * sizeof(double *));

    for (i = 0; i < lin; i++) {
        mat[i] = (double *)malloc(col * sizeof(double));
        for (j = 0; j < col; j++) {
            mat[i][j] = 0;
        }
    }

    Matrix *A;
    A = (Matrix *)malloc(sizeof(Matrix));
    A->matr = mat;
    A->linha = lin;
    A->coluna = col;
    return A;
}

Matrix *identidade(int tam) {
    double **mat;
    int i, j;
    mat = (double **)malloc(tam * sizeof(double *));

    for (i = 0; i < tam; i++) {
        mat[i] = (double *)malloc(tam * sizeof(double));
        for (j = 0; j < tam; j++) {
            if (i == j) {
                mat[i][j] = 1;
            } else {
                mat[i][j] = 0;
            }
        }
    }

    Matrix *b;
    b = (Matrix *)malloc(sizeof(Matrix));
    b->matr = mat;
    b->linha = tam;
    b->coluna = tam;
    return b;
}

void imprimir(Matrix *M) {
    int i, j;
    for (i = 0; i < M->linha; i++) {
        for (j = 0; j < M->coluna; j++) {
            printf("%lf ", M->matr[i][j]);
        }
        printf("\n");
    }
    return;
}

void preenche(Matrix *M) {
    int i, j;
    double valor;

    Matrix *resultado;
    resultado = (Matrix *)malloc(sizeof(Matrix));

    resultado = criar(M->linha, M->coluna);
    resultado->linha = M->linha;
    resultado->coluna = M->coluna;

    for (i = 0; i < M->linha; i++) {
        for (j = 0; j < M->coluna; j++) {
            scanf("%lf", &valor);
            M->matr[i][j] = valor;
        }
    }
    return;
}

Matrix *soma(Matrix *M, Matrix *M2) {
    int i, j;

    Matrix *resultado = (Matrix *)malloc(sizeof(Matrix));

    resultado = criar(M->linha, M->coluna);
    resultado->linha = M->linha;
    resultado->coluna = M->coluna;

    for (i = 0; i < M->linha; i++) {
        for (j = 0; j < M->coluna; j++) {
            resultado->matr[i][j] = M->matr[i][j] + M2->matr[i][j];
        }
    }

    return resultado;
}

Matrix *subtracao(Matrix *M, Matrix *M2) {
    int i, j;

    Matrix *resultado = (Matrix *)malloc(sizeof(Matrix));

    resultado = criar(M->linha, M->coluna);
    resultado->linha = M->linha;
    resultado->coluna = M->coluna;

    for (i = 0; i < M->linha; i++) {
        for (j = 0; j < M->coluna; j++) {
            resultado->matr[i][j] = M->matr[i][j] - M2->matr[i][j];
        }
    }

    return resultado;
}

double determinante(Matrix *M1) {
    int linha, coluna;
    linha = M1->linha;
    coluna = M1->coluna;
    int i, j;
    double a;
    double Mat[linha][coluna];
    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++) {
            Mat[i][j] = M1->matr[i][j];
        }
    }
    int k, p = 1;
    double aux;
    for (k = 0; k < coluna - 1; k++) {
        if (Mat[k][k] == 0) {
            for (i = k + 1; i < linha; i++) {
                if (Mat[i][k] != 0) {
                    for (j = k; j < coluna; j++) {
                        aux = Mat[i][j];
                        Mat[i][j] = Mat[k][j];
                        Mat[k][j] = aux;
                    }
                    p = p * (-1);
                    break;
                }
            }
        }
        if (Mat[k][k] == 0) return 0;
        for (i = k + 1; i < linha; i++) {
            a = Mat[i][k] / Mat[k][k];
            for (j = k; j < coluna; j++) {
                Mat[i][j] = Mat[i][j] - Mat[k][j] * a;
            }
        }
        for (i = 0; i < linha; i++) {
            for (j = 0; j < coluna; j++) {
                printf("%lf ", Mat[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    double total = 1;
    for (i = 0; i < linha; i++) {
        total = total * Mat[i][i];
    }
    // printf("%lf",total*p);
    return total * p;
}

Matrix *zeraTriangulo(Matrix *M1) {
    Matrix *resultado = (Matrix *)malloc(sizeof(Matrix));

    resultado = criar(M1->linha, M1->coluna);
    resultado->linha = M1->linha;
    resultado->coluna = M1->coluna;

    int linha, coluna;
    linha = M1->linha;
    coluna = M1->coluna;
    int i, j;
    double a;
    double Mat[linha][coluna];
    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++) {
            Mat[i][j] = M1->matr[i][j];
        }
    }
    int k, p = 1;
    double aux;
    for (k = 0; k < coluna - 1; k++) {
        if (Mat[k][k] == 0) {
            for (i = k + 1; i < linha; i++) {
                if (Mat[i][k] != 0) {
                    for (j = k; j < coluna; j++) {
                        aux = Mat[i][j];
                        Mat[i][j] = Mat[k][j];
                        Mat[k][j] = aux;
                    }
                    p = p * (-1);
                    break;
                }
            }
        }
        if (Mat[k][k] == 0) return 0;
        for (i = k + 1; i < linha; i++) {
            a = Mat[i][k] / Mat[k][k];
            for (j = k; j < coluna; j++) {
                Mat[i][j] = Mat[i][j] - Mat[k][j] * a;
            }
        }
        for (i = 0; i < linha; i++) {
            for (j = 0; j < coluna; j++) {
                printf("%lf ", Mat[i][j]);
                resultado->matr[i][j] = Mat[i][j];
            }
            printf("\n");
        }
        printf("\n");
    }
    double total = 1;
    for (i = 0; i < linha; i++) {
        total = total * Mat[i][i];
    }
    return resultado;
}

Matrix *multiplicacao(Matrix *M1, Matrix *M2) {
    if (M1->coluna == M2->linha) {
        Matrix *resultado = (Matrix *)malloc(sizeof(Matrix));
        resultado = criar(M1->linha, M2->coluna);
        int i, j, b;
        double somaprod;
        for (j = 0; j < M1->linha; j++) {
            for (b = 0; b < M2->coluna; b++) {
                somaprod = 0;
                for (i = 0; i < M1->coluna; i++) {
                    somaprod = somaprod + (M1->matr[j][i] * M2->matr[i][b]);
                }
                resultado->matr[j][b] = somaprod;
            }
        }
        return resultado;
    } else {
        return NULL;
    }
}

Matrix *transposta(Matrix *M1) {
    int i, j;

    Matrix *resultado = (Matrix *)malloc(sizeof(Matrix));
    resultado = criar(M1->linha, M1->coluna);
    resultado->linha = M1->linha;
    resultado->coluna = M1->coluna;

    for (i = 0; i < resultado->linha; i++) {
        for (j = 0; j < resultado->coluna; j++) {
            resultado->matr[j][i] = M1->matr[i][j];
        }
    }

    return resultado;
}

Matrix *diagonal(Matrix *M1) {
    Matrix *resultado;

    resultado = zeraTriangulo(M1);
    resultado = transposta(resultado);
    resultado = zeraTriangulo(resultado);

    return resultado;
}

Matrix *inversa(Matrix *M1) {
    if (determinante(M1) != 0) {
        Matrix *ident = identidade(M1->linha);
        Matrix *resultado = (Matrix *)malloc(sizeof(Matrix));
        resultado = criar(M1->linha, M1->coluna);
        resultado->linha = M1->linha;
        resultado->coluna = M1->coluna;

        int linha, coluna;
        linha = M1->linha;
        coluna = M1->coluna;
        int i, j;
        double a;

        resultado->matr = (double **)malloc(linha * sizeof(double *));
        for (i = 0; i < linha; i++) {
            resultado->matr[i] = (double *)malloc(coluna * sizeof(double));
            for (j = 0; j < coluna; j++) {
                resultado->matr[i][j] = M1->matr[i][j];
            }
        }

        int k, p = 1;
        double aux;
        for (k = 0; k < coluna - 1; k++) {
            if (resultado->matr[k][k] == 0) {
                for (i = k + 1; i < linha; i++) {
                    if (resultado->matr[i][k] != 0) {
                        for (j = 0; j < coluna; j++) {
                            aux = resultado->matr[i][j];
                            resultado->matr[i][j] = resultado->matr[k][j];
                            resultado->matr[k][j] = aux;

                            aux = ident->matr[i][j];
                            ident->matr[i][j] = ident->matr[k][j];
                            ident->matr[k][j] = aux;
                        }
                        p = p * (-1);
                        break;
                    }
                }
            }
            if (resultado->matr[k][k] == 0) return NULL;
            for (i = k + 1; i < linha; i++) {
                a = resultado->matr[i][k] / resultado->matr[k][k];
                for (j = 0; j < coluna; j++) {
                    resultado->matr[i][j] =
                        resultado->matr[i][j] - resultado->matr[k][j] * a;
                    ident->matr[i][j] =
                        ident->matr[i][j] - ident->matr[k][j] * a;
                }
            }
        }

        for (k = coluna - 1; k > 0; k--) {
            if (resultado->matr[k][k] == 0) {
                for (i = k - 1; i >= 0; i--) {
                    if (resultado->matr[i][k] != 0) {
                        for (j = 0; j < coluna; j++) {
                            aux = resultado->matr[i][j];
                            resultado->matr[i][j] = resultado->matr[k][j];
                            resultado->matr[k][j] = aux;

                            aux = ident->matr[i][j];
                            ident->matr[i][j] = ident->matr[k][j];
                            ident->matr[k][j] = aux;
                        }
                        p = p * (-1);
                        break;
                    }
                }
            }
            if (resultado->matr[k][k] == 0) return NULL;
            for (i = k - 1; i >= 0; i--) {
                a = resultado->matr[i][k] / resultado->matr[k][k];
                for (j = coluna - 1; j >= 0; j--) {
                    resultado->matr[i][j] =
                        resultado->matr[i][j] - resultado->matr[k][j] * a;
                    ident->matr[i][j] =
                        ident->matr[i][j] - ident->matr[k][j] * a;
                }
            }
        }

        for (i = 0; i < linha; i++) {
            a = resultado->matr[i][i];
            resultado->matr[i][i] = resultado->matr[i][i] / a;
            for (j = 0; j < coluna; j++) {
                ident->matr[i][j] = ident->matr[i][j] / a;
            }
        }

        return ident;
    } else {
        return NULL;
    }
}

int main() {
    Matrix *M1, *M2, *result;
    M1 = criar(3, 3);
    M2 = criar(3, 1);
    preenche(M1);
    preenche(M2);
    result = inversa(M1);
    result = multiplicacao(result, M2);
    imprimir(result);

    return 0;
}