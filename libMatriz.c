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
	// Temos 2(n-1)-1 = 2n-2-1 = 2n-3 coeficientes que se repetem.
	int_t numeroRepeticoes;
    int_t ult_linha , grauN;
    Intervalo_t *repetidos;
    numeroRepeticoes = (2 * numCoeficientesG) - 3;
	repetidos = (Intervalo_t *)calloc(numeroRepeticoes, sizeof(Intervalo_t));
    
    // Linha0 Col0 é a quantidade de pontos.
    coeficientes[0].maior.d = (double)numPontos;
    coeficientes[0].menor.d = (double)numPontos;

    ult_linha = (numCoeficientesG -1) * (numCoeficientesG);
    grauN = numCoeficientesG - 1; 

    // Necessario apenas a primeira linha inteira [0..n] e na ultima linha [1..n], que é a linha final inteira menos o termo da diagonal inversa, que é o mesmo termo do final da primeira linha.

    // Começa em [0][1], pois ja foi computado o [0][0]
    for(int_t j = 1; j < numCoeficientesG; j++) {
        // Necessário apenas Σ(Xi^k)
		for(int_t k = 0; k < numPontos; k++) {
			coeficientes[j] = soma_intervalos(coeficientes[j], potenciacao(xy[k].x, j));
		}
        // Copia as repetições
        repetidos[j-1] = coeficientes[j];
    }

    // Começa em [n-1][1], pois ja foi computado o [n-1][0]
    // Vai até Σ(X^(n+n-1))
	for(int_t j = 1; j < numCoeficientesG-1; j++) {
		// Necessário apenas Σ(Xi^k)
		for(int_t k = 0; k < numPontos; k++) {
			coeficientes[(ult_linha) + j] = soma_intervalos(coeficientes[(ult_linha) + j], mult_intervalos(potenciacao(xy[k].x, (grauN)), potenciacao(xy[k].x, j)));
		}

        // Copia as repetições
		repetidos[(numCoeficientesG - 2) + j] = coeficientes[(ult_linha) + j];
	}

	// Σ(X^(n+n)) que sobrou
	for(int_t k = 0; k < numPontos; k++) {
	    coeficientes[(ult_linha) + numCoeficientesG-1] = soma_intervalos(coeficientes[(ult_linha) + numCoeficientesG-1], mult_intervalos(potenciacao(xy[k].x, (grauN)), potenciacao(xy[k].x, numCoeficientesG-1)));
	}

    // escreve dos coeficientes pelo triangulo superior
    // cCopiado para o coeficiente copiado em repetidos[]
    int_t cCopiado, linhaCopia, colunaCopia;
    for (cCopiado = 1; cCopiado < numCoeficientesG; cCopiado++) {
        for (linhaCopia = 1, colunaCopia = cCopiado-1; colunaCopia >= 0; linhaCopia++, colunaCopia--) {
            coeficientes[(linhaCopia * numCoeficientesG) + colunaCopia] = repetidos[cCopiado-1]; 
        }
    }

    int_t copiasFeitas = 0;
    // Copia os coeficientes da parte superior e inferior da matriz
    for (cCopiado = numCoeficientesG -1; cCopiado < numeroRepeticoes; cCopiado++) {
        for (linhaCopia = numCoeficientesG -1, colunaCopia = copiasFeitas+1; colunaCopia < numCoeficientesG; linhaCopia--, colunaCopia++) {
            coeficientes[(linhaCopia * numCoeficientesG) + colunaCopia] = repetidos[cCopiado];
        }   
        copiasFeitas++;
    }

    // Calculo dos termos independentes em separado para não ficar tão ilegível
    for (int_t i = 0; i < numCoeficientesG; i++) {
		for(int k = 0; k < numPontos; k++) {
			independentes[i] = soma_intervalos(independentes[i], mult_intervalos(potenciacao(xy[k].x, i), xy[k].y));
		}
	}

    free(repetidos);
}
