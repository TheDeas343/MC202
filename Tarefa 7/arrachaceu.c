#include <stdio.h>
#include <stdlib.h>

/* Funcoes auxiliares*/

int **alocar(int tam) {
    /*Funcao que aloca uma matriz quadrada de tam = n+2*/

    int **matriz,i; 
    matriz = calloc(tam,sizeof(int*));
    for( i = 0; i < tam; i++) 
        matriz[i] = calloc(tam,sizeof(int));
        
    return matriz;
}

void ler (int **grade,int tam) {
    /* Faz a leitura da matriz inteira*/

    for( int i = 0; i < tam; i++)
        for(int j = 0; j< tam; j++)
            scanf("%d",&grade[i][j]);
        
}

void imprime( int **grade, int n) {
    /* Impressao da parte central da matriz */

    for (int i = 1; i < n+1; i++)
        for (int j = 1; j < n+1; j++)
            if (j != n )
                printf("%d ",grade[i][j]);
            else
                printf("%d\n",grade[i][j]);
}

void liberear(int **grade, int tam) {
    /* Libera o espaco alocado*/

    for( int i = 0; i < tam; i++) 
        free(grade[i]);
    free(grade);
}



/* Funcoes Complementares do Backtracking */

int sem_repeticao(int **m, int n, int l, int c, int v) {
    /* Verificar se pode inserir um numero baseado apenas sem repetir na linha ou coluna*/

    int i;
    for (i = 1; i < n+1; i++)
        if (m[l][i] == v) /* aparece na linha l? */
            return 0;
    for (i = 1; i < n+1; i++)
        if (m[i][c] == v) /* aparece na coluna c? */
            return 0;
    return 1;
}

void proxima_entrada(int L, int C, int *novoL, int *novoC, int n) {

    /* Devolve a proxima posição da matriz nxn dentro da matriz (n+2)x(n+2)*/

    if (C < n) {
        *novoL = L;
        *novoC = C + 1;
    } else {
        *novoL = L + 1;
        *novoC = 1;
    }
}

int conta_arranhaceu(int **m, int n, int l, int c) {
    /* Funcao dividida em 4 restricoes:

    1) Linha: Esquerda->Direita : faz a contagem de edificios enquanto os valores sao testados,
        voltando atras caso a contagem for maior do que a restricao, e ao chegar na coluna n
        verifica se a contagem é exatamente a restricao imposta (armazenada na coluna 0 dessa linha).

    2) Coluna : Cima->Baixo: Mesma lógica da restricao 1) porém essa análise é feita verticalmente
        (com base na restricao armazenada na linha 0 dessa coluna)
    
    3) Linha: Direita->Esquerda : Este caso se difere do 1) e 2) , ja que os numeros edificos sao
        colocados na frente da analise anterior e nao atras como no 1) e no 2), alem de que leva-se em conta
        que as primeiras analises podem ser o numero 0(que indica nenhum edificio).
        Com isso, analise da restricao é feita apenas se for a ultima coluna da linha,
        verificando se a contagem é exatamente a da restricao ( armazenada na coluna n+1 dessa linha)
    
    4) Coluna: Baixo->Cima : Mesma lógica da restricao 3) porém essa análise é feita verticalmente
        apenas se for a ultima linha da coluna 
        (com base na restricao armazenada na linha n+1 dessa coluna)
    */

    int i, j, conta, aux;
    
    /* 1) RESTRICAO LINHA: Esquerda -> Direita */

    conta = 0;
    for( i = 1; i <= n; i++) {
        aux = 1;
        for( j= 1; j < i; j++){
            if (m[l][i] <= m[l][j]){
                aux = 0;
                break;

            }
        }
        if (aux == 1)
            conta += 1;
    }
    
    if (conta > m[l][0])
        return 0;
    else
        if (c == n && conta != m[l][0])
            return 0;


    /* 2) RESTRICAO COLUNA : Cima -> Baixo */
    
    conta = 0;
    for( i = 1; i <= n; i++) {
        aux = 1;
        for( j= 1; j < i; j++){
            if (m[i][c] <= m[j][c]){
                aux = 0;
                break;

            }
        }
        if (aux == 1)
            conta += 1;
    }
    
    if (conta > m[0][c])
        return 0;
    else
        if (l == n && conta != m[0][c])
            return 0;


    if( c == n ) {

        /*3) RESTRICAO LINHA: Direita -> Esquerda */

        conta = 0;

        for( i = n; i >= 1; i--) {
            aux = 1;
            for( j = n; j > i; j--){
                if (m[l][i] <= m[l][j]){
                    aux = 0;
                    break;
                }
            }
            if (aux == 1)
                conta += 1;
        }
        
        
        if (conta != m[l][n+1])
            return 0;
        return 1;
    }
        
    if(l==n){
        /* 4) RESTRICAO COLUNA : Baixo -> Cima*/
        conta = 0;
        for( i = n; i >= 1; i--) {
            aux = 1;
            for( j = n; j > i; j--){
                if (m[i][c] <= m[j][c]){
                    aux = 0;
                    break;
                }
            }
            if (aux == 1)
                conta += 1;
        }
        
        if (conta != m[n+1][c])
            return 0;
    
        return 1; 
    }

     return 1;      
}



/* Funcao principal do Backtracking*/

int backtracking(int **grade, int n, int L, int C) {
    /* Funcao de backtrancking que apresenta dois tipos restricao:
    1- restricao por nao poder repetir o mesmo numero na coluna ou linha.
    2- restricao baseada na contagem de arranhaceus em cada vista
    */

    int  novoL, novoC;
    if (L == n+1) {
        imprime(grade,n);
        return 1;
    }

    proxima_entrada( L, C, &novoL, &novoC, n);

    for (int val = 1; val <= n; val++) {
        if (sem_repeticao( grade, n, L, C, val) == 1 ) {
            grade[L][C] = val;
            if(conta_arranhaceu( grade, n, L, C) == 1)

                if(backtracking(grade, n, novoL, novoC))
                    return 1;
        }
    }
    grade[L][C] = 0;
    return 0;
}


int main() {
    int **grade, n;

    scanf("%d",&n);

    grade = alocar(n+2);
    ler (grade,n+2);
    
    backtracking(grade, n, 1, 1);
    
    liberear(grade,n+2);
}
