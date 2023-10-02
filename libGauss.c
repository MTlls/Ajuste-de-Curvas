#include "libGauss.h"
#include "libDouble.h"

int encontraMax(Intervalo_t* matriz, int tam, int i) {
    int pos = i;

    for (int j = i; j < tam; j++) {
        if (fabs(matriz[(j * tam) + i]) > fabs(matriz[(i * tam) + i])) {
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
            Intervalo_t m = matriz[(k * n) + i] / matriz[(i * n) + i];
            matriz[(k * n) + i] = 0;
            for (int j = i + 1; j < n; j++) {
                matriz[(k * n) + j] -= matriz[(i * n) + j] * m;
            }
            independentes[k] -= independentes[i] * m;
        }
    }
}

void eliminacaoGaussSemMultiplicador(Intervalo_t* matriz, Intervalo_t* independentes, int n) {
    for (int i = 0; i < n - 1; i++) {
        int pivo = encontraMax(matriz, n, i);

        if (pivo != i) {
            trocaLinhas(matriz, independentes, i, pivo, n);
        }

        for (int k = i + 1; k < n; k++) {
            for (int j = i + 1; j < n; j++) {
                matriz[(k * n) + j] = (matriz[(k * n) + j] * matriz[(i * n) + i]) - (matriz[(i * n) + j] * matriz[(k * n) + i]);
            }
            matriz[(k * n) + i] = 0;
            independentes[k] = (matriz[(i * n) + i] * independentes[k]) - (independentes[i] * matriz[(k * n) + i]);
        }
    }
}

void semPivoteamento(Intervalo_t* matriz, Intervalo_t* independentes, int n) {
    Intervalo_t pivo = 0.0;
    // qntd maxima de multiplicadores e n-1
    Intervalo_t m[n - 1];

    for (int i = 0; i < n - 1; i++) {
        // captura o pivo
        pivo = matriz[(i * n) + i];
        // valor do pivo sempre sera 1 depois ad divisao
        matriz[(i * n) + i] = 1;

        // salva o termo independente
        independentes[i] /= pivo;

        // realiza-se a divisao da linha do pivo, enquanto armazena os multiplicadores
        for (int j = i; j < n - 1; j++) {
            // nova linha do pivo dividida pelo pivo
            matriz[(i * n) + (j + 1)] /= pivo;

            // armazenado o multiplicador
            m[j - i] = matriz[((j + 1) * n) + i];

            // Zeramento da coluna abaixo do pivo
            matriz[((j + 1) * n) + i] = 0;
        }

        // realiza-se a subtração dos coeficientes
        for (int k = i; k < n - 1; k++) {
            // subtracao do termo independente
            independentes[k + 1] -= (m[k - i] * independentes[i]);

            // se o multiplicador encontrar um 0, não havera mudancas na coluna
            if (matriz[(i * n) + k + 1] == 0) {
                break;
            }

            // mudança da parte abaixo da linha do pivo (o anulamento foi feito acima no codigo)
            for (int j = i + 1; j < n; j++) {
                matriz[(j * n) + (k + 1)] -= ((m[j - (i + 1)]) * matriz[(i * n) + k + 1]);
            }
        }
    }
}

void retrossubs(Intervalo_t* matriz, Intervalo_t* independentes, Intervalo_t* variaveis, int n) {
    for (int i = n - 1; i >= 0; i--) {
        variaveis[i] = independentes[i];
        for (int j = i + 1; j < n; j++) {
            variaveis[i] -= matriz[(i * n) + j] * variaveis[j];
        }
        variaveis[i] /= matriz[(i * n) + i];
    }
}

Intervalo_t* calculaResiduo(Intervalo_t* matriz, Intervalo_t* independentes, Intervalo_t* solucao, int n) {
    Intervalo_t* residuo = (Intervalo_t*)calloc(n, sizeof(Intervalo_t));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            residuo[i] += (matriz[(i * n) + j] * solucao[j]);
        }
        residuo[i] -= independentes[i];
    }

    return residuo;
}