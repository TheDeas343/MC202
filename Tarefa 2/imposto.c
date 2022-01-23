#include <stdio.h>
#define MAX 1000
#define MESES 12

double calculo_retido(double Salario) {
    double retido ;

    if(Salario > 3743.19){
        retido = (27.5/100)*(Salario-3743.19) +
                 (22.5/100)*(3743.19-2995.7) +
                 (15.0/100)*(2995.7-2246.75) +
                 (7.5/100)*(2246.75-1499.15);

    } else if(Salario > 2995.7) {
        retido = (22.5/100)*(Salario-2995.7) +
                 (15.0/100)*(2995.7-2246.75) +
                 (7.5/100)*(2246.75-1499.15);

    } else if(Salario > 2246.75) {
        retido = (15.0/100)*(Salario-2246.75) +
                 (7.5/100)*(2246.75-1499.15);  

    } else if(Salario > 1499.15) 
        retido = (7.5/100)*(Salario-1499.15);

    else 
        retido = 0;

    return retido;
}

void Retencao(double Salarios[][MESES], double Imposto[][MESES], int n) {
    int i, j;
    for(i = 0; i < n; i++)
        for(j = 0; j < MESES; j++) 
            Imposto[i][j] = calculo_retido(Salarios[i][j]); 
}

double calculo_devido(double Base) {
    double devido;

    if(Base > 44400){
        devido = (27.5/100)*(Base-44400) +
                 (22.5/100)*(44400-36000) +
                 (15.0/100)*(36000-26400) +
                 (7.5/100)*(26400-18000);

    } else if(Base > 36000) {
        devido = (22.5/100)*(Base-36000) +
                 (15.0/100)*(36000-26400) +
                 (7.5/100)*(26400-18000);
       
    } else if(Base > 26400) {
        devido = (15.0/100)*(Base-26400) +
             (7.5/100)*(26400-18000); 

    } else if(Base > 18000) 
        devido = (7.5/100)*(Base-18000);

    else 
        devido = 0;

    return devido; 
}

void Divida(double Salarios[][MESES], double Abater[], double Devido[], int n) {
    double Anual,Base;
    int i, j;

    for (i = 0; i < n; i++){
        Anual = 0;
        for (j = 0; j < MESES; j++)
            Anual += Salarios[i][j];

        Base = Anual - Abater[i];

        Devido[i] = calculo_devido(Base);
    }

}

void le_matriz(double Salarios[][MESES], int n) {
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < MESES; j++)
            scanf("%lf", &Salarios[i][j]);
}

void le_abatimentos( double Abater[], int n) {
   int i;
    for (i = 0; i < n; i++)
        scanf("%lf", &Abater[i]); 
}

void imprimir_tabela(double Imposto[][MESES], double Devido[], int n) {
    printf("Jan	Fev	Mar	Abr	Mai	Jun	Jul	Ago	Set	Out	Nov	Dez	Retido  Devido  Ajuste\n");
    int i, j;
    double Retido;
    for (i = 0; i < n; i++){
        Retido = 0;

        for (j = 0; j < MESES; j++) {
            printf("%.2lf ", Imposto[i][j]);
            Retido += Imposto[i][j];
        }

        printf("%.2f ", Retido);
        printf("%.2f ",Devido[i]);
        printf("%.2f\n",(Devido[i] - Retido));
    }
}

int main() {
    int n;
    double Salarios[MAX][MESES], Imposto[MAX][MESES], Abater[MAX], Devido[MAX];

    scanf("%d", &n);

    le_matriz( Salarios, n);
    le_abatimentos(Abater, n);

    Retencao(Salarios, Imposto, n);
    Divida ( Salarios, Abater, Devido, n);

    imprimir_tabela(Imposto, Devido, n);

    return 0;
}
