#include "lib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Funcoes bases*/

p_fila criar_fila() {
    /*Inicializa uma fila*/

    p_fila f;
    f = malloc(sizeof(Fila));
    f->ini = NULL;
    f->fim = NULL;
    return f;
}

p_pilha criar_vetor_pilhas( int capac_docas, int n_docas){
    /*Cria um vetor para armazenar as docas, representadas como pilhas*/

    p_pilha Docas;
    Docas = malloc(n_docas * sizeof(Pilha));

    for( int i = 0; i < n_docas; i++) {
        (Docas[i]).v = malloc(capac_docas  * sizeof(Conteiner));
        (Docas[i]).topo = 0;
    }
    
    return Docas;
}

void adicionar_navio(p_fila Fila) {
    /*Adiciona um novo onavio a fila, com suas caracteristicas:
        Nome, Objetivo, Tipo de carga e quantidade de conteineres. */

    p_navio navio;
    int  qtd;
    char nome[MAX], objetivo[OBJ], carga[MAX]; 

    scanf("%s %s %s %d", nome, objetivo, carga, &qtd);

    navio = malloc(sizeof(Navio));

    strcpy(navio->nome,nome);
    strcpy(navio->objetivo,objetivo);
    strcpy(navio->carga,carga);
    navio->qtd = qtd;
    navio->prox = NULL;

    if(Fila->ini == NULL)
        Fila->ini = navio;

    else
        Fila->fim->prox = navio;

    Fila->fim = navio;
}

void destruir_lista(p_navio navio) {
    /*Funcao que libera o espaco alocado de uma lista*/

    if (navio != NULL) {
        destruir_lista(navio->prox);
        free(navio);
    }
}

void desenfileira( p_fila Fila) {
    /*Funcao que retira o navio da fila , pois conclui todo seu objetivo*/

    p_navio primeiro = Fila->ini;
    
    Fila->ini = Fila->ini->prox;

    if (Fila->ini == NULL)
        Fila->fim = NULL;

    free(primeiro); 
    
}

void destruir_fila( p_fila Fila) {
    /*Funcao que liberado a memoria alocada em uma fila*/
    destruir_lista(Fila->ini);
    free(Fila);
}

int navios_na_fila(p_fila Fila) {
    /*Funcao que faz a contagem de navios restantes na fila*/

    p_navio atual;
    int n = 0;

    for( atual = Fila->ini ; atual != NULL; atual = atual->prox)
        n++;
    return n;
}



/* Funcoes principais para a execucao do desafio*/

void descarregar(p_pilha Docas, p_fila Fila, int n_docas, int capac_docas, int* acao, int* contagem) {
    /*Funcao que pega a primeira doca disponivel e descarrega o max de conteiner que o o navio conseguir e que a doca suporta.
    Imprimindo a acao executada pelo navio.
    Ao final, move ele para o final da fila caso ainda tenha conteineres, se não o navio é retirado da fila*/

    int descarregou = 0, conteineres = 0;

    *contagem = *contagem +1;

    for(int j = 0; j < n_docas; j++){

        if ( (Docas[j]).topo < capac_docas && descarregou == 0){

            while((Docas[j]).topo < capac_docas) {

                if(Fila->ini->qtd > 0){

                    strcpy(((Docas[j].v)[Docas[j].topo]).carga, Fila->ini->carga);
                    Fila->ini->qtd--;
                    Docas[j].topo++;

                    descarregou = 1;
                    conteineres++;

                }
                else
                    break;

            }
            
            if(conteineres > 0 ){
                *acao = 1;
                printf("%s descarrega %s doca: %d conteineres: %d\n", Fila->ini->nome, Fila->ini->carga, j, conteineres);
            }
        }

    }
    if ( Fila->ini->qtd > 0)
        final_da_fila(Fila); 
    else
        desenfileira(Fila);

}

void carregar(p_pilha Docas, p_fila Fila, int n_docas, int capac_docas, int* acao, int* contagem) {
    /*Funcao que pega a primeira doca que tenha o primeiro conteiner que o navio quer carregar e assim carrega o max que for possivel.
    Imprimindo a acao executada pelo navio.
    Ao final, move ele para o final da fila caso ainda tenha conteineres, se não o navio é retirado da fila*/

    int carregou = 0, conteineres = 0;

    *contagem = *contagem +1;

    for(int j = 0; j < n_docas; j++){

        if ( (Docas[j]).topo != 0 && carregou == 0){

             while((Docas[j]).topo != 0) {

                if(Fila->ini->qtd > 0 && strcmp((Docas[j].v)[(Docas[j].topo)-1].carga, Fila->ini->carga) == 0){

                    Fila->ini->qtd--;
                    Docas[j].topo--;

                    carregou = 1;
                    conteineres++;

                }
                else
                    break;
             }
            if(conteineres > 0 ) {
                *acao = 1;
                printf("%s carrega %s doca: %d conteineres: %d\n", Fila->ini->nome, Fila->ini->carga, j, conteineres);
            }
        }
    }

    if (Fila->ini->qtd > 0)
        final_da_fila(Fila);
    else
        desenfileira(Fila);

}

void atracar(p_pilha Docas, p_fila Fila, int n_docas, int capac_docas, int* acao, int* contagem) {
    /* Funcao que analisa o objetivo do navio e executa o processo*/

    if(strcmp(Fila->ini->objetivo,"descarrega") == 0)
        descarregar( Docas, Fila, n_docas, capac_docas, acao, contagem);

    else 
        carregar( Docas, Fila, n_docas, capac_docas,acao, contagem);
        
}

void final_da_fila( p_fila Fila) {
    /*Funcao que pega o primeira navio da fila e o move para o final dela*/

    p_navio primeiro = Fila->ini;

    Fila->ini = Fila->ini->prox; 

    Fila->fim->prox = primeiro;
    Fila->fim = primeiro;
    
    primeiro->prox = NULL; 

}
