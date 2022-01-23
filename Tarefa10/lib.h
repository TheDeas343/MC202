#define MAX 21
#define OBJ 11

/* Struct para o Navio*/
typedef struct Navio {
    /*Um navio Recebe os atributos do Nome, objetivo (carregar ou descarregar).
    um codigo relacionado com o tipo de carga que ele carrega (arroz, feijao ...),
    a quantidade de conteiners que ele leva e a informacao do navio atras dele, ou sjea, o proximo da fila*/

    char nome[MAX];
    char objetivo[OBJ];
    char carga[MAX];
    int qtd;
    struct Navio * prox;
}Navio ;

typedef struct Navio * p_navio ;

/*Struct da Fila*/
typedef struct Fila {
    p_navio ini , fim;
} Fila;

typedef struct Fila* p_fila;


/*Struct dos Conteiners*/
typedef struct Conteiner {
    char carga[MAX];;
}Conteiner;

typedef struct Conteiner* p_cont;


/*Struct da Pilha*/
typedef struct Pilha{
    p_cont v;
    int topo;
} Pilha;

typedef struct Pilha* p_pilha;


/*Declaração das funcoes utilizadas*/
p_fila criar_fila(); 

void adicionar_navio(p_fila Fila);

void desenfileira( p_fila Fila);

void final_da_fila( p_fila Fila);

p_pilha criar_vetor_pilhas(int capac_docas, int n_docas);

void carregar(p_pilha Docas, p_fila Fila, int n_docas, int capac_docas,int* acao, int* contagem);

void descarregar(p_pilha Docas, p_fila Fila, int n_docas, int capac_docas,int* acao, int* contagem);

void atracar(p_pilha Docas, p_fila Fila, int n_docas, int capac_docas,int* acao, int* contagem);

void destruir_lista(p_navio navio);

void destruir_fila( p_fila Fila);

int navios_na_fila(p_fila Fila);
