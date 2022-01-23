#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 51 /* Tamanho max dos nomes das cidades*/
#define INT_MAX 1000000 /* Simulando o + INFINITO para a funcao DIJKSTRA*/
#define NULO -1 /* Definir um valor de distancia que sempre sera menor que todos os outros*/

#define PAI(i) ((i - 1)/2) /*Pai de i*/
#define F_ESQ(i) (2*i + 1) /*Filho esquerdo de i*/
#define F_DIR(i) (2*i + 2) /*Filho direito de i*/

/* Implementacao do Grafo por Lista de Adjacencia*/

typedef struct No {
    char nome[MAX];
    int pop;
    double dist;
    struct No *prox;
} No;

typedef No * p_no;

typedef struct Grafo {
    int n;
    p_no *adj;
} Grafo;

typedef Grafo * p_grafo;

/* Implementacao d Heap Binario*/

typedef struct {
    double dist;
    int vertice;
} Item;

typedef struct {
    Item *v;
    int n, tam;
} FP;

typedef FP * p_fp;


/* Funcoes bases de Grafos*/

p_grafo criar_grafo(int n) {
    /*Funcao que criar um Grafo com uma Lista de Adjacencia*/
    
    p_grafo G = malloc(sizeof(Grafo));
    G->n = n;
    G->adj = calloc(n, sizeof(p_no));
    
    return G;
}

void destruir_lista(p_no list) {
    /*Funcao que libera a memoria alocada em uma lista ligada*/

    if (list != NULL) {
        destruir_lista(list->prox);
        free(list);
    }
}

void destruir_grafo(p_grafo G) {
    /*Funcao que liberar a memoria alocada em um Grafo de Lista de Adjacencia*/
    
    for (int i = 0; i < G->n; i++)
        destruir_lista(G->adj[i]);

    free(G->adj);
    free(G);
} 



/* Funcoes de inserçao no Grafo*/

p_no inserir_cidade(char nome[MAX], int p) {
    /* Funcao que criar um nó para ser armazenado em um vetor, e poder relacionari o indice com o conteudo do nó*/

    p_no novo ;
    novo = malloc(sizeof(No));
    strcpy(novo->nome,nome);
    novo->pop = p;
    novo->prox = NULL;

    return novo;
}

int indice_vertice(p_no * I, char ini[MAX], int n) {
    /* Funcao que retorna o indice do vertice de um No de um vetor de Nos*/
    for (int i = 0; i < n; i++)
        if( strcmp(I[i]->nome, ini) == 0)
            return i;
    return -1;
}

p_no inserir_na_lista(p_no lista, p_no fim, double dist) {
    /*Funcao que insere um no com peso(distancia) em uma lsita ligada*/

    p_no novo = malloc(sizeof(No));

    strcpy(novo->nome, fim->nome);
    novo->pop = fim->pop;
    novo->dist = dist;
    novo->prox = lista;

    return novo;
}

void inserir_aresta(p_grafo G, char v_ini[MAX], char v_fim[MAX], double dist, p_no* I) {
    /* Funcao que insere os nos vizinhos em um Grafo de Lista Ligada, formando uma aresta (Ida e Volta) */

    int i_ini, i_fim;

    i_ini = indice_vertice(I, v_ini, G->n);
    i_fim = indice_vertice(I, v_fim, G->n);

    G->adj[i_ini] = inserir_na_lista(G->adj[i_ini], I[i_fim], dist);
    G->adj[i_fim] = inserir_na_lista(G->adj[i_fim], I[i_ini], dist);

}



/* Funcoes relacionadas a Fila de Prioridade - Heap Binaria*/

p_fp criar_fp(int tam) {
    /*Funcao que cria uma fila de prioridade com vetores*/
    p_fp Fp = malloc(sizeof(FP));

    Fp->v = malloc(tam * sizeof(Item));
    Fp->n = 0;
    Fp->tam = tam;

    return Fp;
}

void destruir_fp(p_fp FP) {
    /*Funcao que libera a memoria alocada de uma Fila de Prioridade*/
    free(FP->v);
    free(FP);
}

void troca(Item *a, Item *b) {
    /*Funcao que faz a troca de dois itens nos vetores*/
    Item t = *a;
    *a = *b;
    *b = t;
}

void desce_no_Heap(p_fp FP, int k) {
    /*Funcao que arruma a Fila de prioridade descendo a chave pra uma posicao que mantenha a propriedade da Fila*/
    int maior_filho;

    if (F_ESQ(k) < FP->n) {
        maior_filho = F_ESQ(k);

        if (F_DIR(k) < FP->n && FP->v[F_ESQ(k)].dist < FP->v[F_DIR(k)].dist)
            maior_filho = F_DIR(k);

        if (FP->v[k].dist < FP->v[maior_filho].dist) {
            troca(&FP->v[k], &FP->v[maior_filho]);
            desce_no_Heap(FP, maior_filho);
        }
    }
}

void sobe_no_Heap(p_fp FP, int k) {
    /*Funcao que sobe uma chave na fila até manter a propriedade de prioridade da chave*/
    if (k > 0 && FP->v[ PAI(k) ].dist < FP->v[k].dist) {

        troca( &FP->v[k], &FP->v[ PAI(k) ]);
        sobe_no_Heap(FP, PAI(k));
    }
}

void inserir_fp(p_fp FP, int i, int pri) {
    /* Funcao que que insere na fila de prioridade de vetores de itens, com o vertice e sua prioridade que inicia 
    como INT_MAX*/

    Item novo;
    novo.vertice = i;
    
    novo.dist = pri;

    FP->v[FP->n] = novo;
    FP->n++;

    sobe_no_Heap(FP, FP->n - 1);
}

void diminuiprioridade(p_fp FP, int s, int pri) {
    /* Funcao que diminui a prioridade de um no e entao desce ele na fila*/

    for(int j = 0; j <  FP->n; j++)

        if(FP->v[j].vertice == s){
            FP->v[j].dist = pri;
            desce_no_Heap(FP, s);
            break;
        }
}

Item extrai_minimo(p_fp FP){
    /* Funcao que retira o no com menor prioridade da fila, e o substitui pelo no no final do vetor, 
    fazendo o subir para a posicao correta*/

    Item ret = FP->v[0];
    int ind = 0;

    for(int i = 1; i < FP->n; i++)
        if(FP->v[i].dist < ret.dist){
            ret = FP->v[i];
            ind = i;
        }

    FP->v[ind] = FP->v[FP->n - 1];
    sobe_no_Heap(FP, ind);
    FP->n--;

    return ret;
}

double buscar_dist(p_fp FP, int i) {
    /* Funcao que faz a busca na fila de prioridade por um vertice e devolve sua prioridade/distancia*/
    for(int j = 0; j <  FP->n; j++)
        if(FP->v[j].vertice == i)
            return FP->v[j].dist;
    return NULO;
}



/* Funcao principal para o MENOR CAMINHO*/

int * dijkstra(p_grafo G, int s, p_no *I) {
    /* Funcao que calcula o menor caminho entre um vertice S e os demais que ele alcança
    armazenando os pais dos vertices em um vetor.
    Executa essa funcao sempre pegando o vertice com menor distancia dentro da franja que acompanha o vertice S
    e Assim alterando seu pai caso necessario.
    */

    int  ind,  *pai = malloc(G->n * sizeof(int));
    double dist_atual;
    p_no atual;
    Item It;

    

    p_fp FP = criar_fp(G->n);

    for (int i = 0; i < G->n; i++) {
        pai[i] = NULO;
        
        inserir_fp(FP, i, INT_MAX);
    }


    pai[s] = s;
    diminuiprioridade(FP, s, 0);
    

    while (FP->n != 0) {

        It = extrai_minimo(FP);
        

        if (It.dist != INT_MAX) {
            
            for (atual = G->adj[ It.vertice ]; atual != NULL; atual = atual->prox){

                
                
                ind = indice_vertice( I, atual->nome, G->n);
                dist_atual = buscar_dist(FP,ind);

                if (It.dist + atual->dist < dist_atual) {
                    
                    diminuiprioridade(FP, ind, It.dist + atual->dist);
                    pai[ind] = It.vertice;
                }
            }
        }
    }
    destruir_fp(FP);
    
    return pai;
}



/* Calculo da Centralidade*/

p_no encontrar(int pai, int filho, p_grafo G, p_no* I){
    /* Funcao que busca um vizinhos especifico de um vertice e o devolve*/ 

    for( p_no aux = G->adj[pai]; aux != NULL; aux = aux->prox)
        if( strcmp(I[filho]->nome, aux->nome) == 0)
            return aux;
    return NULL;
} 

void dist(int i, int* pai, double* dT, p_no *I, p_grafo G) {
    /* Funcao que recursivamente calcula as distancias de um vertice até o vertice Raiz em questão, 
    sempre calculando a distancia entre um vertice e seu pai */

    p_no aux;

    if(pai[i] != i) {
        aux = encontrar(pai[i], i, G, I);
        *dT = *dT  +  aux->dist;
        dist(pai[i], pai, dT, I, G);
    
    }

}

double centralidade(int v,int * pai, int pT, p_no * I, p_grafo G) {
    /* Funcao que calcula a centralidade de um Vertice Raiz a partir do somatorio do produto da distancia pela populacao da cidade
    acessada pelo vertice raiz*/

    int pop_alcancada = I[v]->pop , pop_x_dist = 0;
    double Cent, d_total_i;

    for(int i = 0; i < G->n; i++)
        if(pai[i] != NULO && i != v){
            d_total_i = 0;

             dist(i, pai, &d_total_i, I, G) ;

            pop_alcancada += I[i]->pop;
            pop_x_dist += (I[i]->pop)*d_total_i;
        }
    

    if(pop_alcancada >= pT/2.0) {
        Cent = pop_x_dist / (pop_alcancada*1.0);
        return Cent;
    }
    return -1.0;
}



/* Funcoes de ordenação pela centralidade e pela ordem alfabetica*/

void troca_int(int *a, int *b) {
    /* Funcao que troca os ponteiros de dois ints em um vetor*/
    int t = *a;
    *a = *b;
    *b = t;
}

void troca_double(double *a, double *b) {
    /* Funcao que troca os ponteiros de dois doubles em um vetor*/
    double t = *a;
    *a = *b;
    *b = t;
}

int partition(double *Cent, int * Esp, int l, int r) {
    /*Fucnao que separa os Nos com frequencias menor que o pivo a esquerda e maiores ou iguais a direita*/

    int i, pos = r + 1;
    double pivo = Cent[l];

    for (i = r; i >= l; i--) {
        if (Cent[i] >= pivo) {
            pos--;
            troca_double(&Cent[i], &Cent[pos]);
            troca_int(&Esp[i], &Esp[pos]);
        }
    }
    return pos;
}

void QuickSort(double *Cent, int * Esp, int l, int r) {
    /*Fucano recursiva que separa o vetor em menores vetores que serao ordenadas*/

    int i;
    if (r <= l) return;
        i = partition(Cent, Esp, l, r);

        QuickSort(Cent, Esp, l, i-1);
        QuickSort(Cent, Esp, i+1, r);
}

int partition_lex(double *Cent, int *Esp, int p, int r, p_no * I) {
     /*Fucnao que separa os Nos com mesma frequencia em ordem alfabetica, menor que o pivo pra esquerda e maior pra direita*/

    int i, pos = r + 1;
    
    
    for (i = r; i >= p; i--) {
        if (strcmp( I[Esp[i]]->nome , I[Esp[p]]->nome) >= 0) {
            
            pos--;

            troca_double(&Cent[i], &Cent[pos]);
            troca_int(&Esp[i], &Esp[pos]);
    

           
        }
    }
    
    return pos;
}

void QuickSort_Lex(double *Cent, int *Esp, int l, int r, p_no * I) {
    /*Funcao recursiva que separa o vetor em menores vetores que serao ordenadas*/

    int i;

    if (r > l) {
        i = partition_lex(Cent, Esp, l, r, I);

        QuickSort_Lex(Cent, Esp, l, i-1, I);
        QuickSort_Lex(Cent, Esp, i + 1, r, I);
    }
}

void Lexicografico(double *Cent, int * Esp, int n, p_no* I){
    /*Fucnao que pega as palavras com a mesma frequencia e as ordena em ordem alfabetica*/
    int i = n, conta, j;

    while (i > 0) {

        for( j = i, conta = 0;  j >= 0 && Cent[i] == Cent[j] ; j--, conta++);
        
        if(conta > 1) {
            QuickSort_Lex(Cent, Esp, j+1, i, I);
        }

        i = i - conta;
    }
}



/* Funcao relacionada a Impressao*/

void imprimir(double * Cent, p_no * Ind, int * Esp, int n) {
    /* Funcao que pega a lista de centralidades ordenadas e imprime sua centralidade com o nome da cidade baseada no
    vetor Espelho que foi ordenado com as mesmas trocas do vetor de Centralidades.
    Sendo esse vetor Espelho para pegar os indices e achar o nome da cidade no vetor de Indices*/

    for(int i = 0; i < n; i++)
        if(Cent[i] != -1.0)
            printf("%s %0.2f\n", Ind[Esp[i]]->nome, Cent[i]);
}



/* Execucao da Tarefa*/

int main () {
    int n, pop, pop_Total = 0, *pais_j, *espelho;
    char nome[MAX], vert_ini[MAX], vert_fim[MAX];
    double dist, * centralidades;
    p_grafo Cidades;
    p_no * Indices;


    /*Criar Grafo*/
    scanf("%d", &n);
    Cidades = criar_grafo(n);

    /*Leitura dos Vertices*/

    Indices = malloc( n * sizeof(p_no));

    for(int i = 0; i < n; i++) {
        scanf("%s %d", nome, &pop);

        Indices[i] = inserir_cidade(nome, pop);
        pop_Total += pop;
    }


    /*Leitura das Arestas*/
    
    while( scanf("%s %s %lf", vert_ini, vert_fim, &dist) != EOF) 
        inserir_aresta(Cidades, vert_ini, vert_fim, dist, Indices);
        
        
    
    /* Calculando o menor caminho para cada cidade e sua conta da centralidade*/

    centralidades = malloc( n * sizeof(double));

    for(int j = 0; j < n; j++){
        
        pais_j = dijkstra(Cidades, j, Indices);
        
        centralidades[j] = centralidade(j, pais_j, pop_Total, Indices, Cidades);

        free(pais_j);
    }

    /* Criando uma funcao espelho para armazenar os indices que sera manipulado de acordo com a ordenacao da funcao de 
    centralidades*/

    espelho = malloc(n * sizeof(int));

    for(int h = 0; h < n; h++)
        espelho[h] = h;


    /* Ordenação numerica das centralidades e em ordem alfabetica dos nomes em caso de empate*/

    QuickSort(centralidades, espelho, 0, n-1);
    Lexicografico(centralidades, espelho,  n-1, Indices);

    /* Impressao das centralidades e nome das cidades ordenadas*/

    imprimir(centralidades, Indices, espelho, n);


    /* Liberar a memoria alocada*/

    free(espelho);
    free(centralidades);

    for(int k = 0; k < n; k++)
        free(Indices[k]);
    free(Indices);

    destruir_grafo(Cidades);
}
