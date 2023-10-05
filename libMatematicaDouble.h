#ifndef _LIBMATEMATICADOUBLE_H_
#define _LIBMATEMATICADOUBLE_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

typedef struct {
    real_t menor;
    real_t maior;
} Intervalo_t; 

struct ponto {
	Intervalo_t x;  // eixo das abcissas.
	Intervalo_t y;  // eixo das ordenadas.
};
typedef struct ponto ponto_t;

/* Imprime um intervalo */
void printIntervalo(Intervalo_t intervalo);

/**
 * Imprime uma operação entre intervalos
*/
void printOperacao(Intervalo_t a, char op, Intervalo_t b);

/**
 * Soma de dois numeros real_t
*/
double soma(real_t a, real_t b);

/**
 * Multiplicação de dois números real_t
*/
double multiplica(real_t a, real_t b);

/**
 * Subtração de dois números real_t
*/
double sub(real_t a, real_t b);

/**
 * Divisão de dois números real_t
*/
double divisao(real_t a, real_t b);

/**
 * Função que ajusta o intervalo
*/
void obtemIntervalo(Intervalo_t *a);

/**
 * Função que multiplica dois intervalos.
*/
Intervalo_t mult_intervalos(Intervalo_t a, Intervalo_t b);

/**
 * Inverte o intervalo enviado para futura divisão.
 */
Intervalo_t inverte(Intervalo_t x);

/**
 * Obtem a quantidade de números representáveis no intervalo
*/
int obtemULPs(Intervalo_t x);

/**
 * Obtem o erro absoluto no intervalo
*/
double erroAbs(Intervalo_t x);

/**
 * Obtem o erro realtivo no intervalo
*/
double erroRelativo(Intervalo_t x);

/**
 * Função que calcula a potencia de um intervalo a um grau N.
*/
Intervalo_t potenciacao(Intervalo_t a, int_t n);

/**
 * Função que retorna a soma de dois intervalos.
*/
Intervalo_t soma_intervalos(Intervalo_t a, Intervalo_t b);

/**
 * Realiza a divisão de intervalos
 */
Intervalo_t div_intervalos(Intervalo_t a, Intervalo_t b);

/**
 * Função que retorna a subtração de dois intervalos.
*/
Intervalo_t sub_intervalos(Intervalo_t a, Intervalo_t b);

/**
 * Realiza a multiplicação de intervalos
 */
Intervalo_t mult_intervalos(Intervalo_t a, Intervalo_t b);

/**
 * Função que captura o mínimo entre 4 valores double
*/
double min(real_t a, real_t b, real_t c, real_t d);

/**
 * Função que captura o mínimo entre 4 valores double
*/
double max(real_t a, real_t b, real_t c, real_t d);

/**
 * Função que retorna o máximo entre 2 valores double
*/
double maxBetween2(double a, double b);

#endif