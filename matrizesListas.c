#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
void tiraNo(Matrix *M, int posicaoi, int posicaoj) {
    int i, j;
    Matrix *aux, *aux2;
    aux = M;
    for (i = 0; i != posicaoi; i++) {
        aux = aux->below;
    }
    for (; aux->right->column < posicaoj && aux->right->column != -1; aux = aux->right)
        ;
    if (aux->right->column == posicaoj) {
        aux->right = aux->right->right;
    }
    aux = M;
    for (j = 0; j != posicaoj; j++) {
        aux = aux->right;
    }
    for (; aux->below->line < posicaoi && aux->below->line != -1; aux = aux->below)
        ;
    if (aux->below->line == posicaoi) {
        aux2 = aux->below;
        aux->below = aux->below->below;
        free(aux2);
    }
    return;
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
    } else if (novo_valor == 0) {
        tiraNo(M, posicaoi, posicaoj);
        free(aux);
        return;
    } else {
        aux2 = M;
        for (i = 0; i < posicaoj; i++) {
            aux2 = aux2->right;
        }
        for (aux3 = aux2, aux2 = aux2->below; aux2->line < posicaoi && aux2->line != -1; aux3 = aux2, aux2 = aux2->below)
            ;
        if (posicaoi == aux2->line) {
            aux2->info = aux->info;
            free(aux);
        } else {
            aux->below = aux2;
            aux3->below = aux;

            aux2 = M;
            for (i = 0; i < posicaoi; i++) {
                aux2 = aux2->below;
            }

            for (aux3 = aux2, aux2 = aux2->right; aux2->column < posicaoj && aux2->column != -1; aux3 = aux2, aux2 = aux2->right)
                ;
            aux->right = aux2;
            aux3->right = aux;
        }
    }

    return;
}
void criarAleatorio(Matrix *M) {
    int i, j;
    srand((unsigned int)time(NULL));
    for (i = 0; i < M->line; i++) {
        for (j = 0; j < M->column; j++) {
            matrix_setelem(M, i + 1, j + 1, ((float)rand() / (float)(RAND_MAX)) * 5.0);
        }
    }
    return;
}

double matrix_getelem(Matrix *M, int x, int y) {
    Matrix *result;
    Matrix *aux, *aux2;
    int i;

    if (x < 1 || y < 1 || x > M->line || y > M->column) {
        printf("Erro - Posicao invalida da Matriz!\n");
        return;
    } else {
        // Percorrer ate a posicao que eu quero pegar o valor
        aux = M;
        for (i = 0; i < y; i++) aux = aux->right;
        for (aux2 = aux, aux = aux->below; aux->line < x && aux->line != -1; aux2 = aux, aux = aux->below)
            ;

        if (aux->line == x)
            return aux->info;
        else
            return 0;
    }
}

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

void imprimirBurra(Matrix *M) {
    int i, j;

    for (i = 0; i < M->line; i++) {
        for (j = 0; j < M->column; j++) {
            printf("%.1lf\t", matrix_getelem(M, i + 1, j + 1));
        }
        printf("\n");
    }
    return;
}

Matrix *create() {
    int posicaoi;
    int posicaoj;
    float valor;
    Matrix *M;
    int linhas;
    int colunas;

    printf("Insira a largura da Matriz: ");
    scanf("%d", &linhas);
    printf("Insira o comprimento da Matriz: ");
    scanf("%d", &colunas);

    M = zeros(linhas, colunas);

    printf("Digite os elementos e -1 para parar\n");
    do {
        printf("Digite a posicao X do elemento: ");
        scanf("%d", &posicaoi);
        printf("Digite a posicao y do elemento: ");
        scanf("%d", &posicaoj);
        printf("Digite o valor do elemento: ");
        scanf("%f", &valor);

        if (valor >= 0) matrix_setelem(M, posicaoi, posicaoj, valor);

    } while (valor >= 0);
    printf("Matriz Finalizada\n");
    return M;
}

void destroy(Matrix *M) {
    int i, j;
    Matrix *aux, *delete;
    aux = M->below;
    for (aux = M->below; aux != M; aux = aux->below) {
        for (aux = aux->right; aux->column != -1; aux = aux->right) {
            delete = aux;
            free(delete);
        }
    }
}

void main() {
    Matrix *M;
    M = create();
    imprimir(M);
    destroy(M);
    imprimir(M);
}