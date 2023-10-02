#ifndef _LIBGAUSS_H_
#define _LIBGAUSS_H_

#include "libDouble.h"

int encontraMax(Intervalo_t* matriz, int tam, int i);

void eliminacaoGauss(Intervalo_t* matriz, Intervalo_t* independentes, int n);

void eliminacaoGaussSemMultiplicador(Intervalo_t* matriz, Intervalo_t* independentes, int n);

void semPivoteamento(Intervalo_t* matriz, Intervalo_t* independentes, int n);

void retrossubs(Intervalo_t* matriz, Intervalo_t* independentes, Intervalo_t* variaveis, int n);

Intervalo_t* calculaResiduo(Intervalo_t* matriz, Intervalo_t* independentes, Intervalo_t* solucao, int n);

#endif