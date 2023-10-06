#include <malloc.h>

#include "libMatematicaDouble.h"
#include "utils.h"
#include "libMatriz.h"
#include "likwid.h"

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

    // Marcador para a geração dos coeficientes e dos termos independentes
    LIKWID_MARKER_START("GERACAO_SL");

	tempoGeraSL.d = timestamp();
	geraSLMinimosQuadrados(pontos, coeficientes, independentes, k, (n + 1));
	eliminacaoGauss(coeficientes, independentes, (n + 1));
    tempoGeraSL.d = timestamp() - tempoGeraSL.d;
    LIKWID_MARKER_STOP("GERACAO_SL");
	

	solucao = (Intervalo_t *)calloc((n + 1), sizeof(Intervalo_t));

	// Marcador para a solucao do SL
    LIKWID_MARKER_START("SOLUCAO_SL");
	
	tempoSolSL.d = timestamp();
	solucaoSL(coeficientes, independentes, solucao, (n + 1));
	tempoSolSL.d = timestamp() - tempoSolSL.d;

	LIKWID_MARKER_STOP("SOLUCAO_SL");
	
    // Fecha o marcador do likwid
    LIKWID_MARKER_CLOSE;

	// Imprime a solução
	printf("\nSolução:\n");
	imprimeVetor(solucao, (n+1));

	// Aloca os resíduos
	residuo = calculaResiduo(solucao, pontos, n, k);
	
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