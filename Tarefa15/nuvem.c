#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 51 /*Numero maximo de caracteres por palavra*/
#define PRINT 50 /*Numero MAX de frequencias que são impressas*/
#define VET 1783 /*Numero primo utilizado nos slides*/

/*Implementação da tabela hashing*/

typedef struct No{
    char chave[MAX];
    int freq;
    struct No * prox;
} No;

typedef No * p_no;

typedef struct {
    p_no vetor[VET];
} Hash;

typedef Hash * p_hash;


/* Funcoes relacionadas a Hashing*/

p_hash criar_hash() {
    /* Funcao que cria uma Tabela hashing.
    Inicializando as entradas como NULL, pois assim é possivel saber quando a entrada foi utilizada ou nao*/
    p_hash H;
    
    H = malloc(sizeof(Hash));

    for( int i = 0; i < VET; i++)
        H->vetor[i] = NULL;
    
    return H;

}

void destruir_lista(p_no lista) {
    /*Funcao que libera a memoria alocada de uma lista ligada*/
    if (lista != NULL) {
        destruir_lista(lista->prox);
    free(lista);
    }
}

void destruir_hash(p_hash H) {
    /*Funcao que libera a memoria alocada de uma tabela hashing formada por listas ligadas*/
    for( int i = 0; i < VET; i++)
        destruir_lista(H->vetor[i]);
    free(H);
}

int hash(char word[MAX]) {
    /*Funcao que calcula um hash para o espalhamento de dados em uma tabela
    Pelo METODO DA DIVISÃO.*/

    int i, n = 0;

    for (i = 0; i < strlen(word); i++)
        n = (256 * n + word[i]) % VET;

    return n;
}

p_no inserir_lista(p_no lista, char word[MAX], int* p_conta) {
    /*Funcao que ou cria um No para armazenar uma palavra e sua frequencia, ou apenas aumenta a frequencia 
    no caso da palavra ja estar na lista.
    Alem de fazer a contagem de quantas palavras foram colocadas na tabela hashing
    */

    p_no novo, atual;
   
    for( atual = lista ; atual != NULL ; atual = atual-> prox)
        if(strcmp(word, atual->chave) == 0) {   
            atual->freq++;
            return lista;
        }

    novo = malloc(sizeof(No));

    strcpy(novo->chave, word);
    novo->freq = 1;
    novo->prox = lista;

    *p_conta = *p_conta + 1;

    return novo;
}

void inserir_hash(p_hash H, char word[MAX], int * p_conta) {
    /*Funcao que insere uma palavra na tabela hashing e conta o numero de palavras colocadas*/
    int n = hash(word);
    H->vetor[n] = inserir_lista(H->vetor[n], word, p_conta);
}


/* Funcoes especificas da Tarefa*/

void arrumar_string(char nova[MAX]) {
    /*Fucnao que recebe uma string e devolve sua versao totalmente em minusculas e sem caracteres que representam pontuacoes ou numeros*/
    char atual[MAX];
    int conta = 0;

    for(int i = 0; i < strlen(nova); i++)
        if( ispunct (nova[i]) == 0 && isdigit (nova[i]) == 0) {
            atual[conta] = tolower(nova[i]) ;
            conta++;
        }

    atual[conta] = '\0';
    strcpy(nova, atual);
    
}

/*-->Funcoes para o vetor de StopWords*/

char ** criar_vetor(int n) {
    /* Funcao que aloca um vetor para armazenar as stopwords que serao ignoradas na contagem das palavras*/
    char ** V;

    V = malloc(n * sizeof(char*));
    for( int i = 0; i < n; i++)
        V[i] = malloc( MAX * sizeof(char));
    
    return V;
}

int verif_StopWord(char ** v, char *w, int n) {
    /*Funcao que verifica se uma palavra encontrada faz parte das palavras que devem ser ignoradas
    Devolve 0 se ela deve ser ignorda e 1 no caso contrario
    */
    for(int i = 0; i < n; i++)
        if (strcmp( w, v[i]) == 0)
            return 0;
    return 1;
}


/*Funcoes relacionadas a ORDENACAO */

void alinhar_tabela(p_no *vetor, p_hash H) {
    /*Funcao que copia a tabela hashing para um vetor para poder ordenalo*/

    p_no atual;
    int aux = 0;

    for(int i = 0; i < VET; i++)
        for(atual = H->vetor[i]; atual != NULL; atual = atual->prox){
            vetor[aux] = atual;
            aux++;
        }
}

void troca(p_no *a, p_no *b) {
    /*Fucnao que troca para onde os ponteiros a e b apontam*/
    p_no  t = *a;
    *a = *b;
    *b = t;
}

 int partition(p_no *v, int l, int r) {
     /*Fucnao que separa os Nos com frequencias menor que o pivo a esquerda e maiores ou iguais a direita*/

    int i, pivo = v[l]->freq, pos = r + 1;

    for (i = r; i >= l; i--) {
        if (v[i]->freq >= pivo) {
            pos--;
            troca(&v[i], &v[pos]);
        }
    }
    return pos;
}

void QuickSort(p_no *v, int l, int r) {
    /*Fucano recursiva que separa o vetor em menores vetores que serao ordenadas*/

    int i;

    if (r > l) {
        i = partition(v, l, r);

        QuickSort(v, l, i-1);
        QuickSort(v, i + 1, r);
    }
}

/*Funcoes relacionadas a IMPRESSAO*/

int partition_lex(p_no *v, int p, int r) {
     /*Fucnao que separa os Nos com mesma frequencia em ordem alfabetica, menor que o pivo pra esquerda e maior pra direita*/

    int i, pos = r + 1;
    
    
    for (i = r; i >= p; i--) {
        
        if (strcmp( v[i]->chave , v[p]->chave) <= 0) {
            pos--;
            troca(&v[i], &v[pos]);
           
        }
    }
    
    return pos;
}

void QuickSort_Lex(p_no *v, int l, int r) {
    /*Funcao recursiva que separa o vetor em menores vetores que serao ordenadas*/

    int i;

    if (r > l) {
        i = partition_lex(v, l, r);

        QuickSort_Lex(v, l, i-1);
        QuickSort_Lex(v, i + 1, r);
    }
}

void Imprimir(p_no *v, int n){
    /*Fucnao que imprime as 50 palavreas mais frequentes*/

    for(int i = n; i > n - PRINT; i--)
        printf("%s %d \n", v[i]->chave, v[i]->freq);
    
    
}

void Lexicografico(p_no *vet, int n){
    /*Fucnao que pega as palavras com a mesma frequencia e as ordena em ordem alfabetica*/
    int i = n, conta, j;

    while (i > n - PRINT) {

        for( j = i, conta = 0;  j >= 0 && vet[i]->freq == vet[j]->freq ; j--, conta++);
        
        if(conta > 1) {
            QuickSort_Lex(vet, j+1, i);
        }

        i = i - conta;
    }
}


/* Leitura das entradas e execucao do codigo*/
int main () {
    p_hash T_Hash;
    p_no *vet_ord;
    int n, n_stpw, conta = 0;
    char nova[MAX], **StopW ;
    
    scanf("%d", &n);

    /*Criar o vetor de Stop Word*/

    scanf("%d", &n_stpw);
    StopW = criar_vetor(n_stpw);
    for( int i = 0 ; i < n_stpw; i++)
        scanf("%s", StopW[i]);

    /*Criar a tabela hashing e adicionar os nos*/

    T_Hash = criar_hash();

    while(scanf("%s", nova) != EOF) {
        arrumar_string(nova);
        if(strlen(nova) > 1 && verif_StopWord(StopW, nova, n_stpw) != 0)
            inserir_hash(T_Hash, nova, &conta);  
    }

    /*Ordenar de acordo comas frequencias */
    vet_ord = malloc(conta * sizeof(p_no));
    alinhar_tabela(vet_ord, T_Hash);
    QuickSort(vet_ord, 0, conta-1);

    /*Imprimir em ordem alfabetica as palavras com mesma frequencia*/

    Lexicografico(vet_ord, conta -1);
    Imprimir(vet_ord, conta-1);

    /*Liberar o espaco alocado*/

    destruir_hash(T_Hash);
    for( int j = 0; j < n_stpw; j++)
        free(StopW[j]);
    free(StopW);
    free(vet_ord);
}
