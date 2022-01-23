#include <stdio.h>
#include <stdlib.h>
#include "minecraft.h"
#define MAX_Y 256 /* Altitude max da coordenada Y*/

/* Definicao de funcoes*/

int **calcularAltitudes(int m, int n, int seed) {
    /*Funcao que aloca e retorna uma matriz de duas dimensoes e 
    calcula a altitude para cada entrada.
    */

    int **altitudes;

    /*alocando matriz 2D*/
    altitudes = malloc(m*sizeof(int *));
    for (int i = 0; i < m; i++)
        altitudes[i] = malloc(n*sizeof(int));

    /*calculando as altitudes*/
    for(int x = 0; x < m; x++)
        for(int z = 0; z < n; z++)
            altitudes[x][z] = (seed*(202 + x + z) + 12345 + x + z) % 256 ;
    
    return altitudes;
}

Bloco ***criarMundo(int m, int n, int **altitudes, int seed) {
    /*Funcao que aloca e retorna uma matriz de tres dimensoes e 
    calcula e fornece o tipo de bloco para cada entrada.
    */

    Bloco ***mundo;
    int x, y, z;
    int M;
    
    /*alocando matriz 3D*/
    mundo = malloc(m*sizeof(Bloco **));
    for ( x = 0; x < m; x++) 
        mundo[x] = malloc(MAX_Y*sizeof(Bloco *));
    for ( x = 0; x < m; x++)
        for( y = 0; y < MAX_Y; y++) 
            mundo[x][y] = malloc(n*sizeof(Bloco));    
    
    /*calculando e atribuindo o tipo*/
    for ( x = 0; x < m; x++)
        for ( y = 0; y < MAX_Y; y++)
            for ( z = 0; z < n; z++){
                if (y > altitudes[x][z])
                    M = 21;
                else
                    M = (seed*(202 + x + y + z) + x + y + z) % 33;
                
                mundo[x][y][z].tipo = M;
            }

    return mundo;
}

double explorarMundo(Bloco ***mundo, int m, int n, int **altitudes, double tempoPorBloco, int *qtdDiamante, int *qtdOuro, int *qtdFerro, int *qtdBlocos) {
    /*Funcao que passa pela matriz mundo e faz a contagem do total blocos
    Ainda faz a contagem especifica de blocos de Diamante, Ouro e Ferro.
    Ao final retorna o tempo que demoraria pra querar todos os blocos.
    */
    
    int x, y, z;

    for ( x = 0; x < m; x++)
        for ( y = 0; y < MAX_Y; y++)
            for ( z = 0; z < n; z++){
                if (mundo[x][y][z].tipo < 21){
                    *qtdBlocos += 1;

                    if (mundo[x][y][z].tipo == 0)
                        *qtdDiamante += 1;

                    else if (mundo[x][y][z].tipo == 1 || mundo[x][y][z].tipo == 2)
                        *qtdOuro += 1;

                    else if (mundo[x][y][z].tipo >= 3 && mundo[x][y][z].tipo <= 5)
                        *qtdFerro += 1;
                        
                }
            }
    
    return(*qtdBlocos)*tempoPorBloco;
}


/* Leitura de entradas execucao do codigo*/

int main() {
    int m, n, seed, **altitudes, qtdDiamante=0, qtdOuro=0, qtdFerro=0, qtdBlocos=0;
    double tempoPorBloco, tempototal;
    Bloco ***mundo;
    int x, y;

    /*Leitura das entradas*/
    scanf("%d %d",&m,&n);
    scanf("%d",&seed);
    scanf("%lf",&tempoPorBloco);

    /*Execucao das funcoes*/
    altitudes= calcularAltitudes( m, n, seed);
    mundo = criarMundo( m,  n, altitudes, seed);
    tempototal = explorarMundo(mundo, m, n, altitudes, tempoPorBloco, &qtdDiamante, &qtdOuro, &qtdFerro, &qtdBlocos);

    /*Impressao das respostas*/
    printf("Total de Blocos: %d\n",qtdBlocos);
    printf("Tempo total: %0.2lfs\n",tempototal);
    printf("Diamantes: %d\n",qtdDiamante);
    printf("Ouros: %d\n",qtdOuro);
    printf("Ferros: %d\n",qtdFerro);


    /*Liberando o espaco alocado*/
    for (int i = 0; i < m; i++)
        free(altitudes[i]);
    free(altitudes);

    for ( x = 0; x < m; x++)
        for( y = 0; y < MAX_Y; y++) 
            free(mundo[x][y]);
    for ( x = 0; x < m; x++) 
        free(mundo[x]);
    free(mundo);
  
    return 0;
}
