#define AERO 4

typedef struct data {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct voo {
    int numero;
    char origem[AERO];
    char destino[AERO];
    struct data data;
    double preco;
    int situacao ;
} Voo;



Data ler_data();

int compara_data(Data data1, Data data2);

int diferenca_data(Data data1, Data data2);

void registrar(Voo voos[], int qtd_voos);

void cancelar(Voo voos[], int qtd_voos);

void alterar(Voo voos[], int qtd_voos);

int verificar(Voo ida, Voo volta);

void planejar(Voo voos[], int qtd_voos);
