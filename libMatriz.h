#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "libDouble.h"
#ifndef __libMatriz__
#define __libMatriz__

void alocaMatrizes(Intervalo_t** original, Intervalo_t** matriz1, Intervalo_t** matriz2, Intervalo_t** matriz3, int n);

void alocaIndependentes(Intervalo_t **independentes, Intervalo_t **independentes1, Intervalo_t **independentes2, Intervalo_t **independentes3, int n);

void alocaResultados(Intervalo_t** variaveis1, Intervalo_t** variaveis2, Intervalo_t ** variaveis3, int n);

void leMatriz(int n, Intervalo_t* original, Intervalo_t* independentes);

void imprimeMatriz(int n, Intervalo_t* matriz, Intervalo_t* independentes);

void trocaLinhas(Intervalo_t* matriz, Intervalo_t* independentes, int i, int pivo, int tamanho);

void imprimeVetor(Intervalo_t *vetor, int n);

void imprimeDados(Intervalo_t *resultado, Intervalo_t *residuo, long int tempo, int n, char *nome, int sessao);

void liberaMatrizes(Intervalo_t *matriz, Intervalo_t *matriz1, Intervalo_t *matriz2, Intervalo_t *matriz3);

void liberaResultados(Intervalo_t *resultado1, Intervalo_t *resultado2, Intervalo_t *resultado3);

void liberaIndependentes(Intervalo_t *independentes, Intervalo_t *independentes1, Intervalo_t *independentes2, Intervalo_t *independentes3);

void liberaResiduos(Intervalo_t *residuo1, Intervalo_t *residuo2, Intervalo_t *residuo3);  

#endif