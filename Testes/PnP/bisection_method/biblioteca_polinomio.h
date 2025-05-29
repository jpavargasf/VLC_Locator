//Autor: João Paulo Vargas da Fonseca
//UNIVERSIDADE  TECNOLÓGICA FEDERAL DO PARANÁ - UTFPR
//TCC
#ifndef BIBLIOTECA_POLINOMIO_H
#define BIBLIOTECA_POLINOMIO_H

#include<stdlib.h>
#include<stdint.h>

//#define BISECTION_SPECIALIZED 1


void biblioteca_polinomio_test();

double *dividir_polinomio(double *polinomio, uint32_t ordem, double raiz);

double *bisection_method(double *polinomio, uint32_t ordem, double erro);

double *bisection_find_interval(double *polinomio, uint32_t ordem);

double bisection_find_root(double *polinomio, uint32_t ordem, double erro);

double function_value(double *polinomio, uint32_t ordem, double x);

void print_polinomio(double *polinomio, uint32_t ordem);

double *intervalo_todas_raizes(double *polinomio, uint32_t ordem);

double **quartic_function_roots(double *polinomio, uint8_t ordem);

double *derivative(double *polinomio, uint32_t ordem);

double **global_newton_method(double *polinomio, uint32_t ordem, double error);

#endif // BIBLIOTECA_POLINOMIO_H
