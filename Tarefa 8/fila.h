#define MAX 26
#define VAX 13

typedef struct No {
    int RG;
    char profissao[MAX];
    char vacina[VAX];
    struct No* prox;
} No;

typedef struct No* p_no;

p_no criar_lista();

void destruir_lista(p_no lista);

int verificar_profissao(p_no pessoa);

p_no fenomeno_0(p_no inicio, p_no pessoa, p_no lanterna);

p_no fenomeno_1(p_no inicio, p_no pessoa);

p_no fenomeno_2(p_no inicio, p_no pessoa);

p_no fenomeno_3(p_no inicio, p_no pessoa, p_no lanterna);

p_no adicionar_pessoa(p_no inicio, p_no lanterna, p_no pessoa, int* aux);

void imprime(p_no lista) ;
