#include <stdio.h>
#include <stdlib.h>

struct no {
    int line;
    int column;
    double info;
    struct no *right;
    struct no *below;
};
typedef struct no Matrix;

Matrix *CriarN0(int l, int c) {
    Matrix *N = (Matrix *)malloc(sizeof(Matrix));
    N->info = 0;
    N->line = l;
    N->column = c;
    N->right = NULL;
    N->below = NULL;
    return N;
}

Matrix *zeros(int n, int m) {
    Matrix *M;
    M = (Matrix *)malloc(sizeof(Matrix));
    M->line = n;
    M->column = m;
    M->right = M;
    M->below = M;
    int i;
    Matrix *aux;
    for (i = n; i > 0; i--) {
        aux = CriarN0(i, -1);
        aux->below = M->below;
        M->below = aux;
        aux->right = aux;
    }
    for (i = m; i > 0; i--) {
        aux = CriarN0(-1, i);
        aux->right = M->right;
        M->right = aux;
        aux->below = aux;
    }
    return M;
}

// arrumar tratamento de erro se a posicao ja existe
void matrix_setelem(Matrix *M, int posicaoi, int posicaoj, float novo_valor) {
    int k, i, j;
    Matrix *aux2, *aux3;
    Matrix *aux = CriarN0(posicaoi, posicaoj);
    aux->info = novo_valor;

    // apontar o aux para o inicio
    if (posicaoi < 1 || posicaoj < 1 || posicaoi > M->line ||
        posicaoj > M->column) {
        printf("ERRO, posicao invalida!!!\n");
        free(aux);
        return;
    } else {
        // fazendo ele percorrer atÃ© a posicao que eu quero colocar
        // o valor
        // tratamento de erro se a posicao jÃ¡ conter um valor
        aux2 = M;
        for (i = 0; i < posicaoi; i++) {
            aux2 = aux2->right;
        }
        for (aux3 = aux2, aux2 = aux2->below;
             aux2->line < posicaoj && aux2->line != -1;
             aux3 = aux2, aux2 = aux2->below)
            ;
        aux->below = aux2;
        aux3->below = aux;

        aux2 = M;
        for (i = 0; i < posicaoj; i++) {
            aux2 = aux2->below;
        }

        for (aux3 = aux2, aux2 = aux2->right;
             aux2->column < posicaoi && aux2->column != -1;
             aux3 = aux2, aux2 = aux2->right)
            ;
        aux->right = aux2;
        aux3->right = aux;
    }

    return;
}

// retorna o valor do elemento (x, y) da matriz m.
float matrix_getelem(Matrix *m, int x, int y) {}

void imprimir(Matrix *M) {
    int i, j;
    Matrix *aux;
    aux = M->below;
    printf("IMPRESSAO!!\n");
    for (aux = M->below; aux != M; aux = aux->below) {
        for (aux = aux->right; aux->column != -1; aux = aux->right) {
            printf("%d %d %lf \n", aux->line, aux->column, aux->info);
        }
    }
}

void main() {
    Matrix *M, *aux;
    M = zeros(3, 4);

    matrix_setelem(M, 1, 1, 50.0);
    matrix_setelem(M, 1, 1, 255.0);
    matrix_setelem(M, 2, 1, 655.0);
    matrix_setelem(M, 4, 4, 755.55);

    /*
    for(aux=M->right;aux!=M;aux=aux->right){
            printf("%lf %d %d \n",aux->info,aux->line,aux->column);
    }
    for(aux=M->below;aux!=M;aux=aux->below){
            printf("%lf %d %d \n",aux->info,aux->line,aux->column);
    }
    */

    imprimir(M);

    return;
}
