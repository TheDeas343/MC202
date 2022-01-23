#include <stdio.h>
#include <stdlib.h>

#define MAX 31 /*Numero max de caracteres por nome*/
#define AT 6 /* Numero de atributos do RPG*/

/* Implementação do Grafo*/

typedef struct Cela {
    char nome[MAX];
    int nvls[AT];
} Cela;

typedef Cela* p_cela;

typedef struct Grafo {
    int **adj;
    int n;
} Grafo;

typedef Grafo* p_grafo;


/* Fucnoes bases do Grafo*/

p_grafo criar_grafo(int N){
    /*Funcao que cria um Grafo de Matriz de Adjacencia*/

    p_grafo G = malloc(sizeof(Grafo));
    G->n = N;
    G->adj = malloc(N * sizeof(int*));

    for(int i = 0; i < N; i++)
        G->adj[i] = calloc(N, sizeof(int));
    
    return G;
}

void destruir_grafo(p_grafo G) {
    /*Funcao que liberar a memoria alocada de um Grafo de Matriz de Adjacencia*/

    for (int i = 0; i < G->n; i++)
        free(G->adj[i]);
    free(G->adj);
    free(G);
}


/*Funcoes de leitura das Entradas*/

Cela adicionar_celas() {
    /*Funcao que le as entradas das celas, seu nome e um vetor com os viveis dos atributos,
    adicionando entao em um vetor de Celas*/

    Cela Cela;

    scanf("%s", Cela.nome);

    for(int j = 0; j < AT; j++)
        scanf("%d", &Cela.nvls[j]);


    return Cela;
}

int comparar_Vetor(int *v1, int *v2) {
    /* Funcao que compara dois vetores de int, retorna 1 se sao iguais e 0 se forem diferentes*/
    for(int j = 0; j < AT; j++)
        if (v1[j] != v2[j])
            return 0;
    return 1;

}

int adicionar_cela_inicial(p_cela Celas, int N) {
    /*Funcao que le as entradas dos jogadores e seus atributos, e armazena em um vetor de ints 
    (cada int significa o indice do vetor de Celas)  relacionando a cela de inicio desse jogador
    (Como o jogador sempre comeca em um cela, entao a funcao nunca retornara -1)
    */

    char nome[MAX];
    int nvls[AT];

    scanf("%s",nome);

    for(int j = 0; j < AT; j++)
        scanf("%d", &nvls[j]);
    
    for(int i = 0; i < N; i++)
        if( comparar_Vetor(nvls, Celas[i].nvls)) 
            return i;
    return -1;
}


/* Funcao de formacao do grafo baseado na tarefa*/

int desafio(p_cela C, p_grafo G, int u, int v ){
    /*Funcao que verifica se é possivel passar de uma cela para outra, contando que o jogador na cela conseguira ganhar
    um ponto no atributo conveninete para que tente passar.
        -Retorna 0 se ele nao conseguir ( mais de um atributo necessitando 1 ponto ou atributos necessitando mais de 1 ponto)
        -Retorna 1 se conseguir.
    */

    int conta_um = 0, aux;

    for( int i = 0; i < AT; i++) {
            aux = C[v].nvls[i]  -C[u].nvls[i];

            if(aux == 1)
                conta_um++;
            if(aux > 1 || conta_um > 1)
                return  0;
    }
    return 1;
    

}

void acessos_celas(p_cela C, p_grafo G) {
    /* Funcao que analisa a possibilidade de passar de uma cela para outra:
        - Se for posivel , entao isso representara uma seta no grafo (1 na matriz de adjacencia)
        - Se nao for entao nao havera seta, indicando que nao é possivel passar daquela cela para a outra 
        (0 na matriz de adjacencia)
    */
    for(int i = 0; i < G->n; i++)
        for(int j = 0; j < G->n; j++) {
            if( i != j)
                G->adj[i][j] = desafio(C, G, i, j);   

            else
                G->adj[i][j] = 1; /* O jogador pode ficar parado por uma rodada*/
        }
}


/* Fucoes relacionadas a simulacao das duas rodadas e Impressao das celas finais*/

int duas_rodadas(p_grafo G, int c, int p) {
    /*Funcao que analisa os 3 caos da funcao de celas_finais*/

    if( c == p || G->adj[p][c] == 1) /* Caso 1 e 2, estar na cela ou ser vizinho da cela*/
        return 1;

    for(int f = 0; f < G->n; f++) /* Caso 3, ter um vizinho que é vizinho da cela*/
        if(f != c && G->adj[p][f] == 1)
            if(G->adj[f][c] == 1)
                return 1;
    return 0;

}

void celas_finais(p_grafo G, p_cela C, int* P, int M) {
    /* Funcao que analisa cela por cela, se esta poderia ser a cela final de todos os jogadores
        Esta funcao analisa jogador por jogador de acordo com sua cela inicial, se este poderia terminar na cela em questao:

            Caso 1- Se ele comecar nessa cela, entao pode ficar parado até o final.
            Caso 2- Se ele for vizinho dessa cela de acordo com o Grafo criado  (pode ir para aqla cela depois de passar no desafio) 
        e ficar parado na proxima rodada.
            Caso 3- Ou entao será visitado seus vizinhos e os vizinhos desses vizinhos na procura da cela em questao.

        Imprimindo as celas que todos os jogadores conseguem estar no final após duas rodadas.
        Ou no caso contrario imprimindo nao ser possivel em nenhuma cela.
    */
    int continua, imprimiu = 0;

    for(int c = 0 ; c < G->n; c++) {
        continua = 1;
        for( int p = 0; p < M; p++)
            if(duas_rodadas(G, c, P[p]) == 0) {
                continua = 0;
                break;
            }
        if(continua != 0){
            imprimiu = 1;
            printf("%s\n", C[c].nome);
        }
    
    }

    if(imprimiu == 0)
        printf("Impossivel terminar em duas rodadas.\n");

}


/*Execucao dos codigos*/

int main() {
    int N, M, * pers;
    p_cela Celas;
    p_grafo Grafo;

    
    /*Entradas das celas*/

    scanf("%d", &N);
    Celas = malloc(N * sizeof(Cela));

    for( int i = 0; i < N; i++)
        Celas[i] = adicionar_celas();


    /*Entradas dos personagens com suas celas iniciais*/

    scanf("%d", &M);
    pers = malloc(M*sizeof(int));
    
    for( int i = 0; i < M; i++)
        pers[i] = adicionar_cela_inicial(Celas, N);


    /* Criando o grafo da interligação das celas ao passar no desafio*/
    
    Grafo = criar_grafo(N);
    acessos_celas(Celas, Grafo);


    /*Achando as celas finais após duas rodadas*/

    celas_finais(Grafo, Celas, pers, M);


    /* Liberarando a memoria alocada*/

    free(Celas);
    free(pers);
    destruir_grafo(Grafo);
}
