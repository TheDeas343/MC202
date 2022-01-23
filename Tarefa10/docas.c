#include "lib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {

    /*Declarando as variaveis*/

    p_fila Fila;
    int n_docas, capac_docas, n_navios, i, acao = 0, contagem = 0;
    p_pilha Docas;
    p_navio aux;

    Fila = criar_fila();

    scanf("%d",&n_docas);
    scanf("%d",&capac_docas);
    scanf("%d",&n_navios);

    Docas = criar_vetor_pilhas( capac_docas, n_docas);
    

    for(  i = 0; i < n_navios; i++)
        adicionar_navio(Fila);

    /*Fixa um navio como auxiliar e analisa se algum descarregamento ou carregamento foi feito, 
    caso todos os navios passem sem fazer uma ação, entao é impossivel esvaziar a fila*/

    aux = Fila->ini;

    while(Fila->ini != NULL) {
        atracar( Docas, Fila, n_docas, capac_docas, &acao, &contagem);
    
        if(acao == 0 ){
            if( contagem == navios_na_fila(Fila) && Fila->ini == aux){
                printf("ALERTA: impossivel esvaziar fila, restam %d navios.", contagem);
                break;
            }
        }
    
        else {
            contagem = 0;
            acao = 0;
            aux = Fila->ini;
        }
    
    }

    /*Liberar a memória alocada*/

    destruir_fila(Fila);
    for(int i = 0; i < n_docas;i++)
        free(Docas[i].v);
    free(Docas);
    
}
