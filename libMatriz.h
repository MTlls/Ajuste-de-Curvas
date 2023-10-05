#ifndef _LIBMATRIZ_H_
#define _LIBMATRIZ_H_

#include "libMatematicaDouble.h"

/**
 * Função que encontra a maior linha da coluna i, o critério escolhido foi o intervalo com o maior limite superior. O paramêtro tam é a ordem da matriz quadrada (se espera que seja quadrada).
*/
int encontraMax(Intervalo_t* matriz, int tam, int i);

/**
 * Função que realiza o método de Gauss com pivoteamento parcial para a solução do sistema linear (COM INTERVALOS).
*/
void eliminacaoGauss(Intervalo_t* matriz, Intervalo_t* independentes, int n);

/**
 * Função que realiza a retrosubstituição do sistema linear COM INTERVALOS e retorna a solucao do sistema no parametro solucao.
 * OBS: é esperado que o sistema esteja triangularizado, com a linha mais baixo com apenas 1 coeficiente.
*/
void solucaoSL(Intervalo_t* matriz, Intervalo_t* independentes, Intervalo_t* solucao, int n);

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

/**
 * Função que gera os coeficientes e os termos independentes do SL, utilizando-se do método dos mínimos quadrados. Mas sem a repetição dos somatorios
 * OBS: com intervalos.
*/
void geraSLMinimosQuadrados(ponto_t *xy, Intervalo_t *coeficientes, Intervalo_t *independentes, int_t numPontos, int_t numCoeficientesG);

#endif