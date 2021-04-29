#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include <sys/time.h>

//MatrixCreate ler e criar os elementos
//MatrixDestrói dar free na memória;

struct no {
    int line;
    int column;
    double info;
    struct no * right;
    struct no * below;
};
typedef struct no Matrix;

void tiraNo(Matrix * M, int posicaoi, int posicaoj);

Matrix * CriarN0(int l, int c) {
    Matrix * N = (Matrix * ) malloc(sizeof(Matrix));
    N -> info = 0;
    N -> line = l;
    N -> column = c;
    N -> right = NULL;
    N -> below = NULL;
    return N;
}

Matrix * zeros(int n, int m) {
    Matrix * M;
    M = (Matrix * ) malloc(sizeof(Matrix));
    M -> line = n;
    M -> column = m;
    M -> right = M;
    M -> below = M;
    int i;
    Matrix * aux;
    for (i = n; i > 0; i--) {
        aux = CriarN0(i, -1);
        aux -> below = M -> below;
        M -> below = aux;
        aux -> right = aux;
    }
    for (i = m; i > 0; i--) {
        aux = CriarN0(-1, i);
        aux -> right = M -> right;
        M -> right = aux;
        aux -> below = aux;
    }
    return M;
}
void matrix_setelem(Matrix * M, int posicaoi, int posicaoj, float novo_valor) {

    //apontar o aux para o inicio
    if (posicaoi < 1 || posicaoj < 1 || posicaoi > M -> line || posicaoj > M -> column) {
        printf("ERRO, posicao invalida!!!\n");
        return;
    } else if (novo_valor == 0) {
        tiraNo(M, posicaoi, posicaoj);
        return;
    } else {
        int k, i, j;
        Matrix * aux2, * aux3;
        Matrix * aux = CriarN0(posicaoi, posicaoj);
        aux -> info = novo_valor;
        aux2 = M;
        for (i = 0; i < posicaoj; i++) {
            aux2 = aux2 -> right;
        }
        for (aux3 = aux2, aux2 = aux2 -> below; aux2 -> line < posicaoi && aux2 -> line != -1; aux3 = aux2, aux2 = aux2 -> below);
        if (aux2 -> line == posicaoi) {
            aux2 -> info = aux -> info;
            free(aux);
        } else {
            aux -> below = aux2;
            aux3 -> below = aux;
            aux2 = M;
            for (i = 0; i < posicaoi; i++) {
                aux2 = aux2 -> below;
            }

            for (aux3 = aux2, aux2 = aux2 -> right; aux2 -> column < posicaoj &&
                aux2 -> column != -1; aux3 = aux2, aux2 = aux2 -> right)
            ;
            aux -> right = aux2;
            aux3 -> right = aux;
        }
    }

    return;
}

//retorna o valor do elemento (x, y) da matriz m.
float matrix_getelem(Matrix * M, int posicaoi, int posicaoj) {
    int k, i, j;
    double valor;
    Matrix * aux2, * aux3;

    //apontar o aux para o inicio
    if (posicaoi < 1 || posicaoj < 1 || posicaoi > M -> line || posicaoj > M -> column) {
        printf("ERRO, posicao selecionada invalida!!!\n");
        return -999;
    } else {
        //fazendo ele percorrer até a posicao que eu quero colocar
        // o valor
        // tratamento de erro se a posicao já conter um valor
        aux2 = M;
        for (i = 0; i < posicaoj; i++) {
            aux2 = aux2 -> right;
        }
        for (aux3 = aux2, aux2 = aux2 -> below; aux2 -> line < posicaoi && aux2 -> line != -1; aux3 = aux2, aux2 = aux2 -> below)
        ;

        if (aux2 -> line == posicaoi) { //tirar o no quando for 0 /preencher aleatorio / tempo de execução das funções
            valor = aux2 -> info;
        } else {
            return 0.0;
        }

        //printf("posicao-> %d %d %lf\n", aux2->line, aux2->column, aux2->info);
    }

    return valor;
}

void imprimir(Matrix * M) {
    int i, j;
    Matrix * aux;
    aux = M -> below;
    //printf("IMPRESSAO!!\n");
    for (aux = M -> below; aux != M; aux = aux -> below) {
        for (aux = aux -> right; aux -> column != -1; aux = aux -> right) {
            printf("%d %d %lf \n", aux -> line, aux -> column, aux -> info);
        }
    }
}

void imprimirBurra(Matrix * M) {
    int i, j;

    for (i = 0; i < M -> line; i++) {
        for (j = 0; j < M -> column; j++) {
            printf("%.1lf\t", matrix_getelem(M, i + 1, j + 1));
        }
        printf("\n");
    }
    return;
}

Matrix * criarAleatorio(int posicaoi, int posicaoj) {
    int i, j;
    time_t t;
    Matrix * M;
    M = zeros(posicaoi, posicaoj);
    srand((unsigned int) time( & t));
    for (i = 0; i < M -> line; i++) {
        for (j = 0; j < M -> column; j++) {
            matrix_setelem(M, i + 1, j + 1, ((float) rand() / (float)(RAND_MAX)) * 5.0);
        }
    }
    return M;
}

void tiraNo(Matrix * M, int posicaoi, int posicaoj) {
    int i, j;
    Matrix * aux, * aux2;
    aux = M;
    for (i = 0; i != posicaoi; i++) {
        aux = aux -> below;
    }
    for (; aux -> right -> column < posicaoj && aux -> right -> column != -1; aux = aux -> right)
    ;
    if (aux -> right -> column == posicaoj) {
        aux -> right = aux -> right -> right;
    }
    aux = M;
    for (j = 0; j != posicaoj; j++) {
        aux = aux -> right;
    }
    for (; aux -> below -> line < posicaoi && aux -> below -> line != -1; aux = aux -> below)
    ;
    if (aux -> below -> line == posicaoi) {
        aux2 = aux -> below;
        aux -> below = aux -> below -> below;
        free(aux2);
    }
    return;
}

Matrix * MatrixCreate() {
    int k, i, j, posicaoi, posicaoj;
    double novo_valor;
    Matrix * aux2, * aux3, * M;
    scanf("%d %d", & i, & j);
    if (i < 0 || j < 0) {
        M = NULL;
        return M;
    } else {
        M = zeros(i, j);
    }

    while (1) {
        //apontar o aux para o inicio
        scanf("%d %d %lf", & posicaoi, & posicaoj, & novo_valor);
        Matrix * aux = CriarN0(posicaoi, posicaoj);
        aux -> info = novo_valor;

        if (posicaoi == 0 || posicaoj == 0) {
            printf("Execução encerrada!!!\n");
            break;
        } else {
            //fazendo ele percorrer até a posicao que eu quero colocar
            // o valor
            // tratamento de erro se a posicao já conter um valor
            matrix_setelem(M, posicaoi, posicaoj, novo_valor);
            // Aqui está o problema
        }
    }

    return M;
}

void matrix_destroy(Matrix * M) {
    int i, j;
    Matrix * aux, * aux2;
    aux = M -> below;
    for (aux2 = M, aux = M -> below; aux != M; aux2 = aux, aux = aux -> below) {
        for (aux2 = aux2 -> right, aux = aux -> right; aux -> column != -1; aux2 = aux) {
            aux = aux -> right;
            free(aux2);
        }
        free(aux2);
    }

    free(aux);
    return;
}

Matrix * somaBurra(Matrix * A, Matrix * B) {
    int i, j;
    if (A -> line == B -> line && A -> column == B -> column) {
        Matrix * C = zeros(A -> line, A -> column);
        for (i = 1; i <= A -> line; i++) {
            for (j = 1; j <= A -> column; j++) {
                matrix_setelem(C, i, j, matrix_getelem(A, i, j) + matrix_getelem(B, i, j));
            }
        }
        return C;
    }
    return NULL;
}

Matrix * soma(Matrix * A, Matrix * B) {
    Matrix * auxA, * auxB;
    int i;
    Matrix * vet[A -> column];
    if (A -> line == B -> line && A -> column == B -> column) {
        Matrix * C, * auxC, * auxNo;
        C = zeros(B -> line, A -> column);
        auxA = A -> below -> right;
        auxB = B -> below -> right;
        auxC = C;
        for (i = 0; i < A -> column; i++) {
            vet[i] = auxC -> right;
            auxC = auxC -> right;
        }
        auxC = C -> below;
        //printf("--> posicao %d %d \n", auxA->column, auxB->column);
        while (auxA -> line != -1 || auxB -> line != -1) {
            while (auxA -> column != -1 || auxB -> column != -1) {

                if ((auxA -> column < auxB -> column || auxB -> column == -1) && auxA -> column != -1) {
                    //printf("entrou1 %d %d \n", auxA->column, auxB->column);
                    auxNo = CriarN0(auxA -> line, auxA -> column);
                    auxNo -> info = auxA -> info;
                    auxA = auxA -> right;

                } else if ((auxA -> column > auxB -> column || auxA -> column == -1) && auxB -> column != -1) {
                    //printf("entrou2 %d %d \n", auxA->column, auxB->column);
                    auxNo = CriarN0(auxB -> line, auxB -> column);
                    auxNo -> info = auxB -> info;
                    auxB = auxB -> right;
                } else if (auxA -> column == auxB -> column) {
                    //printf("entrou3 %d %d \n", auxA->column, auxB->column);
                    auxNo = CriarN0(auxA -> line, auxA -> column);
                    auxNo -> info = auxA -> info + auxB -> info;
                    auxA = auxA -> right;
                    auxB = auxB -> right;
                }

                auxNo -> right = auxC -> right;
                auxC -> right = auxNo;
                auxC = auxNo;
                auxNo -> below = vet[auxNo -> column - 1] -> below;
                vet[auxNo -> column - 1] -> below = auxNo;
                vet[auxNo -> column - 1] = auxNo;

            }
            auxA = auxA -> below -> right;
            auxB = auxB -> below -> right;
        }
        return C;
    }
}
Matrix * trasposta(Matrix * M) {
    Matrix * aux;
    int i, j;
    aux = zeros(M -> column, M -> line);
    for (i = 0; i < M -> line; i++) {
        for (j = 0; j < M -> column; j++) {
            matrix_setelem(aux, j + 1, i + 1, matrix_getelem(M, i + 1, j + 1));
        }

    }
    return aux;
}
void main() {
    int i, n;
    double valor;
    Matrix * M1, * M2, * M3;

    for (n = 1; n < 10; n = n * 2) {
        M1 = criarAleatorio(n, n);
        M2 = criarAleatorio(n, n);

        struct timeval start, end;
        clock_t t;

        gettimeofday( & start, NULL);
        t = clock(); //armazena tempo
        for (i = 0; i < 100; i++) {
            M3 = soma(M1, M2);
        }
        t = clock() - t; //tempo final - tempo inicial
        gettimeofday( & end, NULL);
        float var1 = ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));

        gettimeofday( & start, NULL);
        t = clock(); //armazena tempo
        for (i = 0; i < 100; i++) {
            M3 = somaBurra(M1, M2);
        }
        t = clock() - t; //tempo final - tempo inicial
        gettimeofday( & end, NULL);
        float var2 = ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));

        printf("%lf, %lf, %d\n", var1, var2, n);
    }
}