#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <math.h>

//alterar eigenvector para baixar o eps se todos forem nulos, e tomar cuidado quando tiver mais de uma linha ou coluna nula
static const double eps  = 0x1p-20;


//fazer com que se o erro aumentar no eigenvalues, parar a função, porque provavalmente os autovalores
//são complexos

//a partir de agora fazer teste apenas com matriz simetrica -> autovalores reais!!

double **matrix_create_random(uint32_t height, uint32_t width, double min, double max);

double **matrix_create_random_int(uint32_t height, uint32_t width, uint8_t symmetric, int32_t min, int32_t max);

double **matrix_mult(double **A, double **B, uint32_t heightA, uint32_t widthA, uint32_t heightB, uint32_t widthB);

double **matrix_transpose(double **A, uint32_t heightA, uint32_t widthA);

double **matrix_inverse(double **A, uint32_t heightA, uint32_t widthA);

double ***qr_decomposition(double **A, uint32_t heightA, uint32_t widthA);

double *eigenvalues(double **A, uint32_t heightA, uint32_t widthA);

double **eigenvector(double **A, uint32_t heightA, uint32_t widthA, double eigenvalue);

double ***svd_decomposition(double **A, uint32_t heightA, uint32_t widthA);

void matrix_print(double **A, uint32_t heightA, uint32_t widthA);
void matrix_print_int(uint32_t **A, uint32_t heightA, uint32_t widthA);

void matrix_free(double **A, uint32_t heightA);

uint8_t matrix_equal(double **A, double **B, uint32_t heightA, uint32_t widthA, uint32_t heightB, uint32_t widthB);

#define PRINT_MATRIX 1
uint8_t matrix_test();

//encontra o centroid de n pontos
//forma [v1 v2 v3]
double **centroid(double **points, uint32_t dimensions, uint32_t n_points);

double **matrix_copy(double **matrix, uint32_t height, uint32_t width);

//calcula a determinante atraves da decomposicao QR -> det(A) = det(Q) * det(R) = 1 * det(R)
double *matrix_determinant(double **matrix, uint32_t height, uint32_t width);

double **cross_product(double **A, uint32_t columnA, double **B, uint32_t columnB, uint32_t dimension);

double **matrix_create_double(uint32_t height, uint32_t width);

double **matrix_uint32_t_to_double(uint32_t **matrix, uint32_t height, uint32_t width);

double **matrix_identity(uint32_t dimension);

#endif // MATRIX_H
