#include <stdio.h>
#include <string.h>
#include "planejar.h"

#define MAX 100
#define OP 10

int main() {

    Voo  voos[MAX];
    int qtd_voos=0, x;
    char operacao[OP];
    
    x = 0;
    while (x == 0) {
        memset(operacao,0,sizeof(operacao));
        scanf("%s",operacao);

        if(strcmp(operacao,"registrar")==0){
            registrar( voos, qtd_voos);
            qtd_voos++;
        } else if (strcmp(operacao,"alterar")==0){
            alterar(voos, qtd_voos);

        } else if (strcmp(operacao,"cancelar")==0){
            cancelar( voos, qtd_voos);
        } else {
            planejar( voos,  qtd_voos);
            x = 1;
        }
    } return 0;
}
    
