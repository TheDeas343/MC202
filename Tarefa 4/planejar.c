
#include <stdio.h>
#include <string.h>
#include "planejar.h"
#define MAX 100
#define AERO 4
#define DATA 11

char MESES[12]= {31,28,31,30,31,30,31,31,30,31,30,31};

Data ler_data() {
    Data data;
    scanf("%d/%d/%d",&data.dia,&data.mes,&data.ano);

    return data;
}

int compara_data(Data data1, Data data2) {
     /* ANO */
    if (data1.ano > data2.ano)
        return 1;

    else if (data1.ano < data2.ano)
        return -1;

    else{
        /* MES */
        if (data1.mes > data2.mes)
            return 1;

        else if (data1.mes < data2.mes)
            return -1;
        
        else {
            /* DIA */
            if (data1.dia > data2.dia)
                return 1;

            else if (data1.dia < data2.dia)
                return -1;
            
            else
                return 0;
        }
    }
}

int dias_inicio(Data data) {
    int dias_passados = 0;

    for( int i = 0; i < (data.mes - 1); i++)
        dias_passados += MESES[i];
    dias_passados += data.dia;

    return dias_passados;
}

int diferenca_data(Data data1, Data data2) {
    int diferenca;

    if (data2.ano > data1.ano)
        if (data2.mes > data1.mes)
                diferenca = 365 + dias_inicio(data2)-dias_inicio(data1) + 1;
        else
            diferenca = 365 -(dias_inicio(data1)-dias_inicio(data2)) + 1;
    else
        diferenca = dias_inicio(data2)-dias_inicio(data1) + 1;
    
    return diferenca;
}

void registrar(Voo voos[], int qtd_voos) {
    Voo voo;

    scanf("%d",&voo.numero);
    scanf("%s %s",voo.origem,voo.destino);
    voo.data = ler_data();
    scanf("%lf",&voo.preco);
    voo.situacao = 1;

    voos[qtd_voos] = voo;
}

void cancelar(Voo voos[], int qtd_voos) {
    int numero_voo;

    scanf("%d",&numero_voo);

    for( int i = 0; i < qtd_voos; i++)
        if (voos[i].numero == numero_voo)
            voos[i].situacao = 0;
}

void alterar(Voo voos[], int qtd_voos ) {
    int numero_voo;
    double novo_valor;

    scanf("%d",&numero_voo);
    scanf("%lf",&novo_valor);

    for(int i = 0; i < qtd_voos; i++)
        if (voos[i].numero == numero_voo)
            voos[i].preco = novo_valor;

}

int verificar(Voo ida, Voo volta) {
    if (diferenca_data(ida.data, volta.data) < 4)
        return 0;
    return 1;
}

void planejar(Voo voos[], int qtd_voos) {
    Voo ida[MAX],volta[MAX];
    Voo melhor_ida,melhor_volta;

    Data data_inicio,data_fim;
    char codigo_origem[AERO];

    scanf("%s",codigo_origem);
    data_inicio = ler_data();
    data_fim = ler_data();

    int x = 0, y = 0;

    for(int i = 0; i < qtd_voos; i++)
        if(voos[i].situacao != 0 && strcmp(voos[i].origem,codigo_origem) == 0)
            if(compara_data(data_inicio,voos[i].data) <= 0 && compara_data(data_fim,voos[i].data) >= 0){
                ida[x] = voos[i];
                x++;
            }
        
    
    for(int j = 0; j < qtd_voos; j++)
        if(voos[j].situacao != 0 && strcmp(voos[j].destino,codigo_origem) == 0)
            if(compara_data(data_inicio,voos[j].data) <= 0 && compara_data(data_fim,voos[j].data) >= 0){
                volta[y] = voos[j];
                y++;
            }
        
    
    melhor_ida = ida[0];
    melhor_volta = volta[0];

    for(int j = 0; j < x; j++)
        for(int k = 0; k < y; k++)
            if(strcmp(ida[j].origem,volta[k].destino)==0 && strcmp(ida[j].destino,volta[k].origem)==0)
                if (verificar(ida[j],volta[k]) != 0)
                    if (ida[j].preco + volta[k].preco < melhor_ida.preco + melhor_volta.preco){
                        melhor_ida = ida[j];
                        melhor_volta = volta[k];
                    }
                
    
    printf("%d\n",melhor_ida.numero);
    printf("%d\n",melhor_volta.numero);
}



    
