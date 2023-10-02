#include <malloc.h>

#include "libDouble.h"
#include "utils.h"

struct ponto {
	Intervalo_t x;  // eixo das abcissas.
	Intervalo_t y;  // u eixo das ordenadas.
};
typedef struct ponto ponto_t;

/* vetor de pontos, coeficientes do SL, independentes do SL, numero de pontos, grau do polinomio */
void nome(ponto_t *xy, Intervalo_t **coeficientes, Intervalo_t *independentes, int_t numPontos, int_t numCoeficientesG) {
	/*  */
	for(int_t i = 0; i < numCoeficientesG; i++) {
		/*  */
		coeficientes[i] = (Intervalo_t *)malloc(numCoeficientesG * sizeof(Intervalo_t));
		for(int_t j = 0; j < numCoeficientesG; j++) {
			/* */
			for(int_t k = 0; k < numPontos; k++) {
				coeficientes[i][j] = somaIntervalos(coeficientes[i][j], mult_intervalos(potenciacao2(xy[k].x, i), potenciacao2(xy[k].x, j)));
			}
		}

		for(int k = 0; k < numPontos; k++) {
			independentes[i] = somaIntervalos(independentes[i], mult_intervalos(potenciacao2(xy[k].x, i), xy[k].y));
		}
	}
}

int main() {
	printf("Olá mundo!\n");

	int_t n = 0, k = 0;
	ponto_t *pontos = NULL;
	Intervalo_t **coeficientes = NULL;
	Intervalo_t *independentes = NULL;

	// Obtém o grau N do polinômio e a quantidade K de pontos.
	scanf("%ld %ld", &n, &k);

	// Inicializa-se um array de K structs.
	pontos = (ponto_t *)malloc(k * sizeof(ponto_t));

	// Inicializa-se uma matriz de n linhas.
	coeficientes = (Intervalo_t **)malloc((n + 1) * sizeof(Intervalo_t *));
	for(int_t i = 0; i < n; i++) {
		coeficientes[i] = (Intervalo_t *)malloc(n * sizeof(Intervalo_t));
	}

	// Inicializa-se um array de K termos independentes, todos com 0.
	independentes = (Intervalo_t *)malloc((n + 1) * sizeof(Intervalo_t));

	// Popula com os pontos e ajusta cada intervalo.
	for(int_t i = 0; i < k; i++) {
		scanf("%lf %lf", &(pontos[i].x.maior.d), &(pontos[i].y.maior.d));
		obtemIntervalo(&(pontos[i].x));
		obtemIntervalo(&(pontos[i].y));
	}

	nome(pontos, coeficientes, independentes, k, n + 1);

	printf("Coeficientes:\n");
	for(int_t i = 0; i <= n; i++) {
		for(int_t j = 0; j <= n; j++) {
			printIntervalo(coeficientes[i][j]);
		}
		printf("\n");
	}


    // eliminacaoGauss(matriz1, independentes1, n);
    // retrossubs(matriz1, independentes1, resultado1, n);
    // residuo1 = calculaResiduo(matriz, independentes, resultado1, n);

	return 0;
}