#include "libMatriz.h"
#include "libDouble.h"

void alocaMatrizes(Intervalo_t** original, Intervalo_t** matriz1, Intervalo_t** matriz2, Intervalo_t** matriz3, int n) {
    if (!(*original = malloc(sizeof(Intervalo_t) * n * n))) {
        fprintf(stderr, "erro ao alocar matriz 1\n");
        exit(1);
    }

    if (!(*matriz1 = malloc(sizeof(Intervalo_t) * n * n))) {
        fprintf(stderr, "erro ao alocar matriz 1\n");
        exit(1);
    }
    if (!(*matriz2 = malloc(sizeof(Intervalo_t) * n * n))) {
        fprintf(stderr, "erro ao alocar matriz 2\n");
        exit(1);
    }
    if (!(*matriz3 = malloc(sizeof(Intervalo_t) * n * n))) {
        fprintf(stderr, "erro ao alocar matriz 3\n");
        exit(1);
    }
}

void alocaIndependentes(Intervalo_t** independentes, Intervalo_t** independentes1, Intervalo_t** independentes2, Intervalo_t** independentes3, int n) {
    if (!(*independentes = malloc(sizeof(Intervalo_t) * n))) {
        fprintf(stderr, "erro ao alocar independentes \n");
        exit(1);
    }
    if (!(*independentes1 = malloc(sizeof(Intervalo_t) * n))) {
        fprintf(stderr, "erro ao alocar independentes 1\n");
        exit(1);
    }
    if (!(*independentes2 = malloc(sizeof(Intervalo_t) * n))) {
        fprintf(stderr, "erro ao alocar independentes 2\n");
        exit(1);
    }
    if (!(*independentes3 = malloc(sizeof(Intervalo_t) * n))) {
        fprintf(stderr, "erro ao alocar independentes 3\n");
        exit(1);
    }
}

void alocaResultados(Intervalo_t** variaveis1, Intervalo_t** variaveis2, Intervalo_t** variaveis3, int n) {
    if (!(*variaveis1 = malloc(sizeof(Intervalo_t) * n))) {
        fprintf(stderr, "erro ao alocar resultados 1\n");
        exit(1);
    }
    if (!(*variaveis2 = malloc(sizeof(Intervalo_t) * n))) {
        fprintf(stderr, "erro ao alocar resultados 2\n");
        exit(1);
    }
    if (!(*variaveis3 = malloc(sizeof(Intervalo_t) * n))) {
        fprintf(stderr, "erro ao alocar resultados 3\n");
        exit(1);
    }
}

void leMatriz(int n, Intervalo_t* original, Intervalo_t* independentes) {
    /* leitura da matriz */
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%lf", &original[(i * n) + j].maior.d) == 0) {
                fprintf(stderr, "Erro ao ler a entrada.\n");
                exit(1);
            }
            obtemIntervalo(&original[(i * n) + j]);
        }
        if (scanf("%lf", &independentes[i].maior.d) == 0) {
            fprintf(stderr, "Erro ao ler a entrada.\n");
            exit(1);
        }
        obtemIntervalo(&independentes[i]);
    }
}

/**
 * Função que troca as linhas da matriz.
 * troca a linha i pelo pivo atual.
 */
void trocaLinhas(Intervalo_t* matriz, Intervalo_t* independentes, int i, int pivo, int tamanho) {
    // troca linha da matriz
    for (int col = 0; col < tamanho; col++) {
        Intervalo_t temp = matriz[pivo * tamanho + col];
        matriz[pivo * tamanho + col] = matriz[i * tamanho + col];
        matriz[i * tamanho + col] = temp;
    }

    // troca elemento independente
    Intervalo_t aux = independentes[pivo];
    independentes[pivo] = independentes[i];
    independentes[i] = aux;
}

void imprimeVetor(Intervalo_t* vetor, int n) {
    for (int i = 0; i < n; i++) {
        printIntervalo(vetor[i]);
    }
}

void imprimeDados(Intervalo_t* resultado, Intervalo_t* residuo, long int tempo, int n, char *nome, int sessao) {
    printf("\n          %s:\n", nome);
    printf("\nSolução do sistema: [");
    imprimeVetor(resultado, n);
    putchar(']');
    printf("\n\nTempo de execução em milisegundos: %lf \n", tempo/1e6);
    printf("\nResíduos do método: ");
    imprimeVetor(residuo, n);
    printf("\nsessao %d acabou\n", sessao);
}

void liberaMatrizes(Intervalo_t* matriz, Intervalo_t* matriz1, Intervalo_t* matriz2, Intervalo_t* matriz3) {
    free(matriz);
    free(matriz1);
    free(matriz2);
    free(matriz3);
}

void liberaResultados(Intervalo_t* resultado1, Intervalo_t* resultado2, Intervalo_t* resultado3) {
    free(resultado1);
    free(resultado2);
    free(resultado3);
}

void liberaIndependentes(Intervalo_t* independentes, Intervalo_t* independentes1, Intervalo_t* independentes2, Intervalo_t* independentes3) {
    free(independentes);
    free(independentes1);
    free(independentes2);
    free(independentes3);
}

void liberaResiduos(Intervalo_t* residuo1, Intervalo_t* residuo2, Intervalo_t* residuo3) {
    free(residuo1);
    free(residuo2);
    free(residuo3);
}
