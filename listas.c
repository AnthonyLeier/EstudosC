#include <stdio.h>
#include <stdlib.h>

struct no {
    int valor;
    struct no *prox;
};
struct lista {
    int tam;
    struct no *inicio;
};

typedef struct no NO;
typedef struct lista LISTA;

LISTA *inicializar() {
    LISTA *L;
    L = (LISTA *)malloc(sizeof(LISTA));
    L->tam = 0;
    L->inicio = NULL;
    return L;
}
NO *CriarNo(int valor) {
    NO *N;
    N = (NO *)malloc(sizeof(NO));
    N->valor = valor;
    N->prox = NULL;
    return N;
}
void InserirInicio(LISTA *L, NO *N) {
    N->prox = L->inicio;
    L->inicio = N;
    L->tam++;
    return;
}
void InserirFim(LISTA *L, NO *N) {
    NO *aux;
    if (L->inicio == NULL)
        L->inicio = N;
    else {
        for (aux = L->inicio; aux->prox != NULL; aux = aux->prox)
            ;
        aux->prox = N;
    }
    L->tam++;
    return;
}
void InserirOrdenado(LISTA *L, NO *N) {
    NO *aux;
    if (L->inicio == NULL)
        L->inicio = N;
    else if (N->valor < L->inicio->valor) {
        N->prox = L->inicio;
        L->inicio = N;
    } else {
        for (aux = L->inicio; aux->prox != NULL && N->valor >= aux->prox->valor;
             aux = aux->prox)
            ;
        N->prox = aux->prox;
        aux->prox = N;
    }
    L->tam++;
    return;
}
NO *retirar(LISTA *L, int val) {
    NO *ultimo;
    NO *antipenultimo;
    if (val == L->inicio->valor) {
        ultimo = L->inicio;
        L->inicio = L->inicio->prox;
        L->tam--;
        return ultimo;
    } else {
        for (ultimo = L->inicio, antipenultimo = L->inicio;
             ultimo != NULL && ultimo->valor < val;
             antipenultimo = ultimo, ultimo = ultimo->prox)
            ;
        if (ultimo != NULL && ultimo->valor == val) {
            antipenultimo->prox = ultimo->prox;
            L->tam--;
            return ultimo;
        } else {
            return NULL;
        }
    }
}

LISTA *copiar(LISTA *L) {  // Implementar copiar uma lista para outra lista
    LISTA *novo = inicializar();
    NO *aux;
    for (aux = L->inicio; aux != NULL; aux = aux->prox) {
        InserirFim(novo, CriarNo(aux->valor));
    }
    return novo;
}

NO *RetirarInicio(LISTA *L) {
    NO *aux;
    aux = L->inicio;
    L->inicio = L->inicio->prox;
    if (L->tam > 0) {
        L->tam--;
    }
    aux->prox = NULL;
    return aux;
}
LISTA *ordenar(LISTA *L) {
    NO *aux;
    LISTA *novo;
    novo = inicializar();
    while (L->inicio != NULL) {
        aux = RetirarInicio(L);
        InserirOrdenado(novo, aux);
    }
    return novo;
}

NO *RetirarFim(LISTA *L) {
    NO *ultimo;
    NO *antipenultimo;
    /*
     NO *ultimo = L;
     NO *antipenultimo= L;
    while(ultimo->prox != NULL){
        antipenultimo = ultimo;
        ultimo = ultimo->prox;

    }*/
    for (ultimo = L->inicio, antipenultimo = L->inicio; ultimo->prox != NULL;
         antipenultimo = ultimo, ultimo = ultimo->prox)
        ;
    antipenultimo->prox = NULL;

    if (L->tam > 0) {
        L->tam--;
    }
    return ultimo;
}

void imprimir(LISTA *L) {
    printf("NOSSA LISTA\t");
    NO *aux;
    for (aux = L->inicio; aux != NULL; aux = aux->prox) {
        printf("%d ", aux->valor);
    }
    printf("\n");
    return;
}

void main() {
    LISTA *L, *novo;
    NO *N;
    L = inicializar();

    N = CriarNo(15);
    InserirInicio(L, N);
    // InserirOrdenado(L,N);
    N = CriarNo(5);
    InserirInicio(L, N);
    // InserirOrdenado(L,N);
    N = CriarNo(3);
    InserirInicio(L, N);
    // InserirOrdenado(L,N);
    N = CriarNo(6);
    InserirInicio(L, N);
    // InserirOrdenado(L,N);
    // RetirarFim(L);
    // N = retirar(18,L);
    imprimir(L);

    L = ordenar(L);

    novo = copiar(L);
    RetirarFim(L);
    imprimir(L);
    imprimir(novo);

    return;
}