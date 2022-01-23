#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 21
#define NIV 6

/* Struct da Arvore Binaria*/

typedef struct AB {
    char nome[MAX];
    double invest;
    struct AB * dir, *esq, *pai;
} AB;

typedef  AB* pAB;

/* Struct da Fila e dos nós dessa fila*/

typedef struct No {
    pAB pessoa;
    struct No* prox;
    
} No ;

typedef No* p_no;

typedef struct Fila {
    p_no ini, fim;
} Fila;

typedef  Fila* p_fila;


/*Funcoes bases da arvore binaria*/

pAB criar_arvore(char nome[MAX], int investimento) {
    /*Funcao que criar uma arvore binaria*/
    pAB Topo;

    Topo = malloc(sizeof(AB));

    strcpy(Topo->nome,nome);
    Topo->invest = investimento;
    Topo->esq = NULL;
    Topo->dir = NULL;
    Topo->pai = NULL;

    return Topo;
}

void destruir_arvore(pAB atual){
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

/* Funcoes destinadas a impressao*/

p_fila criar_fila() {
    /*Funcao que cria uma fila para a impressao*/
    p_fila f;
    f = malloc(sizeof(Fila));
    f->ini = NULL;
    f->fim = NULL;
    return f;
}

void destruir_lista(p_no lista) {
    /*Funcao que libera a memoria alocada de uma lista ligada*/
    if (lista != NULL) {
        destruir_lista(lista->prox);
        free(lista);
    }
}

void destruir_fila(p_fila f) {
    /*Funcao que libera a memoria alocada de uma Fila*/
    destruir_lista(f->ini);
    free(f);
}

void enfileirar(p_fila f, pAB raiz) {
    /*Funcao que adiciona um novo item ao final da Fila*/
    p_no novo;
    if (raiz != NULL){
        novo = malloc(sizeof(No));

        novo->pessoa = raiz;
        novo->prox = NULL;

        if (f->ini == NULL)
            f->ini = novo;
        else
            f->fim->prox = novo;
        f->fim = novo;
    }
}

void desenfileirar(p_fila f) {
    /*Funcao que retira o item do inicio da Fila*/
    p_no primeiro = f->ini;

    f->ini = f->ini->prox;

    if (f->ini == NULL)
        f->fim = NULL;

    free(primeiro);

}

int nivel(pAB recruta, pAB Topo) {
    /*Funcao que calcluca que nivel da piramide o recruta esta*/
    int conta = 1;
    pAB aux = recruta;

    while(aux != Topo){
        conta++;
        aux = aux->pai; 
    
    }

    return conta;
}


/* Funcoes principais para execucao do exercicio*/

void bonificacao(pAB chefe, pAB recrut) {
    /*Funcao que calcula a bonificacao do recutado dada pelo chefe dele (quem o recrutou)*/
    double bonif;

    bonif = ((10.0)*(recrut->invest))/100.0;

    chefe->invest = chefe->invest - bonif;
    recrut->invest = recrut->invest + bonif;

}

void dois_recrutados(pAB chefe, pAB Topo) {
    /*Funcao que faz o calculo da remuneracao adquirida para quem conseguiu recrutar duas pessoas e seus consequentes
    recrutadores em ate 5 niveis da piramide acima dele*/

    double x , y , z;
    pAB aux = chefe;

    if (chefe->esq != NULL && chefe->dir != NULL){
        x = 6*(chefe->esq->invest)/100.0;
        y = 6*(chefe->dir->invest)/100.0;

        chefe->esq->invest = chefe->esq->invest - x;
        chefe->dir->invest = chefe->dir->invest - y;
        chefe->invest = chefe->invest + x + y;

        for( int i = 1; i < NIV ; i++)
            if( aux != Topo) {
                z = (6 - i)*(aux->invest)/100.0;

                aux->invest = aux->invest - z;
                aux->pai->invest = aux->pai->invest + z;

                aux = aux->pai;
            
            }
    }

}

pAB inserir(pAB atual, char nome[MAX], char empregado[MAX], int dinheiro, pAB Topo) {
    /*Funcao que cria um novo membro e o adiciona na arvore , calculando as bonificacoes e possivel remuneracao.
    Devolvendo um ponteiro para o Topo da piramide de forma recursiva, pois ao alterar uma parte da arvore todas as 
    outras partes tem que ser  "atualizadas" para retornar o ponteiro para o topo*/

    pAB novo;

    if(atual == NULL)
        return NULL;

    if (strcmp(atual->nome,nome) == 0){

        novo = malloc(sizeof(AB));

        strcpy(novo->nome,empregado);
        novo->invest = dinheiro;
        novo->dir = NULL;
        novo->esq = NULL;
        novo->pai = atual;

        if(atual->esq == NULL)
            atual->esq = novo;
        else
            atual->dir = novo;

        bonificacao(atual, novo);
        dois_recrutados(atual, Topo);
        
        return atual;
    }

    atual->esq = inserir(atual->esq, nome, empregado, dinheiro, Topo);
    atual->dir = inserir(atual->dir, nome, empregado, dinheiro, Topo);

    return atual;
}

void imprimir_piramide_atual(pAB Topo){
    /*Funcao que printa os investimentos das pessoas, percorrendo os nós em largura
    (necessidade da implementacao de uma fila)*/

    p_fila f;
    p_no raiz;
    int conta = 0, aux;

    f = criar_fila();
    enfileirar(f, Topo);

    while(f->ini != NULL) {
        raiz = f->ini;

        aux =  nivel(raiz->pessoa,Topo);

        if( aux != conta) {
            printf("\n");
            printf("Nivel %d: ",aux);
            conta = aux;
        
        }
       
        if (raiz != NULL) {
            enfileirar(f, raiz->pessoa->esq);
            enfileirar(f, raiz->pessoa->dir);
            printf("[%s %0.2f] ", raiz->pessoa->nome,raiz->pessoa->invest);
        }
        desenfileirar(f);
    }
    printf("\n");
    destruir_fila(f);
}


/* Execucao das funcoes e leitura das entradas*/

int main(){

    /* Declaracao de variaveis*/
    char chefe[MAX], acao[8], empregado[MAX], inicio[5], nome_topo[MAX];
    int dinheiro, investimento;
    pAB Topo;


    /*Leitura do Topo e criacao da arvore*/
    scanf("%s %s %d",inicio, nome_topo, &investimento);

    Topo = criar_arvore(nome_topo, investimento);
    imprimir_piramide_atual(Topo);
    

    /*Leitura dos demais recrutados e execucao das contas de bonificacoes e beneficios por recrutar dois membros*/
    while(scanf("%s %s %s %d", chefe, acao, empregado, &dinheiro) != EOF) {

        Topo = inserir(Topo, chefe, empregado, dinheiro, Topo);

        imprimir_piramide_atual(Topo);
    }
    
    /*Liberacao da memoria a locada*/
    destruir_arvore(Topo);

}
