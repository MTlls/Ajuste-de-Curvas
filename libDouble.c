#include "libDouble.h"
#include "utils.h"
#include <math.h>

void printIntervalo(Intervalo_t intervalo) {
	printf("[%15.8e, %15.8e]", intervalo.menor.d, intervalo.maior.d);
}

double soma(real_t a, real_t b) {
	return a.d + b.d;
}


real_t mult(real_t a, real_t b) {
	real_t aux;
	aux.d = a.d * b.d;
	return aux;
}

double multiplica(real_t a, real_t b) {
	return a.d * b.d;
}

double sub(real_t a, real_t b) {
	return (a.d - b.d);
}

double divisao(real_t a, real_t b) {
	return a.d / b.d;
}

double min(real_t a, real_t b, real_t c, real_t d) {
	double min = a.d;

	if(b.d < min) {
		min = b.d;
	}
	if(c.d < min) {
		min = c.d;
	}
	if(d.d < min) {
		min = d.d;
	}

	return min;
}

double max(real_t a, real_t b, real_t c, real_t d) {
	double max = a.d;

	if(b.d > max) {
		max = b.d;
	}
	if(c.d > max) {
		max = c.d;
	}
	if(d.d > max) {
		max = d.d;
	}

	return max;
}

Intervalo_t soma_intervalos(Intervalo_t a, Intervalo_t b) {
	Intervalo_t resultado;

    resultado.menor.d = soma(a.menor, b.menor);
	resultado.maior.d = soma(a.maior, b.maior);

    return resultado;
}

Intervalo_t sub_intervalos(Intervalo_t a, Intervalo_t b) {
	Intervalo_t resultado;

	resultado.menor.d = sub(a.menor, b.maior);
	resultado.maior.d = sub(a.maior, b.menor);

    return resultado;
}

void obtemIntervalo(Intervalo_t *a) {
	// se for 0 e positivo:
	// 0 < num < (proxima representação > 0)
	if(a->maior.i == 0) {
		a->maior.d = nextafter(a->maior.d, INFINITY);
		return;
	}
	// se for diferente de 0 (em representacao inteira).
	a->menor.d = nextafter(a->maior.d, -INFINITY);
}

Intervalo_t inverte(Intervalo_t x) {
	Intervalo_t invertido;
	invertido.menor.d = 1 / x.menor.d;
	invertido.maior.d = 1 / x.maior.d;
	return invertido;
}

Intervalo_t mult_intervalos(Intervalo_t a, Intervalo_t b) {
	Intervalo_t resultado;
	//[min{a*c,a*d,b*c,b*d}, max{a*c,a*d,b*c,b*d}]
	resultado.menor.d = min(mult(a.menor, b.menor), mult(a.menor, b.maior),
	                        mult(a.maior, b.menor), mult(a.maior, b.maior));
	resultado.maior.d = max(mult(a.menor, b.menor), mult(a.menor, b.maior),
	                        mult(a.maior, b.menor), mult(a.maior, b.maior));

	return resultado;
}

Intervalo_t div_intervalos(Intervalo_t a, Intervalo_t b) {
	Intervalo_t resultado = mult_intervalos(a, inverte(b));
	if(resultado.maior.d == INFINITY)
		resultado.menor.d = -INFINITY;
	return resultado;
}

int obtemULPs(Intervalo_t x) {
	return fabs(x.maior.i - x.menor.i) - 1;
}

double erroAbs(Intervalo_t x) {
	return sub(x.maior, x.menor);
}

double erroRelativo(Intervalo_t x) {
	return erroAbs(x) / x.menor.d;
}

double maxBetween2(double a, double b) {
    if(a > b) {
        return a;
    }
    return b;
}

Intervalo_t potenciacao(Intervalo_t a, int_t n) {
	Intervalo_t resultado = a;

    if(n == 0) {
		resultado.menor.d = 1;
		resultado.maior.d = 1;
		return resultado;
	}

	if(n % 2 != 0) {
        resultado.menor.d = pow(a.menor.d, n);
        resultado.maior.d = pow(a.maior.d, n);
        return resultado;
	}
    /* n é par */
    /* a >= 0 */
    if (a.menor.d >= 0){
        resultado.menor.d = pow(a.menor.d, n);
        resultado.maior.d = pow(a.maior.d, n);
        return resultado;
    } 
    if (a.maior.d < 0){
        resultado.menor.d = pow(a.maior.d, n);
        resultado.maior.d = pow(a.menor.d, n);
        return resultado;
    }
    if (a.menor.d < 0 && a.maior.d >= 0){
        resultado.menor.d = 0;
        resultado.maior.d = maxBetween2(a.maior.d, a.menor.d);
        return resultado;
    }
	return resultado;
}