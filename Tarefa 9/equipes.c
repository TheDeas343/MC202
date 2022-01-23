#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int altura;
    struct No* esquerda;
    struct No* direita;
} No;


typedef struct No* p_no;

/* Definiçao das FUNÇÔES*/

p_no criar_lista_circular () {
    /*Criando uma lista circular*/
    return NULL;
}

p_no adicionar_jogador (p_no circulo, p_no novo) {
    /* Adiciona um jogador a direita do outro jogador em forma de uma
    lista circular duplamente ligada*/

    if(circulo == NULL){
        novo->direita = novo;
        novo->esquerda = novo;
        circulo = novo;
    } else {
        novo->direita = circulo;
        novo->esquerda = circulo->esquerda;
        circulo->esquerda->direita = novo;
        circulo->esquerda = novo;

    }
    return circulo;

}

p_no retirar_jogador(p_no circulo, p_no jogador){
    /* Retira um jogador da lista duplamente ligada */

    if(circulo == circulo->direita){
        return NULL;
    }

    jogador->esquerda->direita = jogador->direita;
    jogador->direita->esquerda = jogador->esquerda;

    if (jogador == circulo) 
        circulo = jogador->direita;
    
    return circulo;
            
}

p_no Equipe_1(p_no *circulo, p_no equipe1, int dado){
    /*Seleciona um jogador no sentido anti-horario e o retira da lista circulo (original)
    o adicionando em uma lista da equipe 1.*/
    

    p_no atual = *circulo;

    for( int i = 0; i < dado-1; i++)
        atual = atual->esquerda;

    *circulo = retirar_jogador(*circulo,atual);
    equipe1 = adicionar_jogador( equipe1,atual);
    

    return equipe1;
}

p_no Equipe_2(p_no *circulo, p_no equipe2, int dado){
    /*Seleciona um jogador no sentido horario e o retira da lista circulo (original)
    o adicionando em uma lista da equipe 2.*/

    p_no atual = *circulo;

    for( int i = 0; i < dado-1; i++)
        atual = atual->direita;

    *circulo = retirar_jogador(*circulo,atual);
    equipe2 = adicionar_jogador( equipe2,atual);
    

    return equipe2;
}

void imprimir_destruir(p_no lista){
    /* Funcao recursiva que seleciona o jogador mais baixo da lista, imprime sua altura e 
    libera a memoria alocada por ele*/

    p_no atual, menor;
    
    /*Selecionando o jogador de menor altura*/
    menor = lista;
    for (atual = lista->direita; atual != lista; atual = atual->direita){
        if(atual->altura < menor->altura)
            menor = atual;
        }
    
    /*Imprimindo sua altra*/
    if(lista != lista->direita)
        printf("%d ",menor->altura);
    else
        printf("%d\n",menor->altura);

    /*Liberar o espaco alocado retirando este jogador da lista*/
    lista = retirar_jogador(lista, menor);
    free(menor);

    /*Chamada recursiva*/
    if(lista != NULL)
        imprimir_destruir(lista);
    
}


/*Leitura das entradas e execucao das funcoes*/
int main() {
    /*Declaracao das variaveis*/
    p_no circulo, equipe1 , equipe2, novo;
    int n_jogadores, altura, dado, i=0;

    /*Inicializacao das listas*/
    circulo = criar_lista_circular();
    equipe1 = criar_lista_circular ();
    equipe2 = criar_lista_circular ();

    /*Leitura e Formacao da lista com os jogadores alocando memoria*/
    scanf("%d",&n_jogadores);

    for( int i = 0; i < n_jogadores; i++){
        scanf("%d",&altura);
    
        novo = malloc(sizeof(No));
        novo->altura = altura;

        circulo = adicionar_jogador(circulo,novo);
    }

    /* Formacao da primeira e segunda equipe, levando em consideracao que 
    pode haver um numero impar de jogadores*/
    while (i < n_jogadores) {
        scanf("%d",&dado);
        equipe1 = Equipe_1(&circulo, equipe1, dado);
        i++;

        if( i < n_jogadores){
            scanf("%d",&dado);
            equipe2 = Equipe_2(&circulo, equipe2, dado);
            i++;
        }
    
    }
    
    /*Impressao das alturas em ordem crescente e liberacao da memoria alocada*/
    imprimir_destruir(equipe1);
    imprimir_destruir(equipe2);

    
    
}

