#include <stdio.h>
#include <stdlib.h>

#define PAI(i) ((i - 1)/2)
#define F_ESQ(i) (2*i + 1) /*Filho esquerdo de i*/
#define F_DIR(i) (2*i + 2) /*Filho direito de i*/


/*Implementacao da Fila de Prioridade- Heap de Maximo*/

typedef struct Pacote {
    int id;  /*Identificador*/
    int chave; /*Prioridade*/
    int plus; /*Incremento*/
} Pac;

typedef struct {
    Pac *v; /*Vetor de Pacotes*/
    int n, tam; /*N = numero de espacos utilizados do vetor e Tam = tamanho do vetor*/
} FP; 

 typedef FP * p_fp;

p_fp criar_FP(int tam) {
    /*Funcao que cria uma fila de prioridade com vetores*/
    p_fp Rot = malloc(sizeof(FP));

    Rot->v = malloc(tam * sizeof(Pac));
    Rot->n = 0;
    Rot->tam = tam;

    return Rot;
}

void destruir_FP(p_fp FP) {
    /*Funcao que libera a memoria alocada de uma Fila de Prioridade*/
    free(FP->v);
    free(FP);
}


/*Funcoes Bases de uma Fila de Prioridade*/

void troca(Pac *a, Pac *b) {
    /*Funcao que faz a troca de dois itens nos vetores*/
    Pac t = *a;
    *a = *b;
    *b = t;
}

void desce_no_Heap(p_fp FP, int k) {
    /*Funcao que arruma a Fila de prioridade descendo a chave pra uma posicao que mantenha a propriedade da Fila*/
    int maior_filho;

    if (F_ESQ(k) < FP->n) {
        maior_filho = F_ESQ(k);

        if (F_DIR(k) < FP->n && FP->v[F_ESQ(k)].chave < FP->v[F_DIR(k)].chave)
            maior_filho = F_DIR(k);

        if (FP->v[k].chave < FP->v[maior_filho].chave) {
            troca(&FP->v[k], &FP->v[maior_filho]);
            desce_no_Heap(FP, maior_filho);
        }
    }
}

Pac extrai_MAX(p_fp FP) {
    /* FUncao que extrai e retorna o Max da Fila de Prioridade*/
    Pac Pac = FP->v[0];
    troca( &FP->v[0], &FP->v[FP->n - 1]);
    FP->n--;

    desce_no_Heap(FP, 0);

    return Pac;
}

void sobe_no_Heap(p_fp FP, int k) {
    /*Funcao que sobe uma chave na fila até manter a propriedade de prioridade da chave*/
    if (k > 0 && FP->v[ PAI(k) ].chave < FP->v[k].chave) {

        troca( &FP->v[k], &FP->v[ PAI(k) ]);
        sobe_no_Heap(FP, PAI(k));
    }
}

void insere_HeapMax(p_fp FP, Pac Pac) {
    /* Funcao que insere na Fila de prioridade mantenho suas prioridades*/
    FP->v[FP->n] = Pac;
    FP->n++;

    sobe_no_Heap(FP, FP->n - 1);
}

int fila_cheia(p_fp FP) {
    /*Funcao que verifica se a fila esta cheia
    Retornando 0 nmo caso de estar cheia e 1 no caso contrario
    */
    if(FP->n == FP->tam)
        return 0;
    return 1;
}

Pac novo_pac(int id, int chave, int plus) {
    Pac Pac;
    Pac.id = id;
    Pac.chave = chave;
    Pac.plus = plus;

    return Pac;
}


/*Funcoes Especificas para a execucao do problema*/

void executar_tick(p_fp Rot, int k, int tick) {
    /*Funcao que retira o k maiores pacotes da fila, ou os n maiores em caso do K ser maior que n.
    Imprimindo seu Id sua prioridade e seu incremento do Tick correspondente
    */

    Pac MAX;
    int min;
    printf("\n");
    printf("TICK %d\n", tick);

    if(k < Rot->n)
        min = k;
    else
        min = Rot->n;

    for(int i = 0; i < min; i++) {
        if(Rot != NULL) {
            MAX = extrai_MAX(Rot);
            printf("%d    %d    %d\n", MAX.id, MAX.chave, MAX.plus);
        }

    }
}

void incrementar(p_fp FP) {
    /*Funcao que altera a prioridade ao somar o incremento na chave.
    Necessario apenas observar se o filho tem a chave maior que seu pai, pois o incremento é sempre positivo*/

    for(int i = 0; i < FP->n; i++) {
        FP->v[i].chave = FP->v[i].chave + FP->v[i].plus;
        sobe_no_Heap(FP, i);
    }
}


/* Leitura das Entradas e Execucao do codigo*/

int main() {
    p_fp Rot;
    Pac Pac;
    int k, m, id, pri, incr, tick = 0;

    /*Leitura de entradas e criacao da Fila*/
    scanf("%d %d", &k, &m);
    Rot = criar_FP(m);

    while( scanf("%d %d %d", &id , &pri, &incr) != EOF) {

        /*Execucao principal do codigo*/

        if( id == 0) {
                tick++;
                executar_tick(Rot, k, tick);

                if(Rot != NULL)
                    incrementar(Rot);
        } else {
            if(fila_cheia(Rot) != 0) {
                Pac = novo_pac(id, pri, incr);
                insere_HeapMax(Rot, Pac);
                
            }
        }
    }
    /*Liberação da memoria alocada*/
    destruir_FP(Rot);
}
