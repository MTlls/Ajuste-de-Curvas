#ifndef _LIBGAUSS_H_
#define _LIBGAUSS_H_

#include "libDouble.h"

/**
 * Função que encontra a maior linha da coluna i, o critério escolhido foi o intervalo com o maior limite superior. O paramêtro tam é a ordem da matriz quadrada (se espera que seja quadrada).
*/
int encontraMax(Intervalo_t* matriz, int tam, int i);

/**
 * Função que realiza o método de Gauss com pivoteamento parcial para a solução do sistema linear (COM INTERVALOS).
*/
void eliminacaoGauss(Intervalo_t* matriz, Intervalo_t* independentes, int n);

/**
 * Função que realiza a retrosubstituição do sistema linear COM INTERVALOS.
 * OBS: é esperado que o sistema esteja triangularizado, com a linha mais baixo com apenas 1 coeficiente.
*/
void retrossubs(Intervalo_t* matriz, Intervalo_t* independentes, Intervalo_t* variaveis, int n);

/**
 * Função que calcula os resíduo, que é a diferença entre o ponto Yi a função encontrada para Xi, ou seja: Ri = Yi - f(Xi)
*/
Intervalo_t* calculaResiduo(Intervalo_t* solucao, ponto_t* pontos, int_t grau, int_t qntdPontos);

/** 
 * Função que troca a linha i de uma matriz pelo pivo da mesma.
*/
void trocaLinhas(Intervalo_t* matriz, Intervalo_t* independentes, int i, int pivo, int tamanho);

/**
 *  Função que imprime o vetor em uma linha apenas
 * */
void imprimeVetor(Intervalo_t *vetor, int n);

/**
 * Função que imprime o vetor com \n a cada elemento
*/
void imprimeVetorLinha(Intervalo_t* vetor, int n);

#endif