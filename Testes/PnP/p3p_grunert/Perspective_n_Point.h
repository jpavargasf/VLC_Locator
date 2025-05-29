#ifndef PERSPECTIVE_N_POINT
#define PERSPECTIVE_N_POINT


#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

int test_p6p_p4p();

double ***p6p_dlt(uint32_t **pixel_coordinates, double **real_world_coordinates);

//não funcionando direito
double ***p4p(double **K, double **pontos_real, uint32_t ** pontos_sensor);

//farsa
double *p4p_fischler1981(double **K, double pixelSize, double **pontos_real, double **pontos_sensor);

void p4p_fischler1981_test();

double **p3p_grunert(double **K, double **pontos_real, uint32_t **pontos_sensor);


double **p3p_grunert_v2(double **K, double **rX, uint32_t **sX);


void p3p_grunert_test();

void **p4p_grunert(double **K, double **pontos_real, uint32_t **pontos_sensor);

void **p4p_grunert_v2(double **K, double **pontos_real, uint32_t **pontos_sensor);

void p4p_grunert_test();

//encontra a melhor rotação e translação entre dois set points
//de A para B
//no caso A seria rX e B kX
//kX = camera
//rX = real
//dois pontos na forma [x1 x2 x3]
//está implementado para n pontos e k dimensoes mas so foi testado 3x3
//o algoritimo funciona se n_pontos e menor que dimensions, mas nao sei se faz sentido
//usar desta forma
//nao funciona quando todos os pontos tem uma mesma coordinada
double ***optimal_rotation_translation(double **A, double **B, uint32_t n_pontos, uint32_t dimensions);

//apenas para 3D, funciona quando todos os pontos tem uma mesma coordinada
double ***optimal_rotation_translation_3D(double **A, double **B, uint32_t n_pontos, uint32_t dimensions);

//numero de pontos deve ser 3
//double **optimal_rotation_3D(double **A, double **B)

//retorna a matriz de projecao dado
//K(parametros intrinsecos)
//R - matriz de rotacao
//Z - translacao
double **projection_matrix(double **K, double **R, double **Z);

void Rt_test();

double **p4p_dio_gauss_newton(double **dio, double **cos_theta, double **dij);

double **p4p_Xo_gauss_newton(double **Xoi, double **rX, double **dio);

double **p4p_Xo_Levenberg_Marquardt(double **Xoi, double **rX, double **dio);


double ***p3p_Xo_direct_planar(double **dio, double **rX);

double **p4p_Xo_direct(double **dio, double **rX);

double ***p4p_grunert_gauss_newton(double **K, double **pontos_real, uint32_t **pontos_sensor);

double ***p4p_grunert_gauss_newton_v2(double **K, double **rX, uint32_t **sX);


void p4p_grunert_test_v2();

void p4p_grunert_test_v2_ideal();

double **get_kxs(double **K, uint32_t **sX, uint8_t n_pontos);

double **get_cos_matrix_vectos(double **matrix, uint8_t n_pontos);

double **get_Xo(double **dio, double **rX, double **KsX, uint8_t n_pontos);

double **get_R(double **Xo, double **dio, double **rX, double **KsX, uint8_t n_pontos);


double **calibrateCamerav2(double **Xo, uint32_t **sX, double **rX);

double ***get_projection_matrix(double **solutions, double **K, double **sX, double **rX, uint8_t n_pontos);

double **get_R_v2(double **Xo, double *solution, double **rX, double **KsX, uint8_t n_pontos);

#endif // PERSPECTIVE_N_POINT
