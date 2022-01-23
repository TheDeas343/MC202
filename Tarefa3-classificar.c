#include <stdio.h>
#include <string.h>
#define MAX_TAM 31 /*Maximo de caracteres mais o '\0'*/
#define MAX_NOMES 100
#define TIPO 10 /*Max de caracter entre homonimos e parentes mais o '\0'*/

/*DEFINICAO DE FUNCOES*/

/* Subfuncoes das funcao principal*/
int encontrar(char Nome[MAX_TAM],int tam, char Lista[][MAX_TAM]) {
    /*Funcao que verifica se uma string Nome esta presente em uma Lista de strings de tamanho tam.
    Retorna 0 se nao encontrar.
    Retorna 1 se encontrar.
    */
    int encontrei = 0;
    for (int i =0; i<tam; i++)
        if (strcmp(Lista[i], Nome) == 0)
            encontrei = 1;
    return encontrei;
}

int comparar_nomes(char Nome1[MAX_TAM],char Nome2[MAX_TAM]) {
    /*Funcao que compara os primeiro nomes de duas strings Nome1 e Nome2.
    O primeiro nome de uma string nome é tudo que esta antes doo "_" (underline).
    Retorna 1 se os primeiros nomes forem iguais.
    Retorna 0 se os primeiros nomes forem diferentes.
    */    
    int i=0, j=0, verificar = 1;

    while( Nome1[i] != '_')
        i++;
    while( Nome2[j] != '_')
        j++;
    
    if (i != j)
        verificar = 0;
    else
        for(int x = 0;x<i;x++)
            if(Nome1[x] != Nome2[x])
                verificar = 0;
    return verificar;
}  


/*Funcao principais*/
int homonimos(char Nomes[][MAX_TAM], char Homonimos[][MAX_TAM], int n) {
    /* Funcao que seleciona nomes homonimos de uma lista NOMES de tamanho n
    e os armazena e uma lista HOMONIMOS.
    Ao final, retorna o tamanho da lista HOMONIMOS.
    */
    int tam=0;
    
    for(int i = 0; i < n; i++)     
        for(int j = i+1; j < n; j++)
            if(comparar_nomes(Nomes[i], Nomes[j]) != 0){

                if(encontrar(Nomes[i],tam,Homonimos) == 0){
                    strcpy(Homonimos[tam], Nomes[i]);
                    tam++;
                }if(encontrar(Nomes[j],tam,Homonimos) == 0){
                    strcpy(Homonimos[tam], Nomes[j]);
                    tam++;
                }
            }                  
    return tam;
}


/* Funcoes de ordenacao e impressao*/
void BubbleSort(char Lista[][MAX_TAM], int indices[MAX_NOMES],int tam){
    /*Funcao que ordena uma lista de indices que se referem a elementos de uma lista de nomes.
    Comparando os elementos dessa lista de nomes lexicograficamente
    e ordenando os respectivos indices na lisa de Indices.
    */
    int trocou =1,aux;

    for (int x = 0; x < tam; x++)
        indices[x] = x;

    while(trocou == 1){
        trocou = 0;
        for (int i = 0; i < tam-1; i++){
            
            if(strcmp(Lista[indices[i]],Lista[indices[i+1]])>0){
                
                aux = indices[i];
                
                indices[i] = indices[i+1];
                indices[i+1] = aux;
            
                trocou = 1;
            }
        }
    }
}

void imprime_nomes(char Lista[][MAX_TAM],int indices[MAX_NOMES],int tam) {
    /*Funcao impreme cada item de uma lista, dado uma Lista de tamanho n.*/
    
    for(int i = 0; i < tam; i++)
        printf("%s\n",Lista[indices[i]]);        
}


/*LEITURA DAS ENTRADAS E EXECUCAO DO CODIGO*/
int main() {
    int n,tamanho,indices[MAX_NOMES];
    char tipo[TIPO];
    char Nomes[MAX_NOMES][MAX_TAM],Homonimos[MAX_NOMES][MAX_TAM];
    
    scanf("%d",&n);
    scanf("%s",tipo);

    for(int i = 0; i < n; i++)
        scanf("%s",Nomes[i]);
    
    if (strcmp(tipo,"homonimos") == 0){

        tamanho = homonimos(Nomes,Homonimos,n);

        BubbleSort(Homonimos,indices,tamanho);
        imprime_nomes(Homonimos,indices,tamanho);
    
        
    }
}
