#ifndef _LIBDOUBLE_H_
#define _LIBDOUBLE_H_

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

typedef struct {
    real_t menor;
    real_t maior;
} Intervalo_t; 

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

Intervalo_t escolheOperacao(Intervalo_t *a, char op, Intervalo_t *b);

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
 * Funcao que zera n intervalos
*/
void zeraIntervalos(Intervalo_t *intervalos, int n);

/**
 * Funcao que calcula a potencia de um intervalo a um grau N.
*/
void potenciacao(Intervalo_t a, int n);

Intervalo_t potenciacao2(Intervalo_t a, int n);

/**
 * Função que retorna a soma de dois intervalos.
*/
Intervalo_t somaIntervalos(Intervalo_t a, Intervalo_t b);
#endif