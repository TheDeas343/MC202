#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 101 /*Tamanho max dos enderecos*/
#define IP 16 /*tamanho max dos IP'S*/

enum Cor {VERMELHO , PRETO};

/* ARVORE BINARIA DE BUSCA BALANCEADA : RUBRO-NEGRA ESQUERDISTA*/

typedef struct No {

    char dom[MAX]; 
    char ip[IP]; 
    int conta;
    enum Cor cor;

    struct No *esq, *dir;
} No;

typedef No* p_no;


/*Funçoes bases da ABB rubro-negra esquerdista*/

int Vermelho(p_no NO) {
    if (NO == NULL)
        return 0;
    return NO->cor == VERMELHO;
}

int Preto(p_no NO) {
    if (NO == NULL)
        return 1;
    return NO->cor == PRETO;
}

p_no rotaciona_esquerda(p_no raiz) {
    /*Funcao que rotaciona um no com suas subarvores para a esquerda*/
    p_no aux = raiz->dir;

    raiz->dir = aux->esq;
    aux->esq = raiz;
    aux->cor = raiz->cor;

    raiz->cor = VERMELHO;

    return aux;
}

p_no rotaciona_direita(p_no raiz) {
    /*Funcao que rotaciona um no com suas subarvores para a direita*/
    p_no aux = raiz->esq;

    raiz->esq = aux->dir;
    aux->dir = raiz;
    aux->cor = raiz->cor;

    raiz->cor = VERMELHO;

    return aux;
}

void sobe_vermelho(p_no raiz) {
    /* Nos de ABB Rubro-Negras esquerdistas nao tem dois filhos vermelhos, passa o vermelho pro pai, nao altera a altura-negra*/

    raiz->cor = VERMELHO;
    raiz->esq->cor = PRETO;
    raiz->dir->cor = PRETO;
}


/*Função de inserção e busca da ABB de DOMINIOS*/

p_no inserir_DOM_rec(p_no raiz, char dom[MAX], char ip[IP]) {
    /* Funcao que insere em uma ABB rubro-negra esquerdista mantendo suas prorpiedades
    ABB de Dominios, apenas com os enderecos e o correspondente IP*/

    p_no novo;

    if (raiz == NULL) {
        novo = malloc(sizeof(No));

        novo->esq = novo->dir = NULL;
        strcpy(novo->dom, dom);
        strcpy(novo->ip, ip);
        novo->cor = VERMELHO;

        return novo;
    }
    /*Enderecos que forem menores que do o nó ficam a esquerda*/

    if (strcmp(dom, raiz->dom) < 0 )
        raiz->esq = inserir_DOM_rec(raiz->esq, dom, ip);
    else
        raiz->dir = inserir_DOM_rec(raiz->dir, dom, ip);

    /* corrigir a ABB */
    if (Vermelho(raiz->dir) && Preto(raiz->esq))
        raiz = rotaciona_esquerda(raiz);
    if (Vermelho(raiz->esq) && Vermelho(raiz->esq->esq))
        raiz = rotaciona_direita(raiz);
    if (Vermelho(raiz->esq) && Vermelho(raiz->dir))
        sobe_vermelho(raiz);
    return raiz;
}

p_no inserir_DOM(p_no raiz, char dom[MAX], char ip[IP]) {
    /*Funcao que insere na ABB de DOMINIOS e mantem o no da raiz preto*/
    raiz = inserir_DOM_rec(raiz, dom, ip);
    raiz->cor = PRETO;
    return raiz;
    }

/* Funcoes de Impressao do codigo */ 

int buscar_imprimir(p_no raiz, char ip[MAX], char dom[MAX]){
    /*Funcao de busca e impressao:
        Se o dominio for achado, é printado o IP correspondente e a funcao retorna 1
        Caso nao ache retorna 0;   
    */
    int aux;
    
    if(raiz != NULL) {
        aux = strcmp(dom, raiz->dom);

        if( aux == 0) {
            printf("ACCEPTED %s FROM %s RESPOND %s\n", dom, ip, raiz->ip);
            return 1;
        }
        else{
            if( aux < 0)
                return buscar_imprimir(raiz->esq, ip, dom);
            else    
                return buscar_imprimir(raiz->dir, ip, dom);
        
        }
    }
    return 0;
}

void imprimir(p_no raiz, char dom[MAX], p_no Dominios) {

    /*Funcao que verifica se o o usuario passou do limite de acessos, se nao a funcao busca pelo IP correspondente do dominio, 
    caso nao ache, entao a funcao imprime que nao achou*/
    int aux ;
    
    if(raiz->conta <= 0)
        printf("FORBIDDEN %s FROM %s\n", dom, raiz->ip);    
    else{
        aux = buscar_imprimir(Dominios, raiz->ip, dom);
        if( aux == 0)
            printf("NOTFOUND %s FROM %s\n",dom, raiz->ip);
        }
        
}


/*Funcao de inserção para a arvore de IP'S de USUARIOS*/

p_no inserir_IP_rec(p_no raiz, char dom[MAX], char ip[IP], int u, p_no Dominios) {
    /* Funcao que insere em uma ABB rubro-negra esquerdista mantendo suas prorpiedades
    ABB de IPS de USUARIOS, com ip do usuario e a contagem de acessos
    Funcao ja imprime o ip correspondete, se o dominio nao existe ou se o usuario passou do numero de acessos*/

    p_no novo;
    int aux;

    if (raiz == NULL) {

        novo = malloc(sizeof(No));

        novo->esq = novo->dir = NULL;
        novo->conta = u;
        strcpy(novo->ip, ip);

        imprimir(novo, dom, Dominios);

        novo->cor = VERMELHO;

        return novo;
    }

    /*IP's que forem menores que o IP do nó ficam a esquerda*/

    aux = strcmp(ip, raiz->ip);

    if ( aux == 0 ){
        raiz->conta = raiz->conta - 1;
        imprimir(raiz, dom, Dominios);
    }
    else if (aux < 0 )
        raiz->esq = inserir_IP_rec(raiz->esq, dom, ip, u, Dominios);
    else
        raiz->dir = inserir_IP_rec(raiz->dir, dom, ip, u, Dominios);

    /* corrigir a ABB */
    if (Vermelho(raiz->dir) && Preto(raiz->esq))
        raiz = rotaciona_esquerda(raiz);
    if (Vermelho(raiz->esq) && Vermelho(raiz->esq->esq))
        raiz = rotaciona_direita(raiz);
    if (Vermelho(raiz->esq) && Vermelho(raiz->dir))
        sobe_vermelho(raiz);

    return raiz;
}

p_no inserir_IP(p_no raiz, char dom[MAX], char ip[IP], int u, p_no Dominios) {


    /*Funcao que insere na ABB de IPS e mantem o no da raiz preto*/

    raiz = inserir_IP_rec(raiz, dom, ip, u, Dominios);
    raiz->cor = PRETO;
    return raiz;
}


/*Liberar Memoria alocada*/

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


/* Leitura das entradas e execução do codigo*/

int main() {
    /* Declaracao das variaveis*/
    p_no Dominios = NULL, Usuarios = NULL;
    int u, n, m;
    char dom[MAX], ip_dom[IP], dom_acess[MAX], user[IP], inutil1[4], inutil2[5]; /* Variaveis inuteis para a leitura de trechos da entrada descartaveis*/

    /*Criacao da ABB de DOMINIOS*/
    scanf("%d %d", &u, &n);

    for( int i = 0; i < n ; i++){
        scanf("%s %s",dom, ip_dom);
        Dominios = inserir_DOM(Dominios, dom, ip_dom);
    }

    /*Criacao da ABB de IPS de USUARIOS e execucao das impressoes*/
    scanf("%d",&m);

    for( int j = 0; j < m ; j++){
        scanf("%s %s %s %s", inutil1,dom_acess,inutil2, user);
        Usuarios = inserir_IP(Usuarios, dom_acess, user, u, Dominios);
    }

    /* Liberacao da memoria alocada*/
    destruir_arvore(Dominios);
    destruir_arvore(Usuarios);

    return 0;
}
