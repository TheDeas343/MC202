#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 27 /*26 alfabeto mais o caracter nulo*/

void ID(char *seg_dna, int n, int *id) {
    
    for (int i = 0; i < n; i++)
        id[i] = 0;
    
    for (int j = 0; j < n - 1; j++)
        for (int k = j + 1; k < n; k++)
            if (seg_dna[j] == seg_dna[k])
                id[k]++;

    printf("ID:     ");
    for (int m = 0; m < n; m++){
        if (m != n-1)
            printf("%d ",id[m]);
        else
            printf("%d\n",id[m]);
    
    
    }
}

void transcricao(char DNA[MAX], char RNA[MAX], char *seg_dna, char *seg_rna, int n) {
    int j;

    for( int i = 0; i < n; i++){
        j=0;
        while (DNA[j] != '\0') {
            if (seg_dna[i] == DNA[j]){
                seg_rna[i] = RNA[j];
            }
            j++;
        }
    }
}

void imprime(char *seg, int n){
    for (int i = 0; i < n; i++)
        if (i != n-1)
            printf("%c ",seg[i]);
        else
            printf("%c\n",seg[i]);
}

int main() {
    int tam;
    char *seg_dna,*seg_rna;
    char DNA[MAX],RNA[MAX];
    int *id;
    
    scanf("%s",DNA);
    scanf("%s",RNA);

    scanf("%d",&tam);

    seg_dna = malloc((tam+1)*sizeof(char));
    seg_rna = malloc((tam+1)*sizeof(char));
    id = malloc(tam*sizeof(int));

    scanf("%s",seg_dna);
    
    ID(seg_dna, tam, id);
    transcricao(DNA, RNA, seg_dna, seg_rna, tam);

    printf("DNA:    ");
    imprime(seg_dna,tam);

    printf("        ");
    for( int i = 0; i < tam; i++)
        if (i != tam-1)
            printf("| ");
        else
            printf("|\n");


    printf("RNA:    ");
    imprime(seg_rna,tam);

    free(id);
    free(seg_dna);
    free(seg_rna);
      
    return 0;
}
