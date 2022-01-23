#include <stdio.h>
# define max 10000

int index(int vetor[], int n,int N) {
    int i;

    for(i = 0; i < n; i++) {
        if (vetor[i] == N)
            return i;
        
        
    }
    return 0; 
}

void inversa(int n, int vetor[], int p1, int p2) {
    int i, aux1 , aux2, i1, i2;

    i1 = index(vetor,n,p1);
    i2 = index(vetor,n,p2);

    for ( i = 0 ; i < (i2-i1)/2 + 1; i++) {
        
        aux1 = vetor[i1+i];
        aux2 = vetor[i2-i];

        vetor[i1+i] = aux2;
        vetor[i2-i] = aux1;

    }
}

void esperar(int n, int vetor[], int p1, int p2) {
    int i, aux1 , aux2, i1, i2;

    i1 = index(vetor,n,p1);
    i2 = index(vetor,n,p2);

    for( i = i1; i < i2; i++) {

        aux1 = vetor[i];
        aux2 = vetor[i+1];

        vetor[i] = aux2;
        vetor[i+1] = aux1;

    }
   
}
int main() {
    int n, m, vetor[max], i, tipo, p1, p2;

    scanf("%d",&n);
    scanf("%d",&m);


    for( i = 0; i< n+1; i++)
        vetor[i]=i+1;

    for( i = 0; i < m; i++) {
        scanf("%d %d %d", &tipo, &p1, &p2);

        if (tipo == 1)
            inversa(n,vetor,p1, p2);
        else
            esperar(n,vetor,p1, p2);
            
    }


    for( i = 0 ; i<n ;i++) {
        if (i != n-1)
            printf("%d ",vetor[i]);
        else
            printf("%d\n",vetor[i]);
    }
    return 0;

}
