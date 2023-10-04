#include <malloc.h>

#include "libDouble.h"
#include "utils.h"
#include "libGauss.h"
#include "likwid.h"

/* vetor de pontos, coeficientes do SL, independentes do SL, numero de pontos, grau do polinomio */
void nome(ponto_t *xy, Intervalo_t *coeficientes, Intervalo_t *independentes, int_t numPontos, int_t numCoeficientesG) {
	for(int_t i = 0; i < numCoeficientesG; i++) {

		for(int_t j = 0; j < numCoeficientesG; j++) {
			
			for(int_t k = 0; k < numPontos; k++) {
				coeficientes[(i * numCoeficientesG) + j] = soma_intervalos(coeficientes[(i * numCoeficientesG) + j], mult_intervalos(potenciacao(xy[k].x, i), potenciacao(xy[k].x, j)));
			}
		}

		for(int k = 0; k < numPontos; k++) {
			independentes[i] = soma_intervalos(independentes[i], mult_intervalos(potenciacao(xy[k].x, i), xy[k].y));
		}
	}
}

int main() {
	int_t n = 0, k = 0;
	real_t tempoGeraSL, tempoSolSL;
	ponto_t *pontos = NULL;
	Intervalo_t *coeficientes = NULL;
	Intervalo_t *independentes = NULL;
	Intervalo_t *solucao = NULL;
	Intervalo_t *residuo = NULL;


    // Inicializa o marcador do likwid
    LIKWID_MARKER_INIT;

	// Obtém o grau N do polinômio e a quantidade K de pontos.
	if(scanf("%ld %ld", &n, &k) == 0){
		fprintf(stderr, "Erro ao ler a entrada.\n");
        exit(1);
    }
	

	// Inicializa-se um array de K structs.
	pontos = (ponto_t *)calloc(k, sizeof(ponto_t));

	// Inicializa-se um vetor 2d de (n+1)^2 linhas.
	coeficientes = (Intervalo_t *) calloc(((n+1)*(n+1)), sizeof(Intervalo_t));

	// Inicializa-se um array de K termos independentes, todos com 0.
	independentes = (Intervalo_t *) calloc((n + 1), sizeof(Intervalo_t));

	// Popula com os pontos e ajusta cada intervalo.
	for(int_t i = 0; i < k; i++) {
		if(scanf("%lf %lf", &(pontos[i].x.maior.d), &(pontos[i].y.maior.d)) == 0){
			fprintf(stderr, "Erro ao ler a entrada.\n");
        	exit(1);
    	}
		obtemIntervalo(&(pontos[i].x));
		obtemIntervalo(&(pontos[i].y));
	}

	// Essa função é responsável por gerar os coeficientes e termos independentes do SL

	nome(pontos, coeficientes, independentes, k, (n + 1));

	printf("Coeficientes:\n");
	for(int_t i = 0; i < n+1; i++) {
		for(int_t j = 0; j < n+1; j++) {
			printIntervalo(coeficientes[((n+1)* i) + j]);
			putchar(' ');
		}
		printf("\n");
	}

	
    // Marcador para a geração dos coeficientes e dos termos independentes
    LIKWID_MARKER_START("GERACAO_SL");

	tempoGeraSL.d = timestamp();
	eliminacaoGauss(coeficientes, independentes, (n + 1));
    tempoGeraSL.d = timestamp() - tempoGeraSL.d;
    LIKWID_MARKER_STOP("GERACAO_SL");
	

	solucao = (Intervalo_t *)calloc((n + 1), sizeof(Intervalo_t));

	// Marcador para a solucao do SL
    LIKWID_MARKER_START("SOLUCAO_SL");
	
	tempoSolSL.d = timestamp();
	retrossubs(coeficientes, independentes, solucao, (n + 1));
	tempoSolSL.d = timestamp() - tempoSolSL.d;

	LIKWID_MARKER_STOP("SOLUCAO_SL");
	
	// Aloca os resíduos
	residuo = calculaResiduo(solucao, pontos, n, k);

    // Fecha o marcador do likwid
    LIKWID_MARKER_CLOSE;
	
	printf("\nResíduo:\n");
	imprimeVetorLinha(residuo, k);

	putchar('\n');
	printf("tgeraSL: %lf\n", tempoGeraSL.d);
	printf("tsolSL: %lf\n", tempoSolSL.d);
    
	free(pontos);
	free(coeficientes);
	free(independentes);
	free(solucao);
	free(residuo);

	return 0;
}