#include "fila.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

p_no criar_lista() {
    /*Funcao que cria uma lista ligada*/
    return NULL;
}

void destruir_lista(p_no lista) {
    /*Funcao que liberta a memoria alocada em uma lista ligada*/
    if (lista != NULL) {
        destruir_lista(lista->prox);
        free(lista);
    }
}

int verificar_profissao(p_no pessoa) {
    /*Funcao que verifica as "profissoes/ocupacoes" de acordo com os 3 fenomenos descritos.
    Retorna:
        1 para coach,ex-bbb, herdeiro, filho-politico ou youtuber-financas.
        2 para funcionarios.
        3 para fiscais.
        0 para as demais profissoes.
    */

    char prof[MAX] ;

    strcpy(prof,pessoa->profissao);

    if (strcmp(prof,"coach") == 0 || strcmp(prof,"ex-bbb")  == 0 || 
        strcmp(prof,"filho-politico")  == 0 || strcmp(prof,"herdeiro")  == 0 || 
        strcmp(prof,"youtuber-financas")  == 0)
        return 1;

    else if (strcmp(prof,"funcionario") == 0)
        return 2;
    
    else if (strcmp(prof,"fiscal") == 0)
        return 3;

    return 0;
}

p_no fenomeno_0(p_no inicio, p_no pessoa, p_no lanterna) {
    /* Adiciona a pessoa atras de quem estiver com a lanterna*/
    
    pessoa->prox = lanterna->prox;
    lanterna->prox = pessoa;

    return inicio;
}

p_no fenomeno_1(p_no inicio, p_no pessoa) {
    /* Fenomeno 1 :
        Pessoas "famosas" entram no comeco da fila 
    */

    pessoa->prox = inicio;
    return pessoa;
}

p_no fenomeno_2(p_no inicio, p_no pessoa) {
    /* Fenomeno 2:
        Funcionarios por nao pagarem entram no final da fila
    */

    p_no atual;

    for (atual = inicio; atual->prox != NULL; atual = atual->prox);

    pessoa->prox = atual->prox;
    atual->prox = pessoa;

    return inicio;

}

p_no fenomeno_3(p_no inicio, p_no pessoa, p_no lanterna) {
    /* Fenomeno 3:
        Fiscais retiram da fila as pessoas que estiverem atras dele que nao estejam vacinadas até encontrar um vacinada ou acabar a fila.
    */
    p_no atual;

    for(atual=lanterna->prox ; atual != NULL && strcmp(atual->vacina,"nao-vacinado") == 0 ; atual = atual->prox);

    pessoa->prox = atual;
    lanterna->prox = pessoa;
    
    return inicio;
}

p_no adicionar_pessoa(p_no inicio, p_no lanterna, p_no pessoa, int* aux) {

    /*Funcao que adicona uma nova pessoa a fila baseada na sua profissao/ocupacao.
    Dividida em 3 etapas:
        Etapa 0- Se a lista estiver vazia essa inicia a fila.

        Etapa 0.5- Verificar se a pessoa pode entrar na fila devido a possibilidade de fiscas de vacinacao.
                alterando a variavel auxiliar para que essa pessoa nao pegue a lanterna.

        Etapa 1- Subdividida em 4 fenomenos de acordo com a profissao/ocupacao da pessoa.
    
        */ 
 
    int verif ;
    *aux = 1;
    
    /*Etapa 0*/
    if(inicio == NULL) {
        pessoa->prox = inicio;
        return pessoa;
    }
    
    else{

    /*Etapa 0.5*/
        verif = verificar_profissao(pessoa);
        
        if (verif != 1 && strcmp(lanterna->profissao,"fiscal") == 0 && strcmp(pessoa->vacina,"vacinado") != 0){
            free(pessoa);
            *aux=0;

        } else {
                
    /*Etapa 1*/
            if (verif == 1)
                inicio = fenomeno_1(inicio, pessoa);

            else if (verif == 2) 
                inicio = fenomeno_2(inicio, pessoa);

            else if (verif == 3) 
                inicio = fenomeno_3(inicio, pessoa,lanterna);

            else 
                inicio = fenomeno_0(inicio, pessoa,lanterna);
            
        }
        return inicio;
    }

}

void imprime(p_no lista) {
    /*Funcao que imprime a fila na ordem final*/

    p_no atual;
    for (atual = lista; atual != NULL; atual = atual->prox)
        printf("%d %s %s\n",atual->RG, atual->profissao,atual->vacina);
}
