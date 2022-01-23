typedef struct {
    int tipo;
} Bloco;

int **calcularAltitudes(int m, int n, int seed);

Bloco ***criarMundo(int m, int n, int **altitudes, int seed);

double explorarMundo(
    Bloco ***mundo, int m, int n, int **altitudes, double tempoPorBloco,
    int *qtdDiamante, int *qtdOuro, int *qtdFerro, int *qtdBlocos);
