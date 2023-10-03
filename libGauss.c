#include "libGauss.h"
#include "libDouble.h"
#include "libMatriz.h"

int encontraMax(Intervalo_t* matriz, int tam, int i) {
    int pos = i;

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

        if (pivo != i) {
            trocaLinhas(matriz, independentes, i, pivo, n);
        }

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

void retrossubs(Intervalo_t* matriz, Intervalo_t* independentes, Intervalo_t* variaveis, int n) {
    for (int i = n - 1; i >= 0; i--) {
        variaveis[i] = independentes[i];
        for (int j = i + 1; j < n; j++) {
            variaveis[i] = sub_intervalos(variaveis[i], mult_intervalos(matriz[(i * n) + j], variaveis[j]));
        }
        variaveis[i] = div_intervalos(variaveis[i], matriz[(i * n) + i]);
    }
}

Intervalo_t* calculaResiduo(Intervalo_t* matriz, Intervalo_t* independentes, Intervalo_t* solucao, int n) {
    Intervalo_t* residuo = (Intervalo_t*)calloc(n, sizeof(Intervalo_t));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            residuo[i] = soma_intervalos(residuo[i], mult_intervalos(matriz[(i * n) + j] , solucao[j]));
        }
        residuo[i] = sub_intervalos(residuo[i], independentes[i]);
    }

    return residuo;
}