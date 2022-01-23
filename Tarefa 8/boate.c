#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fila.h"

int main() {

    /* Declaracao de variaveis*/
    p_no inicio, lanterna, pessoa;
    int RG, entrou = 1;
    char profissao[MAX], vacina[VAX];

    /*Inicialiacao da lista*/
    inicio = criar_lista();

    /*Leitura das entradas e execucao das funcoes*/
    while(scanf("%d %s %s",&RG,profissao,vacina) != EOF) {

        /* Alocacao da memoria*/
        pessoa = malloc(sizeof(No));

        /*Atribuicao dos inputs para as caracteristicas do Nó*/
        pessoa->RG = RG;
        strcpy(pessoa->profissao , profissao);
        strcpy(pessoa->vacina , vacina);
        
        /*Adicionando ou nao a pessoa na fila*/
        inicio = adicionar_pessoa( inicio, lanterna, pessoa, &entrou);

        /*Verifica se a pessoa entrou na fila e da a lanterna caso tenha entrado*/
        if( entrou != 0) {
            lanterna = pessoa;
        
        }
        
    }

    /*Impressao da fila */
    imprime(inicio);

    /*Liberaçao do espaço alocado*/
    destruir_lista(inicio);

}
