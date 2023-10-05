#include "libMatriz.h"
#include "libMatematicaDouble.h"
#include <math.h>

int encontraMax(Intervalo_t* matriz, int tam, int i) {
    int pos = i;

    // Procura o maior limite superior a partir da linha i+1
    for (int j = i+1; j < tam; j++) {
        if (fabs(matriz[(j * tam) + i].maior.d) > fabs(matriz[(i * tam) + i].maior.d)) {
            pos = j;
        }
    }

    return pos;
}

void eliminacaoGauss(Intervalo_t* matriz, Intervalo_t* independentes, int n) {
    for (int i = 0; i < n - 1; i++) {
        int pivo = encontraMax(matriz, n, i);

        // Caso a linha com o maior valor seja outra, realiza o pivoteamento parcial
        if (pivo != i) {
            trocaLinhas(matriz, independentes, i, pivo, n);
        }

        // Encontra o multiplicador m e realiza a subtração das linhas abaixo da atual (i+1)
        for (int k = i + 1; k < n; k++) {
            Intervalo_t m = div_intervalos(matriz[(k * n) + i], matriz[(i * n) + i]);
            matriz[(k * n) + i].menor.i = 0;
            matriz[(k * n) + i].maior.i = 0;

            for (int j = i + 1; j < n; j++) {
                matriz[(k * n) + j] = sub_intervalos(matriz[(k * n) + j], mult_intervalos(matriz[(i * n) + j], m));
            }

            independentes[k] = sub_intervalos(independentes[k], mult_intervalos(independentes[i], m));
        }
    }
}

void solucaoSL(Intervalo_t* matriz, Intervalo_t* independentes, Intervalo_t* solucao, int n) {
    for (int i = n - 1; i >= 0; i--) {
        solucao[i] = independentes[i];

        // Subtrai da solução encontrada na linha abaixo de i.
        // se for a primeira iteração, nem passa pelo laço.
        for (int j = i + 1; j < n; j++) {
            solucao[i] = sub_intervalos(solucao[i], mult_intervalos(matriz[(i * n) + j], solucao[j]));
        }

        // Divide o resultado das subtrações com o termo independente da linha i pelo coeficiente da diagonal da linha i.
        solucao[i] = div_intervalos(solucao[i], matriz[(i * n) + i]);
    }
}

Intervalo_t* calculaResiduo(Intervalo_t* solucao, ponto_t* pontos, int_t grau, int_t qntdPontos) {
    Intervalo_t* residuo = (Intervalo_t*)calloc(qntdPontos, sizeof(Intervalo_t));

    // Para cada ponto, encontra um resíduo (Ri).
    for (int_t i = 0; i < qntdPontos; i++) {
        // f(Xi) = aXi^0
        residuo[i] = solucao[0];
        // f(Xi) = aXi^0 + bXi^1
        residuo[i] = soma_intervalos(residuo[i], mult_intervalos(solucao[1], pontos[i].x));

        // f(Xi) =  aXi^0 + bXi^1 + cX^2 + ... + αX^grau
        for (int_t j = 2; j <= grau; j++) {
            residuo[i] = soma_intervalos(residuo[i], mult_intervalos(solucao[j], potenciacao(pontos[i].x, j)));
        }
        
        // Ri = Yi - f(Xi)
        residuo[i] = sub_intervalos(pontos[i].y, residuo[i]);
    }

    return residuo;
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

void imprimeVetorLinha(Intervalo_t* vetor, int n) {
    for (int i = 0; i < n; i++) {
        printIntervalo(vetor[i]);
        putchar('\n');
    }
}

void geraSLMinimosQuadrados(ponto_t *xy, Intervalo_t *coeficientes, Intervalo_t *independentes, int_t numPontos, int_t numCoeficientesG) {
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
