#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 15 /* Tamanho maximo das strings dos nomes das lojas*/

/* Struct da arvore binaria*/
typedef struct No {
    double preco;
    int cod;
    char loja[MAX];
    struct No *dir, *esq, *pai;
} No;

typedef  No* p_no;


/*Structs da Fila para a organizacao e impressao das melhores ofertas*/
typedef struct Cap {
    p_no anuncio;
    struct Cap* prox;
    
} Cap ;

typedef Cap* p_cap;

typedef struct Fila {
    p_cap ini, fim;
} Fila;

typedef  Fila* p_fila;

/* Funcoes Bases*/

void destruir_arvore(p_no atual){
    /* Funcao que libera recursivamente a memoria alocada na arvore binaria*/

    if (atual != NULL){
        if(atual->dir == NULL && atual->esq == NULL)
            free(atual);
        else{
            destruir_arvore(atual->esq);
            destruir_arvore(atual->dir);
            free(atual);
        }
    
    }
}

p_fila criar_fila() {
    /*Funcao que cria uma fila para a impressao*/
    p_fila f;
    f = malloc(sizeof(Fila));
    f->ini = NULL;
    f->fim = NULL;
    return f;
}

void enfileirar(p_fila f, p_no raiz) {
    /*Funcao que adiciona um novo item ao final da Fila*/
    p_cap novo;

    if (raiz != NULL){
        novo = malloc(sizeof(Cap));

        novo->anuncio = raiz;
        novo->prox = NULL;
        
        if (f->ini == NULL)
            f->ini = novo;
        else
            f->fim->prox = novo;

        f->fim = novo;
    }
}

void desenfileirar(p_fila f, p_cap ret) {
    /*Funcao que retira um item especifico de alguma parte da fila e libera sua memria alocada*/
    p_cap atual;

    if(f->ini == ret){
        f->ini = ret->prox;
    }

    else{
        for(atual = f->ini ; atual->prox != ret  ; atual = atual->prox);

        if(f->fim == ret){
            f->fim = atual;
        }
        atual->prox = ret->prox;
    }
    free(ret);
}


/*Funcoes principais para resolucao do exercicio*/

p_no adicionar_ABB(p_no raiz, char loja[MAX] , int codigo, double preco) {
    /*Funcao recursivamente adiciona um novo produto de uma loja em uma arvore binaria ordenada sendo:
        1- Todos os nós da subárvore esquerda tem o preco de seu produto menor que o da raiz.
        2- Todos os nós da subárvore direita tem o preco de seu produto maior que o da raiz.
    */

    p_no novo;

    if (raiz == NULL) {

        novo = malloc(sizeof(No));

        novo->esq = novo->dir = novo->pai =NULL;
        strcpy(novo->loja, loja);
        novo->cod = codigo;
        novo->preco = preco;

        return novo;
    }

    if (preco < raiz->preco)
        raiz->esq = adicionar_ABB(raiz->esq, loja, codigo, preco);
    else
        raiz->dir = adicionar_ABB(raiz->dir, loja, codigo, preco);
    return raiz;
}

void buscar(p_no raiz, int codigo, double oferta, p_fila Fila) {
    /*Funcao que recursivamente busca pelos produtos com o mesmo codigo da oferta que tenham seu preco como menor que
    110% o preco da oferta.
    Adicionando cada produto em uma fila*/

    if(raiz != NULL) {

        if (raiz->preco <= oferta*(1.1)) {
           if(raiz->cod == codigo)
                enfileirar(Fila, raiz);

            buscar(raiz->esq, codigo, oferta, Fila);
            buscar(raiz->dir, codigo, oferta, Fila);
        }
        else
            buscar(raiz->esq, codigo, oferta, Fila);
    }
    
}

void imprimir_destruir_fila(p_fila f, int codigo) {
    /*Funcao que imprime as melhores ofertas para de um produto em ordem alfabetica com respeito ao nome das lojas.
    Liberando a memoria alocada depois da impressao.
    */
    p_cap atual , menor;

    printf("\n");
    printf("OFERTAS para %d:\n", codigo);

    if(f->ini == NULL)
        printf("nenhuma boa oferta foi encontrada\n");
    else
        while(f->ini != NULL) {

            menor = f->ini;

            for( atual = f->ini ; atual != NULL; atual = atual->prox)
                if(strcmp(atual->anuncio->loja, menor->anuncio->loja) < 0) 
                    menor = atual;
                
            printf("%s %d %0.2f \n", menor->anuncio->loja, menor->anuncio->cod, menor->anuncio->preco);
            desenfileirar(f, menor);
        }
    free(f);
}


/* Execucao dos codigos e leitura das entradas*/

int main() {
    /*Declaracao das variaveis*/

    char loja[MAX];
    int n, m, codigo;
    double oferta, preco;
    p_no AB = NULL;
    p_fila Fila;
    
    /*Leitura dos anuncios cadastrados*/
    scanf("%d", &n);

    for( int i = 0; i < n ; i++) {
        scanf("%s %d %lf", loja, &codigo, &preco);
        AB = adicionar_ABB(AB, loja, codigo, preco);
    }
    
    /*Leitura das ofertas consultadas pelo usuario*/
    scanf("%d", &m);

    for( int j = 0; j < m; j++) {
        scanf("%d %lf", &codigo, &oferta);

        /*Execucao da busca e impressao*/
        Fila = criar_fila();

        buscar(AB, codigo, oferta, Fila);

        imprimir_destruir_fila(Fila, codigo);
    }

    /*Liberacao da memoria alocada para a ABB*/
    destruir_arvore(AB);
}
