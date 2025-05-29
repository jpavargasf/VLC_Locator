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

double ***p6p_dlt(uint32_t **pixel_coordinates, double **real_world_coordinates);

double ***p4p(double **K, double **pontos_real, uint32_t ** pontos_sensor);

double *p4p_fischler1981(double **K, double pixelSize, double **pontos_real, double **pontos_sensor);

void p4p_fischler1981_test();

int main()
{
    srand(time(NULL));
    printf("Hello world!\n");

    //criando os pontos

    double **K_mean;
    K_mean = (double **) malloc(3 * sizeof(double*));
    for(uint8_t i = 0; i < 3; i++){
        K_mean[i] = (double*) malloc(3 * sizeof(double));
        for(uint8_t j = 0; j < 3; j++){
            K_mean[i][j] = 0;
        }
    }

    double *c, *m, *s, *xh, *yh;
    c = (double*) malloc(5 * sizeof(double));
    m = (double*) malloc(5 * sizeof(double));
    s = (double*) malloc(5 * sizeof(double));
    xh = (double*) malloc(5 * sizeof(double));
    yh = (double*) malloc(5 * sizeof(double));

    uint32_t **pontos_sensor_teste;
    double **pontos_real_teste;
    double **z;

    z = (double**) malloc(3 * sizeof(double));
    for(uint32_t i = 0; i < 3; i++){
        z[i] = (double*) malloc(1 * sizeof(double));
    }

    pontos_sensor_teste = (uint32_t**) malloc(2 * sizeof(uint32_t*));
    pontos_real_teste = (double**) malloc(2 * sizeof(double*));

    for(uint32_t i = 0; i < 2; i++){
        pontos_real_teste[i] = (double*) malloc(4 * sizeof(double));
        pontos_sensor_teste[i] = (uint32_t*) malloc(3 * sizeof(uint32_t));
    }

    uint32_t **pontos_sensor;
    double **pontos_real;
    pontos_sensor = (uint32_t**) malloc(6 * sizeof(uint32_t*));
    pontos_real = (double**) malloc(6 * sizeof(double*));

    for(uint32_t i = 0; i < 6; i++){
        pontos_real[i] = (double*) malloc(4 * sizeof(double));
        pontos_sensor[i] = (uint32_t*) malloc(3 * sizeof(uint32_t));
    }

    //1
    pontos_real[0][0] = 0;pontos_real[0][1] = 0;pontos_real[0][2] = 0;pontos_real[0][3] = 1;
    //2
    pontos_real[1][0] = -0.047;pontos_real[1][1] = 0.163;pontos_real[1][2] = 0;pontos_real[1][3] = 1;
    //4
    pontos_real[2][0] = 0.227;pontos_real[2][1] = -0.015;pontos_real[2][2] = 0.15;pontos_real[2][3] = 1;
    //5
    pontos_real[3][0] = 0.237;pontos_real[3][1] = 0.315;pontos_real[3][2] = 0.15;pontos_real[3][3] = 1;
    //6
    pontos_real[4][0] = 0.459;pontos_real[4][1] = 0.328;pontos_real[4][2] = 0.15;pontos_real[4][3] = 1;
    //7
    pontos_real[5][0] = 0.507;pontos_real[5][1] = 0.11;pontos_real[5][2] = 0.15;pontos_real[5][3] = 1;


    //3
    pontos_real_teste[0][0] = 0.022;pontos_real_teste[0][1] = 0.328;pontos_real_teste[0][2] = 0;pontos_real_teste[0][3] = 1;
    //8
    pontos_real_teste[1][0] = 0.472;pontos_real_teste[1][1] = -0.07;pontos_real_teste[1][2] = 0.15;pontos_real_teste[1][3] = 1;

    for(uint32_t n = 0; n < 5; n++){
        printf("\n\n\n\n\n\nPONTO");
        putchar('_');
        for(uint8_t k = 0; k < 50; k++){
            putchar('0' + n + 1);
            putchar('_');
        }
        putchar('\n');

        switch(n){
            case 0:
                //pontos referentes a P1
                //1
                pontos_sensor[0][0] = 2677;pontos_sensor[0][1] = 1328;pontos_sensor[0][2] = 1;
                //2
                pontos_sensor[1][0] = 2711;pontos_sensor[1][1] = 1865;pontos_sensor[1][2] = 1;
                //4
                pontos_sensor[2][0] = 1834;pontos_sensor[2][1] = 1105;pontos_sensor[2][2] = 1;
                //5
                pontos_sensor[3][0] = 1596;pontos_sensor[3][1] = 2143;pontos_sensor[3][2] = 1;
                //6
                pontos_sensor[4][0] = 1036;pontos_sensor[4][1] = 1960;pontos_sensor[4][2] = 1;
                //7
                pontos_sensor[5][0] = 1031;pontos_sensor[5][1] = 1295;pontos_sensor[5][2] = 1;



                //3
                pontos_sensor_teste[0][0] = 2388;pontos_sensor_teste[0][1] = 2283;pontos_sensor_teste[0][2] = 1;
                //8
                pontos_sensor_teste[1][0] = 1181;pontos_sensor_teste[1][1] = 966;pontos_sensor_teste[1][2] = 1;


                //p8
                //x = 1050 y = 1274
                //p3
                //x = 2685 y = 1942

                z[0][0] = -0.3;z[1][0] = 0;z[2][0] = 1;
                break;
            case 1:
                //pontos referentes a P4
                //1
                pontos_sensor[0][0] = 2269;pontos_sensor[0][1] = 1593;pontos_sensor[0][2] = 1;
                //2
                pontos_sensor[1][0] = 2157;pontos_sensor[1][1] = 2087;pontos_sensor[1][2] = 1;
                //4
                pontos_sensor[2][0] = 1427;pontos_sensor[2][1] = 1269;pontos_sensor[2][2] = 1;
                //5
                pontos_sensor[3][0] = 950;pontos_sensor[3][1] = 2218;pontos_sensor[3][2] = 1;
                //6
                pontos_sensor[4][0] = 297;pontos_sensor[4][1] = 1857;pontos_sensor[4][2] = 1;
                //7
                pontos_sensor[5][0] = 360;pontos_sensor[5][1] = 1134;pontos_sensor[5][2] = 1;



                //3
                pontos_sensor_teste[0][0] = 1735;pontos_sensor_teste[0][1] = 2360;pontos_sensor_teste[0][2] = 1;
                //8
                pontos_sensor_teste[1][0] = 606;pontos_sensor_teste[1][1] = 808;pontos_sensor_teste[1][2] = 1;


                //p8
                //x = 1050 y = 1274
                //p3
                //x = 2685 y = 1942

                z[0][0] = 0;z[1][0] = -0.3;z[2][0] = 0.9;
                break;
            case 2:
                //pontos referentes a P3
                //1
                pontos_sensor[0][0] = 2499;pontos_sensor[0][1] = 953;pontos_sensor[0][2] = 1;
                //2
                pontos_sensor[1][0] = 2770;pontos_sensor[1][1] = 1390;pontos_sensor[1][2] = 1;
                //4
                pontos_sensor[2][0] = 1665;pontos_sensor[2][1] = 1059;pontos_sensor[2][2] = 1;
                //5
                pontos_sensor[3][0] = 1869;pontos_sensor[3][1] = 2102;pontos_sensor[3][2] = 1;
                //6
                pontos_sensor[4][0] = 1283;pontos_sensor[4][1] = 2253;pontos_sensor[4][2] = 1;
                //7
                pontos_sensor[5][0] = 1033;pontos_sensor[5][1] = 1636;pontos_sensor[5][2] = 1;



                //3
                pontos_sensor_teste[0][0] = 2685;pontos_sensor_teste[0][1] = 1942;pontos_sensor_teste[0][2] = 1;
                //8
                pontos_sensor_teste[1][0] = 1050;pontos_sensor_teste[1][1] = 1274;pontos_sensor_teste[1][2] = 1;


                //p8
                //x = 1050 y = 1274
                //p3
                //x = 2685 y = 1942

                z[0][0] = -0.3;z[1][0] = 0.3;z[2][0] = 1;

                /*
                K
                |2.334597 -0.869206 -5051.016077 |
                |0.000000 2.129448 3910.840046 |
                |0.000000 0.000000 4093.547993 |
                R
                |-0.866360 0.499419 0.000138 |
                |0.499419 0.866360 -0.000097 |
                |-0.000168 -0.000015 -1.000000 |
                Z
                |-0.270160 |
                |0.215703 |
                |1.060472 |
                */


                break;
            case 3:
                //pontos referentes a P4
                //1
                pontos_sensor[0][0] = 2578;pontos_sensor[0][1] = 1811;pontos_sensor[0][2] = 1;
                //2
                pontos_sensor[1][0] = 2487;pontos_sensor[1][1] = 2317;pontos_sensor[1][2] = 1;
                //4
                pontos_sensor[2][0] = 1814;pontos_sensor[2][1] = 1447;pontos_sensor[2][2] = 1;
                //5
                pontos_sensor[3][0] = 1396;pontos_sensor[3][1] = 2330;pontos_sensor[3][2] = 1;
                //6
                pontos_sensor[4][0] = 937;pontos_sensor[4][1] = 1983;pontos_sensor[4][2] = 1;
                //7
                pontos_sensor[5][0] = 1043;pontos_sensor[5][1] = 1364;pontos_sensor[5][2] = 1;



                //3
                pontos_sensor_teste[0][0] = 2107;pontos_sensor_teste[0][1] = 2588;pontos_sensor_teste[0][2] = 1;
                //8
                pontos_sensor_teste[1][0] = 1237;pontos_sensor_teste[1][1] = 1093;pontos_sensor_teste[1][2] = 1;


                //p8
                //x = 1050 y = 1274
                //p3
                //x = 2685 y = 1942

                z[0][0] = -0.3;z[1][0] = -0.3;z[2][0] = 1;
                break;
            case 4:
                //pontos referentes a P5
                //1
                pontos_sensor[0][0] = 2377;pontos_sensor[0][1] = 1439;pontos_sensor[0][2] = 1;
                //2
                pontos_sensor[1][0] = 2546;pontos_sensor[1][1] = 1938;pontos_sensor[1][2] = 1;
                //4
                pontos_sensor[2][0] = 1523;pontos_sensor[2][1] = 1472;pontos_sensor[2][2] = 1;
                //5
                pontos_sensor[3][0] = 1579;pontos_sensor[3][1] = 2614;pontos_sensor[3][2] = 1;
                //6
                pontos_sensor[4][0] = 853;pontos_sensor[4][1] = 2641;pontos_sensor[4][2] = 1;
                //7
                pontos_sensor[5][0] = 603;pontos_sensor[5][1] = 1920;pontos_sensor[5][2] = 1;



                //3
                pontos_sensor_teste[0][0] = 2347;pontos_sensor_teste[0][1] = 2425;pontos_sensor_teste[0][2] = 1;
                //8
                pontos_sensor_teste[1][0] = 677;pontos_sensor_teste[1][1] = 1504;pontos_sensor_teste[1][2] = 1;


                //p8
                //x = 1050 y = 1274
                //p3
                //x = 2685 y = 1942

                z[0][0] = 0;z[1][0] = 0;z[2][0] = 0.8;
                break;
        }

        printf("pontos_sensor\n");
        matrix_print_int(pontos_sensor, 6, 3);
        printf("pontos_real\n");
        matrix_print(pontos_real, 6, 4);

        double ***KRZ = p6p_dlt(pontos_sensor, pontos_real);
        printf("K\n");
        matrix_print(KRZ[0], 3, 3);
        printf("R\n");
        matrix_print(KRZ[1], 3, 3);
        printf("Z\n");
        matrix_print(KRZ[2], 3, 1);

        double errorZ = 0;
        for(uint32_t i = 0; i < 3; i++){
            errorZ += pow(KRZ[2][i][0] - z[i][0], 2);
        }
        errorZ = sqrt(errorZ);
        printf("Erro = %f m\n", errorZ);

        printf("pontos_sensor_teste\n");
        matrix_print_int(pontos_sensor_teste,2 , 3);
        printf("pontos_real_teste\n");
        matrix_print(pontos_real_teste, 2, 4);

        //double **P = KRZ[3];

        double **B = matrix_mult(KRZ[0], KRZ[1], 3, 3, 3, 3);
        double **b = matrix_mult(B, KRZ[2], 3, 3, 3, 1);
        double **P = (double**) malloc(3 * sizeof(double*));
        for(uint32_t i = 0; i < 3; i++){
            P[i] = (double*) malloc(4 * sizeof(double));
            for(uint32_t j = 0; j < 4; j++){
                if(j < 3){
                    P[i][j] = B[i][j];
                }else{
                    P[i][j] = -b[i][0];
                }
            }
        }
        //matrix_free(B, 3);
        //matrix_free(b, 3);
        //matrix_free(KRZ[3], 3);

        printf("P\n");
        matrix_print(P, 3, 4);

        for(uint32_t i = 0; i < 2; i++){
            double *p_teste = (double*) malloc(3 * sizeof(double));

            double error = 0;
            for(uint32_t line = 0; line < 3; line++){
                p_teste[line] = 0;
                for(uint32_t column = 0; column < 4; column++){
                    p_teste[line] += P[line][column] * pontos_real_teste[i][column];
                }
            }
            for(uint32_t j = 0; j < 3; j++){
                error += pow((p_teste[j]/p_teste[2]) - pontos_sensor_teste[i][j], 2);
            }
            error = sqrt(error);

            printf("Ponto teste %d: [%f, %f, %f] - Erro = %f pixels\n", i, p_teste[0]/p_teste[2], p_teste[1]/p_teste[2], p_teste[2]/p_teste[2], error);


            free(p_teste);
        }

        matrix_free(P, 3);
        matrix_free(B, 3);
        matrix_free(b, 3);
        //matrix_free(pontos_real_teste, 2);
        //matrix_free(pontos_sensor_teste, 2);

        for(uint8_t line = 0; line < 3; line++){
            for(uint8_t column = 0; column < 3; column++){
                K_mean[line][column] += KRZ[0][line][column] / KRZ[0][2][2];
            }
        }

        c[n] = KRZ[0][0][0] / KRZ[0][2][2];
        s[n] = KRZ[0][0][1] / (KRZ[0][0][0]);
        m[n] = (KRZ[0][1][1] / KRZ[0][0][0]) - 1;
        xh[n] = KRZ[0][0][2] / KRZ[0][2][2];
        yh[n] = KRZ[0][1][2] / KRZ[0][2][2];


        matrix_free(KRZ[0], 3);
        matrix_free(KRZ[1], 3);
        matrix_free(KRZ[2], 3);
        matrix_free(KRZ[3], 3);
        free(KRZ);
        //matrix_free(pontos_real, 6);
        //matrix_free(pontos_sensor, 6);
    }
    /*//esses abaixo fazem sentido nenhum
    pontos_sensor[0][0] = 200;pontos_sensor[0][1] = 200;pontos_sensor[0][2] = 1;
    pontos_sensor[1][0] = 300;pontos_sensor[1][1] = 200;pontos_sensor[1][2] = 1;
    pontos_sensor[2][0] = 200;pontos_sensor[2][1] = 300;pontos_sensor[2][2] = 1;
    pontos_sensor[3][0] = 300;pontos_sensor[3][1] = 300;pontos_sensor[3][2] = 1;
    pontos_sensor[4][0] = 250;pontos_sensor[4][1] = 250;pontos_sensor[4][2] = 1;
    pontos_sensor[5][0] = 150;pontos_sensor[5][1] = 250;pontos_sensor[5][2] = 1;

    pontos_real[0][0] = 0;pontos_real[0][1] = 0;pontos_real[0][2] = 0;pontos_real[0][3] = 1;
    pontos_real[1][0] = 1;pontos_real[1][1] = 0;pontos_real[1][2] = 0;pontos_real[1][3] = 1;
    pontos_real[2][0] = 0;pontos_real[2][1] = 1;pontos_real[2][2] = 0;pontos_real[2][3] = 1;
    pontos_real[3][0] = 1;pontos_real[3][1] = 1;pontos_real[3][2] = 0;pontos_real[3][3] = 1;
    pontos_real[4][0] = 0.5;pontos_real[4][1] = 0.5;pontos_real[4][2] = 1;pontos_real[4][3] = 1;
    pontos_real[5][0] = -0.5;pontos_real[5][1] = 0.5;pontos_real[5][2] = 1;pontos_real[5][3] = 1;
    */

    for(uint8_t line = 0; line < 3; line++){
        for(uint8_t column = 0; column < 3; column++){
            K_mean[line][column] = K_mean[line][column] / 5;
        }
    }
    printf("\n\nK_mean\n");
    matrix_print(K_mean, 3, 3);

    printf("c = %f\n", K_mean[0][0]);
    printf("s = %f\n", K_mean[0][1] / K_mean[0][0]);
    printf("m = %f\n", (K_mean[1][1] / K_mean[0][0]) - 1);
    printf("xh = %f\n", K_mean[0][2]);
    printf("yh = %f\n", K_mean[1][2]);

    //matrix_free(K_mean, 3);


    double c_mean = 0, s_mean = 0, m_mean = 0, xh_mean = 0, yh_mean = 0;
    double c_error = 0, s_error = 0, m_error = 0, xh_error = 0, yh_error = 0;
    for(uint8_t i = 0; i < 5; i++){
            printf("si = %f\tmi = %f\n", s[i], m[i]);
        c_mean += c[i];
        s_mean += s[i];
        m_mean += m[i];
        xh_mean += xh[i];
        yh_mean += yh[i];
    }
    c_mean /= 5;
    s_mean /= 5;
    m_mean /= 5;
    xh_mean /= 5;
    yh_mean /= 5;

    for(uint8_t i = 0; i < 5; i++){
        c_error += pow(c_mean - c[i], 2);
        s_error += pow(s_mean - s[i], 2);
        m_error += pow(m_mean - m[i], 2);
        xh_error += pow(xh_mean - xh[i], 2);
        yh_error += pow(yh_mean - yh[i], 2);
    }
    c_error = sqrt(c_error) / 5;
    s_error = sqrt(s_error) / 5;
    m_error = sqrt(m_error) / 5;
    xh_error = sqrt(xh_error) / 5;
    yh_error = sqrt(yh_error) / 5;

    printf("c = %f +- %f\n", c_mean, c_error);
    printf("s = %f +- %f\n", s_mean, s_error);
    printf("m = %f +- %f\n", m_mean, m_error);
    printf("xh = %f +- %f\n", xh_mean, xh_error);
    printf("yh = %f +- %f\n", yh_mean, yh_error);

    //1
    pontos_sensor[0][0] = 2578;pontos_sensor[0][1] = 1811;pontos_sensor[0][2] = 1;
    //2
    pontos_sensor[1][0] = 2487;pontos_sensor[1][1] = 2317;pontos_sensor[1][2] = 1;
    //4
    pontos_sensor[2][0] = 1814;pontos_sensor[2][1] = 1447;pontos_sensor[2][2] = 1;
    //5
    pontos_sensor[3][0] = 1396;pontos_sensor[3][1] = 2330;pontos_sensor[3][2] = 1;

    /*K
|2760.912863 48.512644 2171.975439 |
|0.000000 2817.339205 1340.746374 |
|0.000000 0.000000 1.000000 |
R
|-0.809736 -0.427203 -0.402275 |
|-0.474026 0.880299 0.019315 |
|0.345871 0.206329 -0.915315 |
Z
|-0.133101 |
|-0.259731 |
|0.864544 |
*/
    double ***RZ = p4p(K_mean, pontos_real, pontos_sensor);
    printf("p4p RZ\n");
    printf("R\n");
    matrix_print(RZ[0], 3, 3);
    printf("Z\n");
    matrix_print(RZ[1], 3, 1);
    matrix_free(RZ[0], 3);
    matrix_free(RZ[1], 3);
    free(RZ);

    matrix_free(K_mean, 3);
    matrix_free(pontos_real_teste, 2);
    matrix_free(pontos_sensor_teste, 2);
    matrix_free(pontos_real, 6);
    matrix_free(pontos_sensor, 6);

    free(c);
    free(s);
    free(m);
    free(xh);
    free(yh);

    p4p_fischler1981_test();



    return 0;
}

double **matrix_create_random(uint32_t height, uint32_t width, double min, double max){
    if(width == 0 || height == 0){
        return NULL;
    }
    double **matrix;
    double range;
    uint32_t random;

    srand(time(NULL));

    matrix = (double**) malloc(height * sizeof(double*));

    range = max - min;
    if(range < 0){
        range *= -1;
    }

    for(uint32_t line = 0; line < height; line++){
        matrix[line] = (double*) malloc(width * sizeof(double));

        for(uint32_t column = 0; column < width; column++){
            random = rand()% 0xffff;
            matrix[line][column] = ((double)((double)random / (double)0xffff)) * range + min;
        }
    }
    return matrix;
}

double **matrix_create_random_int(uint32_t height, uint32_t width, uint8_t symmetric, int32_t min, int32_t max){
    if(width == 0 || height == 0){
        return NULL;
    }
    double **matrix;
    int32_t range;
    uint32_t random;
    uint32_t column_start = 0;
    srand(time(NULL));

    matrix = (double**) malloc(height * sizeof(double*));

    range = max - min;
    if(range < 0){
        range *= -1;
    }

    for(uint32_t line = 0; line < height; line++){
        matrix[line] = (double*) malloc(width * sizeof(double));
    }

    for(uint32_t line = 0; line < height; line++){
        for(uint32_t column = column_start; column < width; column++){
            random = rand()% range;
            matrix[line][column] = (double) random + min;
            if(line != column && symmetric == 1){
                matrix[column][line] = matrix[line][column];
            }
        }
        if(symmetric == 1){
            column_start++;
        }
    }
    return matrix;
}

double **matrix_mult(double **A, double **B, uint32_t heightA, uint32_t widthA, uint32_t heightB, uint32_t widthB){
    double **resultMatrix = NULL;

    if(A != NULL && B != NULL && widthA == heightB && widthA > 0 && heightA > 0 && widthB > 0 && heightB > 0){
        resultMatrix = (double**) malloc(heightA * sizeof(double*));
        for(uint32_t line = 0; line < heightA; line++){
            resultMatrix[line] = (double*) malloc(widthB * sizeof(double));
            for(uint32_t column = 0; column < widthB; column++){
                resultMatrix[line][column] = 0;
                for(uint32_t it = 0; it < widthA; it++){
                    resultMatrix[line][column] = resultMatrix[line][column] + A[line][it] * B[it][column];
                }
            }
        }
    }

    return resultMatrix;
}

double **matrix_transpose(double **A, uint32_t heightA, uint32_t widthA){
    double **resultMatrix = NULL;

    if(A != NULL && widthA > 0 && heightA > 0){
        resultMatrix = (double**) malloc(widthA * sizeof(double*));
        for(uint32_t line = 0; line < widthA; line++){
            resultMatrix[line] = (double*) malloc(heightA * sizeof(double*));
            for(uint32_t column = 0; column < heightA; column++){
                resultMatrix[line][column] = A[column][line];
            }
        }
    }

    return resultMatrix;
}

double **matrix_inverse(double **A, uint32_t heightA, uint32_t widthA){
    if(A == NULL || heightA == 0 || widthA == 0 || heightA != widthA){
        return NULL;
    }
    double **inverseMatrix;
    double **ACopy;
    inverseMatrix = (double**) malloc(heightA * sizeof(double*));
    ACopy = (double**) malloc(heightA * sizeof(double*));
    for(uint32_t line = 0; line < heightA; line++){
        inverseMatrix[line] = (double*) malloc(widthA * sizeof(double));
        ACopy[line] = (double*) malloc(widthA * sizeof(double));
        for(uint32_t column = 0; column < widthA; column++){
            ACopy[line][column] = A[line][column];
            inverseMatrix[line][column] = line == column;
        }
    }

    //primeiro: transformar a matriz em triangular superior
    for(uint32_t index = 0; index < heightA; index++){

        //checa se o elemento é não nulo
        if(ACopy[index][index] == 0){
            //se é nulo, procura alguma linha abaixo que não seja nula
            uint8_t trocado = 0;
            for(uint32_t line = index + 1; line < heightA; line++){
                if(ACopy[line][index] != 0){
                    //trocar a linha
                    double *aux = ACopy[line];
                    ACopy[line] = ACopy[index];
                    ACopy[index] = aux;

                    aux = inverseMatrix[line];
                    inverseMatrix[line] = inverseMatrix[index];
                    inverseMatrix[index] = aux;
                    trocado = 1;
                }
            }
            if(trocado == 0){
                //não foi tracado e não há inversa
                matrix_free(ACopy, heightA);
                matrix_free(inverseMatrix, heightA);
                return NULL;
            }
        }

        //checa se é unitário
        if(ACopy[index][index] != (double)1){
            //transforma em um
            double element = ACopy[index][index];
            for(uint32_t column = 0; column < widthA; column++){
                ACopy[index][column] = ACopy[index][column] / element;
                inverseMatrix[index][column] = inverseMatrix[index][column] / element;
            }
        }
        //zera os elementos das linhas abaixo
        for(uint32_t line = index + 1; line < heightA; line++){
            if(ACopy[line][index] != 0){
                double aux = ACopy[line][index];
                for(uint32_t column = 0; column < widthA; column++){
                    ACopy[line][column] = ACopy[line][column] - aux * ACopy[index][column];
                    inverseMatrix[line][column] = inverseMatrix[line][column] - aux * inverseMatrix[index][column];
                }
            }
        }
    }

    //printf("ACopy\n");
    //matrix_print(ACopy, heightA, widthA);

    //agora já deve ter uma matriz triangular superior
    uint32_t index = heightA;
    do{
        index--;
        for(uint32_t line = 0; line < index; line++){
            if(ACopy[line][index] != 0){
                double aux = ACopy[line][index];
                ACopy[line][index] = ACopy[line][index] - aux * ACopy[index][index];
                for(uint32_t column = 0; column < widthA; column++){
                    //ACopy[line][column] = ACopy[line][column] - aux * ACopy[index][column];
                    inverseMatrix[line][column] = inverseMatrix[line][column] - aux * inverseMatrix[index][column];
                }
            }
        }

    }while(index != 0);

    //printf("ACopy\n");
    //matrix_print(ACopy, heightA, widthA);

    matrix_free(ACopy, heightA);

    return inverseMatrix;
}

double module_of_vector(double *v, uint32_t size){
    if(v == NULL || size == 0){
        return -1;
    }
    double module = 0;

    for(uint32_t i = 0; i < size; i++){
        module += pow(v[i], 2);
    }
    module = sqrt(module);

    return module;
}

double module_of_vector_matrix(double **A, uint32_t heightA, uint32_t column){
    if(A == NULL || heightA == 0 || column == 0){
        return -1;
    }
    double module = 0;

    for(uint32_t line = 0; line < heightA; line++){
        module += pow(A[line][column], 2);
    }
    module = sqrt(module);

    return module;
}

double internal_product(double **A,uint32_t columnA, double **B, uint32_t columnB, uint32_t height){
    //assumindo que tudo está certo
    double result = 0;
    for(uint32_t line = 0; line < height; line++){
        result += A[line][columnA] * B[line][columnB];
    }
    return result;
}

//0 - q
//1 - r
double ***qr_decomposition(double **A, uint32_t heightA, uint32_t widthA){
    //printf("qr_decomposition\n");
    if(A == NULL || heightA == 0 || widthA == 0 || heightA != widthA){
        return NULL;
    }
    double ***qr;
    double *internal_product_memmory;
    double module;


    qr = (double***) malloc(2 * sizeof(double**));
    qr[0] = (double**) malloc(heightA * sizeof(double*));
    qr[1] = (double**) malloc(heightA * sizeof(double*));
    for(uint32_t line = 0; line < heightA; line++){
        qr[0][line] = (double*) malloc(widthA * sizeof(double));
        qr[1][line] = (double*) malloc(widthA * sizeof(double));
    }

    internal_product_memmory = (double*) malloc((heightA - 1) * sizeof(double));

    //calcular q primeiro
    for(uint32_t column = 0; column < widthA; column++){
        //calculo do produto interno
        for(uint32_t c = 0; c < column; c++){
            internal_product_memmory[c] = internal_product(A, column, qr[0], c, heightA);
        }

        module = 0;

        for(uint32_t line = 0; line < heightA; line++){
            qr[0][line][column] = A[line][column];
            for(uint32_t c = 0; c < column; c++){
                qr[0][line][column] = qr[0][line][column] - internal_product_memmory[c] * qr[0][line][c];
            }
            module += pow(qr[0][line][column], 2);
        }
        module = sqrt(module);
        if(module > eps){
            for(uint32_t line = 0; line < heightA; line++){
                qr[0][line][column] = qr[0][line][column] / module;
            }
        }

        //diagonal da matriz R
        qr[1][column][column] = module;

    }

    //preenche o restante da matriz R
    for(uint32_t line = 0; line < heightA; line++){
        for(uint32_t column = 0; column < widthA; column++){
            //caso column == line já foi preenchido
            if(column != line){
                if(line < column){
                    qr[1][line][column] = internal_product(A, column, qr[0], line, heightA);
                }else{
                    qr[1][line][column] = 0;
                }
            }
        }
    }
    //printf("Q\n");
    //matrix_print(qr[0], heightA, widthA);

    free(internal_product_memmory);
    return qr;
}

//retorna os autovalores da matriz quadrada A
//por algum motivo, funciona o autovetor apenas para o primeiro autovalor com Q acumulado
double *eigenvalues(double **A, uint32_t heightA, uint32_t widthA){
    if(A == NULL || heightA == 0 || widthA == 0 || heightA != widthA){
        return NULL;
    }
    double *lambda;
    double **B;
    double error;
    double ***qr;
    //double **V;
    //double **U;
    //double **QT;
    /*V = (double**) malloc(heightA * sizeof(double*));
    for(uint32_t line = 0; line < heightA; line++){
        V[line] = (double*) malloc(widthA * sizeof(double));
        for(uint32_t column = 0; column < widthA; column++){
            V[line][column] = line == column;
        }
    }
    */
    //printf("V\n");
    //matrix_print(V, heightA, widthA);
    lambda = (double*) malloc(heightA * sizeof(double));

    //copia a matriz A para B
    /*
    B = (double**) malloc(heightA * sizeof(double*));
    for(uint32_t line = 0; line < heightA; line++){
        B[line] = (double*) malloc(widthA * sizeof(double));
        for(uint32_t column = 0; column < widthA; column++){
            B[line][column] = A[line][column];
        }
    }
    */
    qr = qr_decomposition(A, heightA, widthA);
    //QT = matrix_transpose(A, heightA, widthA);
    //U = matrix_mult(V,qr[0], heightA, widthA, heightA, widthA);
    //U = matrix_mult(V,QT, heightA, widthA, heightA, widthA);
    //matrix_free(QT, heightA);
    //matrix_free(V, heightA);
    /*for(uint32_t line = 0; line < heightA; line++){
        for(uint32_t column = 0; column < widthA; column++){
            V[line][column] = U[line][column];
        }
    }
    */
    //matrix_free(U, heightA);
    //printf("V\n");
    //matrix_print(V, heightA, widthA);
    //V = U;
    //U = NULL;
    B = matrix_mult(qr[1],qr[0],heightA, widthA, heightA, widthA);
    for(uint32_t index = 0; index < heightA; index++){
        lambda[index] = B[index][index];
    }
    matrix_free(qr[0], heightA);
    matrix_free(qr[1], heightA);
    free(qr);
    //matrix_free(B, heightA);
    //uint32_t n = 0;
    do{
        qr = qr_decomposition(B, heightA, widthA);
        //QT = matrix_transpose(A, heightA, widthA);
        //U = matrix_mult(V,qr[0], heightA, widthA, heightA, widthA);
        //U = matrix_mult(V,QT, heightA, widthA, heightA, widthA);
        //matrix_free(QT, heightA);
        //for(uint32_t line = 0; line < heightA; line++){
        //    for(uint32_t column = 0; column < widthA; column++){
        //        V[line][column] = U[line][column];
        //    }
        //}
        //printf("V\n");
        //matrix_print(V, heightA, widthA);
        //matrix_free(U, heightA);
        //matrix_free(V, heightA);
        //V = U;
        //U = NULL;
        matrix_free(B, heightA);
        B = matrix_mult(qr[1],qr[0],heightA, widthA, heightA, widthA);
        error = 0;
        for(uint32_t index = 0; index < heightA; index++){
            double aux = B[index][index] - lambda[index];
            if(aux < 0){
                aux = -aux;
            }
            if(aux > error){
                error = aux;
            }

            lambda[index] = B[index][index];
        }
        /*
        if(error <= eps * eps){
            printf("FROM QR_ALGORITHM\nQ\n");
            matrix_print(qr[0],heightA, widthA);
            printf("R\n");
            matrix_print(qr[1],heightA, widthA);
            printf("B\n");
            matrix_print(B,heightA, widthA);
            //printf("V\n");
            //matrix_print(V,heightA, widthA);
        }
        */
        matrix_free(qr[0], heightA);
        matrix_free(qr[1], heightA);
        free(qr);

        //printf("n = %d\terror = %e\n", ++n, error);
        //printf("B\n");
        //matrix_print(B, heightA, widthA);
    }while(error > eps * eps);

    matrix_free(B, heightA);
    //matrix_free(V, heightA);

    //quando a matriz é apenas diagonal, pode acontecer dos eigenvalues estarem desordenados
    //isso é só para quebrar o galho
    for(uint32_t i = 0; i < heightA; i++){
        for(uint32_t j = i + 1; j < heightA; j++){
            if(fabs(lambda[j]) > fabs(lambda[i])){
                double aux = lambda[j];
                lambda[j] = lambda[i];
                lambda[i] = aux;
            }
        }
    }


    return lambda;
}
//cuidado com variavel que pode ter valor zero
double **eigenvector(double **A, uint32_t heightA, uint32_t widthA, double eigenvalue){
    if(A == NULL || heightA == 0 || widthA == 0 || heightA != widthA){
        return NULL;
    }
    //static const double eps  = 0x1p-20;
    double **v;
    double **matrix;
    uint8_t *independent_variables;
    uint32_t number_of_ind_var = 0;
    independent_variables = (uint8_t*) malloc(heightA * sizeof(uint8_t));
    //v = (double*) malloc(heightA * sizeof(double));

    matrix = (double**) malloc(heightA * sizeof(double*));
    //matrix = A - lambda * I
    for(uint32_t line = 0; line < heightA; line++){
        independent_variables[line] = 0;

        matrix[line] = (double*) malloc(widthA * sizeof(double));
        for(uint32_t column = 0; column < widthA; column++){
            if(line == column){
                matrix[line][column] = A[line][column] - eigenvalue;
            }else{
                matrix[line][column] = A[line][column];
            }
        }
    }
    //printf("A\n");
    //matrix_print(A, heightA, widthA);
    //printf("matrix\n");
    //matrix_print(matrix, heightA, widthA);

    //primeiro: transformar em uma matriz 'triangular' superior com diagonal unitária
    //mas com última linha zerada
    for(uint32_t index = 0; index < heightA - 1; index++){

        //checa se o elemento é não nulo
        //if(matrix[index][index] == 0){
        if(matrix[index][index] < eps && matrix[index][index] > -eps){
            //se é nulo, procura alguma linha abaixo que não seja nula
            uint8_t trocado = 0;
            for(uint32_t line = index + 1; line < heightA; line++){
                //if(matrix[line][index] != 0){
                if(matrix[index][index] > eps || matrix[index][index] < -eps){
                    //trocar a linha
                    double *aux = matrix[line];
                    matrix[line] = matrix[index];
                    matrix[index] = aux;

                    trocado = 1;
                }
            }
            if(trocado == 0){
                independent_variables[index] = 1;
                number_of_ind_var++;
                continue;
            }
        }

        //checa se é unitário
        if(matrix[index][index] != (double)1){
            //transforma em um
            double aux = matrix[index][index];
            for(uint32_t column = index; column < widthA; column++){
                matrix[index][column] = matrix[index][column] / aux;
            }
        }
        //zera os elementos das linhas abaixo
        for(uint32_t line = index + 1; line < heightA; line++){
            if(matrix[line][index] > eps || matrix[line][index] < -eps){
                double aux = matrix[line][index];
                for(uint32_t column = index; column < widthA; column++){
                    matrix[line][column] = matrix[line][column] - aux * matrix[index][column];
                }
            }
        }
        //printf("matrix\n");
        //matrix_print(matrix, heightA, widthA);
        //getchar();
    }
    if(matrix[heightA - 1][heightA - 1] < eps && matrix[heightA - 1][heightA - 1] > -eps){
        independent_variables[heightA - 1] = 1;
        number_of_ind_var++;
    }
/*
    printf("ind_vars = [");
    uint32_t ccccc = 0;
    for(uint32_t n = 0; n < heightA; n++){
        if(independent_variables[n] == 1){
            printf("%d", n);
            ccccc++;
            if(ccccc == number_of_ind_var){
                break;
            }
            printf(", ");
        }


    }
    printf("]\n");
*/
    if(number_of_ind_var == 0){
        /*
        v = (double**) malloc(2 * sizeof(double*));
        v[1] = (double*) NULL;
        v[0] = (double*) malloc(heightA * sizeof(double));
        for(uint32_t n = 0; n < heightA; n++){
            v[0][n] = 0;
        }
        free(independent_variables);
        matrix_free(matrix, heightA);
        return v;
        */
        number_of_ind_var = 1;
        independent_variables[heightA - 1] = 1;
    }

    //printf("matrix\n");
    //matrix_print(matrix, heightA, widthA);
    //escolhe a variável independente
    v = (double**) malloc((number_of_ind_var + 1) * sizeof(double*));
    v[number_of_ind_var] = (double*) NULL;
    uint32_t ind_var = heightA;
    //uint32_t n_eigenvec = 0;

    for(uint32_t n_eigenvec = 0; n_eigenvec < number_of_ind_var; n_eigenvec++){
        //procurando proxima variavel independente
        while(1){
            ind_var--;
            if(independent_variables[ind_var] == 1){
                break;
            }
        }
        v[n_eigenvec] = (double*) malloc(heightA * sizeof(double));
        for(uint32_t counter = 0; counter < heightA; counter++){
            v[n_eigenvec][counter] = 0;
        }

        if(ind_var != heightA - 1){
            for(uint32_t line = 0; line < heightA; line++){
                for(uint32_t column = 0; column < widthA; column++){
                    if(line == column){
                        matrix[line][column] = A[line][column] - eigenvalue;
                    }else{
                        matrix[line][column] = A[line][column];
                    }
                }
            }
            //printf("ind_var = %d\n A - lambda\n", ind_var);
            //matrix_print(matrix, heightA, widthA);

            for(uint32_t index = 0; index < heightA; index++){
                if(index == ind_var){
                    continue;
                }

                if(matrix[index][index] < eps && matrix[index][index] > -eps){//==0
                    uint32_t trocado = 0;
                    for(uint32_t line = index + 1; line < heightA; line++){
                        if(matrix[line][index] > eps || matrix[line][index] < -eps){
                            double *aux = matrix[index];
                            matrix[index] = matrix[line];
                            matrix[line] = aux;
                            trocado = 1;
                            break;
                        }
                    }
                    if(trocado == 0){
                        continue;
                    }
                }

                if(matrix[index][index] != (double)1){
                    double aux = matrix[index][index];
                    for(uint32_t column = index; column < widthA; column++){
                        matrix[index][column] = matrix[index][column] / aux;
                    }
                }

                for(uint32_t line = index + 1; line < heightA; line++){
                    if(matrix[line][index] > eps || matrix[line][index] < -eps){
                        double aux = matrix[line][index];
                        for(uint32_t column = 0; column < widthA; column++){
                            matrix[line][column] = matrix[line][column] - aux * matrix[index][column];
                        }
                    }
                }
                //zera da linha do ind_var
                if(matrix[ind_var][index] > eps || matrix[ind_var][index] < -eps){
                    double aux = matrix[ind_var][index];
                    for(uint32_t column = 0; column < widthA; column++){
                        matrix[ind_var][column] = matrix[ind_var][column] - aux * matrix[index][column];
                    }
                }


            }
            //printf("ind_var = %d\n", ind_var);
            //matrix_print(matrix, heightA, widthA);

        }
        v[n_eigenvec][ind_var] = 1;
        uint32_t index = ind_var;
        do{

            if(index == 0){
                index = heightA - 1;
            }else{
                index--;
            }
            if(index == ind_var){
                break;
            }
            //v[n_eigenvec][index] = 0;
            if(matrix[index][index] > eps || matrix[index][index] < -eps){
                for(uint32_t column = 0; column < widthA; column++){
                    if(column != index){
                        v[n_eigenvec][index] = v[n_eigenvec][index] - v[n_eigenvec][column] * matrix[index][column];
                    }
                }
            }
        }while(1);



    }

/*
    uint32_t index = heightA;
    do{
        index--;
        if(matrix[index][index] > eps || matrix[index][index] < -eps){
            printf("%d,%f\n", index, matrix[index][index]);
            v[index] = 0;
        }else{
            //independent_variable = index;
            v[index] = 1;
            break;
        }
    }while(index != 0);

    while(index != 0){
        index--;
        v[index] = 0;
        for(uint32_t column = index + 1; column < widthA; column++){
            v[index] = v[index] - v[column] * matrix[index][column];
        }
    }*/
    free(independent_variables);
    matrix_free(matrix, heightA);
    return v;
}
/*
//cuidado com variavel que pode ter valor zero
double **eigenvector(double **A, uint32_t heightA, uint32_t widthA, double eigenvalue){
    if(A == NULL || heightA == 0 || widthA == 0 || heightA != widthA){
        return NULL;
    }
    //static const double eps  = 0x1p-20;
    double *v;
    double **matrix;
    uint32_t independent_variable;
    v = (double*) malloc(heightA * sizeof(double));

    matrix = (double**) malloc(heightA * sizeof(double*));
    //matrix = A - lambda * I
    for(uint32_t line = 0; line < heightA; line++){
        matrix[line] = (double*) malloc(widthA * sizeof(double));
        for(uint32_t column = 0; column < widthA; column++){
            if(line == column){
                matrix[line][column] = A[line][column] - eigenvalue;
            }else{
                matrix[line][column] = A[line][column];
            }
        }
    }
    //printf("A\n");
    //matrix_print(A, heightA, widthA);
    //printf("matrix\n");
    //matrix_print(matrix, heightA, widthA);

    //primeiro: transformar em uma matriz 'triangular' superior com diagonal unitária
    //mas com última linha zerada
    for(uint32_t index = 0; index < heightA - 1; index++){

        //checa se o elemento é não nulo
        if(matrix[index][index] == 0){
            //se é nulo, procura alguma linha abaixo que não seja nula
            uint8_t trocado = 0;
            for(uint32_t line = index + 1; line < heightA; line++){
                if(matrix[line][index] != 0){
                    //trocar a linha
                    double *aux = matrix[line];
                    matrix[line] = matrix[index];
                    matrix[index] = aux;

                    trocado = 1;
                }
            }
            if(trocado == 0){
                //não foi tracado e não há subespaço??????não sei
                //talvez seja uma solução dizer que é nulo o valor da variavel
                matrix_free(matrix, heightA);
                return NULL;
            }
        }

        //checa se é unitário
        if(matrix[index][index] != (double)1){
            //transforma em um
            double aux = matrix[index][index];
            for(uint32_t column = index; column < widthA; column++){
                matrix[index][column] = matrix[index][column] / aux;
            }
        }
        //zera os elementos das linhas abaixo
        for(uint32_t line = index + 1; line < heightA; line++){
            if(matrix[line][index] > eps || matrix[line][index] < -eps){
                double aux = matrix[line][index];
                for(uint32_t column = index; column < widthA; column++){
                    matrix[line][column] = matrix[line][column] - aux * matrix[index][column];
                }
            }
        }
        //printf("matrix\n");
        //matrix_print(matrix, heightA, widthA);
        //getchar();
    }
    //printf("matrix\n");
    //matrix_print(matrix, heightA, widthA);
    //escolhe a variável independente
    uint32_t index = heightA;
    do{
        index--;
        if(matrix[index][index] > eps || matrix[index][index] < -eps){
            printf("%d,%f\n", index, matrix[index][index]);
            v[index] = 0;
        }else{
            //independent_variable = index;
            v[index] = 1;
            break;
        }
    }while(index != 0);

    while(index != 0){
        index--;
        v[index] = 0;
        for(uint32_t column = index + 1; column < widthA; column++){
            v[index] = v[index] - v[column] * matrix[index][column];
        }
    }
    return v;
}
*/

//A = US(V^T)
//0 - U
//1 - Sigma
//2 - V
double ***svd_decomposition(double **A, uint32_t heightA, uint32_t widthA){
    //printf("svd_decomposition\n");
    if(A == NULL || heightA == 0 || widthA == 0){
        return NULL;
    }
    double ***svd;
    double *eigenval;
    double **AT;
    double **AAT;
    double **ATA;
    uint32_t n_eigenval;

    double **m;
    uint32_t index_svd;


    svd = (double***) malloc(3 * sizeof(double**));

    AT = matrix_transpose(A, heightA, widthA);

    AAT = matrix_mult(A, AT, heightA, widthA, widthA, heightA);

    ATA = matrix_mult(AT, A, widthA, heightA, heightA, widthA);


    if(heightA > widthA){
        eigenval = eigenvalues(AAT, heightA, heightA);
        n_eigenval = heightA;
        m = AAT;
        index_svd = 0;
    }else{
        eigenval = eigenvalues(ATA, widthA, widthA);
        n_eigenval = widthA;
        m = ATA;
        index_svd = 2;
    }

/*
    printf("Eigenvalues:[");
    for(uint32_t index = 0; index < n_eigenval; index++){
        printf("%f", eigenval[index]);
        if(index != heightA - 1){
            printf(", ");
        }
    }
    printf("]\n");
*/

    svd[0] = (double**) malloc(heightA * sizeof(double*));
    svd[1] = (double**) malloc(heightA * sizeof(double*));
    svd[2] = (double**) malloc(widthA * sizeof(double*));

    for(uint32_t line = 0; line < n_eigenval; line++){
        if(line < heightA){
            svd[0][line] = (double*) malloc(heightA * sizeof(double));
            svd[1][line] = (double*) malloc(widthA * sizeof(double));


            for(uint32_t column = 0; column < widthA; column++){
                if(line == column){
                    svd[1][line][column] = sqrt(eigenval[line]);
                }else{
                    svd[1][line][column] = 0;
                }
            }
        }
        if(line < widthA){
            svd[2][line] = (double*) malloc(widthA * sizeof(double));
        }
    }

    uint32_t index = n_eigenval;
    double **eigenvec;
    double module;
    uint32_t counter = 1;

    do{
        index = index - counter;
        //printf("index = %d\n", index);
        eigenvec = eigenvector(m, n_eigenval, n_eigenval, eigenval[index]);
        /*
        printf("\tEigenvalue = %f\n", eigenval[index]);
        for(uint32_t i = 0; eigenvec[i] != NULL; i++){
            printf("\t\tEigenvector = [");
            for(uint32_t j = 0; j < n_eigenval; j++){
                printf("%f", eigenvec[i][j]);
                if(j != n_eigenval - 1){
                    printf(", ");
                }
            }
            printf("]\n");
        }
*/
        //printf("af_eig");
        counter = 0;
        do{
            //printf("Counter = %d\n", counter);
            module = 0;
            for(uint32_t eigenvec_index = 0; eigenvec_index < n_eigenval; eigenvec_index++){
                module += pow(eigenvec[counter][eigenvec_index], 2);
                svd[index_svd][eigenvec_index][index - counter] = eigenvec[counter][eigenvec_index];
            }
            module = sqrt(module);
            if(module != 0){
                for(uint32_t eigenvec_index = 0; eigenvec_index < n_eigenval; eigenvec_index++){
                    svd[index_svd][eigenvec_index][index - counter] = svd[index_svd][eigenvec_index][index - counter] / module;
                }
            }
            free(eigenvec[counter]);
            if(index - counter == 0){
                index = 0;
                break;
            }
            counter++;
        }while(eigenvec[counter] != NULL);
        free(eigenvec);

    }while(index != 0);

    uint32_t height2, width2;

    if(index_svd == 0){
        index_svd = 2;
        m = AT;
        index = widthA;
        height2 = widthA;
        width2 = heightA;
    }else{
        index_svd = 0;
        m = A;
        index = heightA;
        height2 = heightA;
        width2 = widthA;
    }

    do{
        index--;

        for(uint32_t line = 0; line < height2; line++){
            //printf("line = %d\n", line);
            svd[index_svd][line][index] = 0;
            for(uint32_t column = 0; column < width2; column++){
                //printf("column = %d\n", column);
                svd[index_svd][line][index] += m[line][column] * svd[2 - index_svd][column][index];
            }
            if(svd[1][index][index] != 0){
                svd[index_svd][line][index] = svd[index_svd][line][index] / svd[1][index][index];
            }else{
                svd[index_svd][line][index] = 0;
            }
            //printf("[%d][%d] = %f\n", line, index, svd[index_svd][line][index]);

        }

    }while(index != 0);

    free(eigenval);
    matrix_free(AT, widthA);
    matrix_free(ATA, widthA);
    matrix_free(AAT, heightA);

    //printf("end_svd_decomposition\n");
    return svd;
}

void matrix_print(double **A, uint32_t heightA, uint32_t widthA){
    if(A == NULL || heightA == 0 || widthA == 0){
        printf("NULL\n");
        return;
    }

    for(uint32_t line = 0; line < heightA; line++){
        printf("|");
        for(uint32_t column = 0; column < widthA; column++){
            printf("%f ", A[line][column]);
        }
        printf("|\n");
    }

}
void matrix_print_int(uint32_t **A, uint32_t heightA, uint32_t widthA){
    if(A == NULL || heightA == 0 || widthA == 0){
        printf("NULL\n");
        return;
    }

    for(uint32_t line = 0; line < heightA; line++){
        printf("|");
        for(uint32_t column = 0; column < widthA; column++){
            printf("%d ", A[line][column]);
        }
        printf("|\n");
    }
}


void matrix_free(double **A, uint32_t heightA){
    if(A == NULL || heightA == 0){
        return;
    }

    for(uint32_t line = 0; line < heightA; line++){
        free(A[line]);
    }
    free(A);
    A = NULL;
}

uint8_t matrix_equal(double **A, double **B, uint32_t heightA, uint32_t widthA, uint32_t heightB, uint32_t widthB){
    if(A == NULL || B == NULL || heightA == 0 || heightA != heightB || widthA == 0 || widthA != widthB){
        return 0;
    }
    for(uint32_t line = 0; line < heightA; line++){
        for(uint32_t column = 0; column < widthA; column++){
            if(A[line][column] < B[line][column] - eps ||
               A[line][column] > B[line][column] + eps){
                return 0;
            }
        }
    }
    return 1;
}

//linha i da matriz deve ser o vetor de coordenadas
//pixel_coordinates 6x3
//  [xi * wi, yi * wi, wi]
//real_world_coordinates 6x4
// [Xi * Wi, Yi * Wi, Zi * Wi, Wi]
double ***p6p_dlt(uint32_t **pixel_coordinates, double **real_world_coordinates){
    printf("p6p_dlt\n");
    if(pixel_coordinates == NULL || real_world_coordinates == NULL){
        return NULL;
    }
    double ***KRZ;
    //montagem da matriz A
    double **A;
    A = (double**) malloc(12 * sizeof(double*));

    for(uint32_t i = 0; i < 6; i++){
        uint32_t line1 = i << 1;
        uint32_t line2 = line1 + 1;
        uint32_t index = 0;
        A[line1] = (double*) malloc(12 * sizeof(double));
        A[line2] = (double*) malloc(12 * sizeof(double));

        do{
            A[line1][index] = 0;
            A[line2][index] = real_world_coordinates[i][index] / real_world_coordinates[i][3];
            index++;
        }while(index < 4);
        do{
            A[line1][index] = -real_world_coordinates[i][index - 4] / real_world_coordinates[i][3];
            A[line2][index] = 0;
            index++;
        }while(index < 8);
        do{
            A[line1][index] = ((double)pixel_coordinates[i][1] / (double)pixel_coordinates[i][2]) * (real_world_coordinates[i][index - 8] / real_world_coordinates[i][3]);
            A[line2][index] = -((double)pixel_coordinates[i][0] / (double)pixel_coordinates[i][2]) * (real_world_coordinates[i][index - 8] / real_world_coordinates[i][3]);
            index++;
        }while(index < 12);

    }
    matrix_print(A, 12, 12);
    /*
    printf("printing matrix for wolframalpha = ");
    printf("{");
    for(uint32_t i = 0; i < 12; i++){
        printf("{");
        for(uint32_t j = 0; j < 12; j++){
            printf("%f", A[i][j]);
            if(j != 11){
                printf(", ");
            }
        }
        printf("}");
        if(i != 11){
            printf(",");
        }
    }
    printf("}\n");
    */
    double ***svd = svd_decomposition(A, 12, 12);

    printf("SVD{A}\n");
    printf("S = \n");
    matrix_print(svd[0], 12, 12);
    printf("Sigma = \n");
    matrix_print(svd[1], 12, 12);
    printf("V = \n");
    matrix_print(svd[2], 12, 12);

    double **aux_m = matrix_mult(svd[0], svd[1], 12, 12, 12, 12);
    double **VT = matrix_transpose(svd[2], 12, 12);
    double **svd_m = matrix_mult(aux_m, VT, 12, 12, 12, 12);
    printf("SVD multiplicado ( S * Sigma * V^T )\n");
    matrix_print(svd_m, 12, 12);
    printf("SVD - ");
    if(matrix_equal(A, svd_m, 12, 12, 12, 12)){
        printf("SUCESSO\n");
    }else{
        printf("FALHA\n");
    }

    matrix_free(aux_m, 12);
    matrix_free(VT, 12);
    matrix_free(svd_m, 12);


    double **p;
    p = (double**) malloc(12 * sizeof(double));
    for(uint32_t line = 0; line < 3; line ++){
        p[line] = (double*) malloc(4 * sizeof(double));
        for(uint32_t column = 0; column < 4; column++){
            p[line][column] = svd[2][line * 4 + column][11];
        }
    }
    printf("p\n");
    matrix_print(p, 3, 4);


    //point = (double*) malloc(3 * sizeof(double));
    //printf("teste com ponto i = 0\n");
    //printf("[");
    for(uint32_t i = 0; i < 6; i++){
        double *point = (double*) malloc(3 * sizeof(double));
        for(uint32_t line = 0; line < 3; line++){
            point[line] = 0;
            for(uint32_t column = 0; column < 4; column++){
                point[line] += p[line][column] * real_world_coordinates[i][column];
            }
        }
        printf("Ponto i = %d\t[", i);
        for(uint32_t line = 0; line < 3; line++){
            printf("%f", point[line] / point[2]);
            if(line == 2){
                printf("]\n");
            }else{
                printf(",");
            }
        }
        free(point);
    }
    //free(point);

    double **B_inv;
    B_inv = matrix_inverse(p, 3, 3);
    if(B_inv == NULL){
        printf("p6p_dlt: sem solução\n");
        goto p6p_dlt_end;
    }

    printf("B_inv = \n");
    matrix_print(B_inv, 3, 3);
    double **BB_inv = matrix_mult(p, B_inv, 3, 3, 3, 3);
    printf("BB_inv\n");
    matrix_print(BB_inv, 3, 3);
    matrix_free(BB_inv, 3);

    double **Z;
    Z = (double **) malloc(3 * sizeof(double*));
    for(uint32_t index = 0; index < 3; index++){
        Z[index] = (double*) malloc(sizeof(double));
        Z[index][0] = 0;
        for(uint32_t column = 0; column < 3; column++){
            Z[index][0] = Z[index][0] -B_inv[index][column] * p[column][3];
        }
    }

    printf("Z = [");
    for(uint32_t i = 0; i < 3; i++){
        printf("%f", Z[i][0]);
        if(i == 2){
            printf("]\n");
        }else{
            printf(", ");
        }
    }

    //se eu passo 3 e 3 acessa so as 3 primeiras, igual a B
    double ***qr = qr_decomposition(B_inv, 3, 3);

    KRZ = (double***) malloc(4 * sizeof(double**));
    KRZ[0] = matrix_inverse(qr[1], 3, 3);
    KRZ[1] = matrix_transpose(qr[0], 3, 3);
    KRZ[2] = Z;
    KRZ[3] = p;


    printf("qr[1]\n");
    matrix_print(qr[1], 3, 3);
    double **qrqr = matrix_mult(qr[0], qr[1], 3, 3, 3, 3);
    printf("qrqr\n");
    matrix_print(qrqr, 3, 3);
    if(matrix_equal(qrqr, B_inv, 3, 3, 3, 3) == 1){
        printf("qr_SUCCESS\n");
    }else{
        printf("qr_FAILED\n");
    }
    matrix_free(qrqr, 3);
    printf("KRZ[0] sem normalizar\n");
    matrix_print(KRZ[0], 3, 3);


    for(uint8_t i = 0; i < 3; i++){
        for(uint8_t j = 0; j < 3; j++){
            KRZ[0][i][j] = KRZ[0][i][j] / KRZ[0][2][2];
        }
    }
    printf("KRZ[0] normalizado\n");
    matrix_print(KRZ[0], 3, 3);

    matrix_free(qr[0], 3);
    matrix_free(qr[1], 3);
    free(qr);

    //free(Z);
p6p_dlt_end:
    matrix_free(B_inv, 3);
    //matrix_free(p, 3);

    matrix_free(svd[0], 12);
    matrix_free(svd[1], 12);
    matrix_free(svd[2], 12);
    free(svd);



    matrix_free(A, 12);

    //apagar isso depois
    //KRZ = NULL;
    return KRZ;

}

double ***p4p(double **K, double **pontos_real, uint32_t ** pontos_sensor){
    if(K == NULL || pontos_real == NULL || pontos_sensor == NULL){
        return NULL;
    }

    printf("-------------p4p-------------");
    printf("K\n");
    matrix_print(K, 3, 3);
    printf("pontos_real\n");
    matrix_print(pontos_real, 4, 4);
    printf("pontos_sensor\n");
    matrix_print_int(pontos_sensor, 4, 3);
    double ***RZ;

    double **K_inv = matrix_inverse(K, 3, 3);
    printf("K_inv\n");
    matrix_print(K_inv, 3, 3);
    double **Xr = matrix_transpose(pontos_real, 4, 4);
    printf("Xr\n");
    matrix_print(Xr, 4, 4);
    //double **Xs = matrix_transpose(pontos_sensor, 4, 3);
    double **Xs;
    Xs = (double**) malloc(3 * sizeof(double*));
    for(uint8_t i = 0; i < 3; i++){
        Xs[i] = (double*) malloc(4 * sizeof(double));
        for(uint8_t j = 0; j < 4; j++){
            Xs[i][j] = (double) pontos_sensor[j][i];
        }
    }
    printf("Xs\n");
    matrix_print(Xs, 3, 4);

    double **K_invXs = matrix_mult(K_inv, Xs, 3, 3, 3, 4);
    printf("K_invXs\n");
    matrix_print(K_invXs, 3, 4);

    //double **XrT = matrix_transpose(Xr, 4, 4);

    double **K_invXsXrT = matrix_mult(K_invXs, pontos_real, 3, 4, 4, 4);
    //double **K_invXsXrT = matrix_mult(K_invXs, XrT, 3, 4, 4, 4);
    printf("K_invXsXrT\n");
    matrix_print(K_invXsXrT, 3, 4);
    //matrix_free(XrT, 4);

    double **XrXrT = matrix_mult(Xr, pontos_real, 4, 4, 4, 4);
    printf("XrXrT\n");
    matrix_print(XrXrT, 4, 4);
    double **XrXrT_inv = matrix_inverse(XrXrT, 4, 4);
    printf("XrXrT_inv\n");
    matrix_print(XrXrT_inv, 4, 4);

    double **XrXrTXrXrT_inv = matrix_mult(XrXrT, XrXrT_inv, 4, 4, 4, 4);
    printf("XrXrTXrXrT_inv\n");
    matrix_print(XrXrTXrXrT_inv, 4, 4);
    matrix_free(XrXrTXrXrT_inv, 4);

    double **M = matrix_mult(K_invXsXrT, XrXrT_inv, 3, 4, 4, 4);
    printf("M\n");
    matrix_print(M, 3, 4);

    double **M_4 = (double**) malloc(3 * sizeof(double*));

    RZ = (double***) malloc(2 * sizeof(double**));
    RZ[0] = (double**) malloc(3 * sizeof(double*));
    //RZ[1] = (double**) malloc(3 * sizeof(double*));
    for(uint8_t i = 0; i < 3; i++){
        RZ[0][i] = (double*) malloc(3 * sizeof(double));
        //RZ[1][i] = (double*) malloc(1 * sizeof(double));
        M_4[i] = (double*) malloc(1 * sizeof(double));
        M_4[i][0] = -M[i][3];

        for(uint8_t j = 0; j < 3; j++){
            RZ[0][i][j] = M[i][j];
        }

    }
    for(uint8_t column = 0; column < 3; column++){
        double a = pow(RZ[0][1][column], 2) + pow(RZ[0][0][column], 2);
        if(a < 1){
            RZ[0][2][column] = sqrt(1 - a);
        }else{
            RZ[0][2][column] = 0;
        }
        //RZ[0][2][column] = sqrt(1 - pow(RZ[0][1][column], 2) - pow(RZ[0][0][column], 2));
    }
    //achou os módulos, agora falta a direção


    double **R_inv = matrix_inverse(RZ[0], 3, 3);
    RZ[1] = matrix_mult(R_inv, M_4, 3, 3, 3, 1);



    matrix_free(K_inv, 3);
    matrix_free(Xr, 4);
    matrix_free(Xs, 3);
    matrix_free(K_invXs, 3);
    matrix_free(K_invXsXrT, 3);
    matrix_free(XrXrT, 4);
    matrix_free(XrXrT_inv, 4);
    matrix_free(M, 3);
    matrix_free(M_4, 3);
    matrix_free(R_inv, 3);


    return RZ;
}

//todos os pontos no mesmo plano z
double *p4p_fischler1981(double **K, double pixelSize, double **pontos_real, double **pontos_sensor){
    printf("___p4p_fischler1981__\n");
    if(K == NULL || pixelSize == 0 || pontos_real == 0 || pontos_sensor == 0){
        return NULL;
    }
    //calcular a matriz de projeção
    double **rX = (double**) malloc(3 * sizeof(double*));
    double **sX = (double**) malloc(3 * sizeof(double*));

    double **rx4 = (double**) malloc(3 * sizeof(double*));
    double **sx4 = (double**) malloc(3 * sizeof(double*));

    for(uint8_t line = 0; line < 3; line++){
        rX[line] = (double*) malloc(3 * sizeof(double));
        sX[line] = (double*) malloc(3 * sizeof(double));

        for(uint8_t column = 0; column < 3; column++){
            if(line != 2){
                rX[line][column] = pontos_real[column][line];
            }else{
                rX[line][column] = pontos_real[column][3];
            }

            sX[line][column] = pontos_sensor[column][line];
        }
        //pula a 3 linha para rX e vai para os fatores de multiplicação
        //rX[line][2] = pontos_real[3][line];
        //sX[line][2] = pontos_sensor[2][line];

        rx4[line] = (double*) malloc(1 * sizeof(double));
        sx4[line] = (double*) malloc(1 * sizeof(double));
        if(line != 2){
            rx4[line][0] = pontos_real[3][line];
        }else{
            rx4[line][0] = pontos_real[3][3];
        }
        sx4[line][0] = pontos_sensor[3][line];
    }
    printf("rX\n");
    matrix_print(rX, 3, 3);
    printf("sX\n");
    matrix_print(sX, 3, 3);
    printf("rx4\n");
    matrix_print(rx4, 3, 1);
    printf("sx4\n");
    matrix_print(sx4, 3, 1);
    double **sX_inv = matrix_inverse(sX, 3, 3);
    printf("sX_inv\n");
    matrix_print(sX_inv, 3, 3);
    double **F = matrix_mult(sX_inv, sx4, 3, 3, 3, 1);
    printf("F\n");
    matrix_print(F, 3, 1);
    double **rX_inv = matrix_inverse(rX, 3, 3);
    printf("rX_inv\n");
    matrix_print(rX_inv, 3, 3);
    double **G = matrix_mult(rX_inv, rx4, 3, 3, 3, 1);
    printf("G \n");
    matrix_print(G , 3, 1);
    double **E = (double**) malloc(3 * sizeof(double*));
    double g3_over_f3 = G[2][0] / F[2][0];
    for(uint8_t line = 0; line < 3; line++){
        E[line] = (double*) malloc(3 * sizeof(double*));
        for(uint8_t column = 0; column < 3; column++){
            if(line == column){
                E[line][column] = (F[line][0] / G[line][0]) * g3_over_f3;
            }else{
                E[line][column] = 0;
            }
        }
    }
    printf("E \n");
    matrix_print(E, 3, 3);
    //rXT_inv = rX_invT
    double **rXT_inv = matrix_transpose(rX_inv, 3, 3);
    double **sXT = matrix_transpose(sX, 3, 3);

    double **EsXT = matrix_mult(E, sXT, 3, 3, 3, 3);
    double **PT = matrix_mult(rXT_inv, EsXT, 3, 3, 3, 3);

    //P = [inv[T]]'

    printf("PT\n");
    matrix_print(PT, 3, 3);

    //double **ET = matrix_transpose(E, 3, 3);
    //ET = E
    double **sXE = matrix_mult(sX, E, 3, 3, 3, 3);
    double **P = matrix_mult(sXE, rX_inv, 3, 3, 3, 3);
    printf("P\n");
    matrix_print(P, 3, 3);

    double **P_inv = matrix_inverse(P, 3, 3);

    matrix_free(sXE, 3);


    //double **P = matrix_transpose(PT, 3, 3);
    double **pontos_sensor_obtidos = matrix_mult(P, rX, 3, 3, 3, 3);
    for(uint8_t line = 0; line < 3; line++){
        for(uint8_t column = 0; column < 3; column++){
            pontos_sensor_obtidos[line][column] = pontos_sensor_obtidos[line][column] / pontos_sensor_obtidos[2][column];
        }
    }
    printf("pontos_sensor_obtidos\n");
    matrix_print(pontos_sensor_obtidos, 3, 3);
    //matrix_free(P, 3);
    matrix_free(pontos_sensor_obtidos, 3);

    matrix_free(rX, 3);
    matrix_free(sX, 3);
    matrix_free(rx4, 3);
    matrix_free(sx4, 3);
    matrix_free(sX_inv, 3);
    matrix_free(F, 3);
    matrix_free(rX_inv, 3);
    matrix_free(G, 3);
    matrix_free(E, 3);
    matrix_free(rXT_inv, 3);
    matrix_free(sXT, 3);
    matrix_free(EsXT, 3);

    double **PT_inv = matrix_inverse(PT, 3, 3);

    printf("PT_inv\n");
    matrix_print(PT_inv, 3, 3);

    double **xh = (double**) malloc(3 * sizeof(double));
    for(uint8_t line = 0; line < 3; line++){
        xh[line] = (double*) malloc(1 * sizeof(double));
        xh[line][0] = K[line][2];
    }
    printf("xh\n");
    matrix_print(xh, 3, 1);

    //double **rxh = matrix_mult(PT, xh, 3, 3, 3, 1);
    double **rxh = matrix_mult(P_inv, xh, 3, 3, 3, 1);
    printf("rxh\n");
    matrix_print(rxh, 3, 1);

    double **lr = (double**) malloc(3 * sizeof(double*));
    for(uint8_t line = 0; line < 3; line++){
        lr[line] = (double*) malloc(1 * sizeof(double));
        lr[line][0] = 2 == line;
    }

    double **lim = matrix_mult(P, lr, 3, 3, 3, 1);
    printf("lim\n");
    matrix_print(lim, 3, 1);

    double **rlo = matrix_mult(P_inv, lr, 3, 3, 3, 1);
    printf("rlo\n");
    matrix_print(rlo, 3, 1);

    double dim = 1 / sqrt(pow(lim[0][0] / lim[2][0], 2) + pow(lim[1][0] / lim[2][0], 2));

    printf("dim\n%f\n", dim);

    double theta = atan((K[0][0] / dim) * pixelSize);
    printf("theta\n%f\n", theta);

    double d01 = (rxh[0][0] / rxh[2][0]) * (rlo[0][0] / rlo[2][0]);
    double d02 = (rxh[1][0] / rxh[2][0]) * (rlo[1][0] / rlo[2][0]);
    double d03 = pow((rlo[0][0] / rlo[2][0]), 2) + pow((rlo[1][0] / rlo[2][0]), 2);
    double d0 = (d01 + d02) / sqrt(d03);
    if(d0 < 0){
        d0 = -d0;
    }

    /*double d0 = abs(((rxh[0][0] / rxh[2][0]) * (rlo[0][0] / rlo[2][0]) +
                     (rxh[1][0] / rxh[2][0]) * (rlo[1][0] / rlo[2][0])) /
                    (sqrt(pow((rlo[0][0] / rlo[2][0]), 2) + pow((rlo[1][0] / rlo[2][0]), 2))));
    */
    printf("d0\n%f\n", d0);

    double alpha = atan( - rxh[1][0] / rxh[0][0]);
    printf("alpha\n%f\n", alpha);

    double or1 = (rxh[0][0] / rxh[2][0]) * (rlo[0][0] / rlo[2][0]);
    double or2 = (rxh[1][0] / rxh[2][0]) * (rlo[1][0] / rlo[2][0]);
    double or = or1 + or2;

    double Xor;
    double Yor;

    if((or / (rlo[0][0] / rlo[2][0])) < 0){
        Xor = 1;
    }else{
        Xor = -1;
    }

    if((or / (rlo[1][0] / rlo[2][0])) < 0){
        Yor = 1;
    }else{
        Yor = -1;
    }

    double xc = d0 * pow(sin(theta), 2) * cos(alpha);
    if(xc < 0){
        xc = -xc;
    }
    xc = Xor * xc + rxh[0][0] / rxh[2][0];
    printf("xc\n%f\n", xc);
    double yc = d0 * pow(sin(theta), 2) * sin(alpha);
    if(yc < 0){
        yc = -yc;
    }
    yc = Yor * yc + rxh[1][0] / rxh[2][0];
    printf("yc\n%f\n", yc);
    double zc = d0 * sin(theta) * cos(theta);
    printf("zc\n%f\n", zc);



    matrix_free(P, 3);
    matrix_free(PT, 3);
    matrix_free(PT_inv, 3);
    matrix_free(P_inv, 3);
    matrix_free(rxh, 3);
    matrix_free(xh, 3);

    return NULL;
}

//todos os pontos no mesmo plano z
double *p4p_fischler1981_v2(double **K, double pixelSize, double **pontos_real, double **pontos_sensor){
    printf("___p4p_fischler1981__\n");
    if(K == NULL || pixelSize == 0 || pontos_real == 0 || pontos_sensor == 0){
        return NULL;
    }
    //calcular a matriz de projeção
    double **rX = (double**) malloc(3 * sizeof(double*));
    double **sX = (double**) malloc(3 * sizeof(double*));

    double **rx4 = (double**) malloc(3 * sizeof(double*));
    double **sx4 = (double**) malloc(3 * sizeof(double*));

    for(uint8_t line = 0; line < 3; line++){
        rX[line] = (double*) malloc(3 * sizeof(double));
        sX[line] = (double*) malloc(3 * sizeof(double));

        for(uint8_t column = 0; column < 3; column++){
            if(line != 2){
                rX[line][column] = pontos_real[column][line];
            }else{
                rX[line][column] = pontos_real[column][3];
            }

            sX[line][column] = pontos_sensor[column][line];
        }
        //pula a 3 linha para rX e vai para os fatores de multiplicação
        //rX[line][2] = pontos_real[3][line];
        //sX[line][2] = pontos_sensor[2][line];

        rx4[line] = (double*) malloc(1 * sizeof(double));
        sx4[line] = (double*) malloc(1 * sizeof(double));
        if(line != 2){
            rx4[line][0] = pontos_real[3][line];
        }else{
            rx4[line][0] = pontos_real[3][3];
        }
        sx4[line][0] = pontos_sensor[3][line];
    }
    printf("rX\n");
    matrix_print(rX, 3, 3);
    printf("sX\n");
    matrix_print(sX, 3, 3);
    printf("rx4\n");
    matrix_print(rx4, 3, 1);
    printf("sx4\n");
    matrix_print(sx4, 3, 1);
    double **sX_inv = matrix_inverse(sX, 3, 3);
    printf("sX_inv\n");
    matrix_print(sX_inv, 3, 3);
    double **F = matrix_mult(sX_inv, sx4, 3, 3, 3, 1);
    printf("F\n");
    matrix_print(F, 3, 1);
    double **rX_inv = matrix_inverse(rX, 3, 3);
    printf("rX_inv\n");
    matrix_print(rX_inv, 3, 3);
    double **G = matrix_mult(rX_inv, rx4, 3, 3, 3, 1);
    printf("G \n");
    matrix_print(G , 3, 1);
    double **E = (double**) malloc(3 * sizeof(double*));
    double g3_over_f3 = G[2][0] / F[2][0];
    for(uint8_t line = 0; line < 3; line++){
        E[line] = (double*) malloc(3 * sizeof(double*));
        for(uint8_t column = 0; column < 3; column++){
            if(line == column){
                E[line][column] = (F[line][0] / G[line][0]) * g3_over_f3;
            }else{
                E[line][column] = 0;
            }
        }
    }
    printf("E \n");
    matrix_print(E, 3, 3);
    //rXT_inv = rX_invT
    double **rXT_inv = matrix_transpose(rX_inv, 3, 3);
    double **sXT = matrix_transpose(sX, 3, 3);

    double **EsXT = matrix_mult(E, sXT, 3, 3, 3, 3);
    double **PT = matrix_mult(rXT_inv, EsXT, 3, 3, 3, 3);

    //P = [inv[T]]'

    printf("PT\n");
    matrix_print(PT, 3, 3);

    //double **ET = matrix_transpose(E, 3, 3);
    //ET = E
    double **sXE = matrix_mult(sX, E, 3, 3, 3, 3);
    double **P = matrix_mult(sXE, rX_inv, 3, 3, 3, 3);
    printf("P\n");
    matrix_print(P, 3, 3);

    double **P_inv = matrix_inverse(P, 3, 3);

    matrix_free(sXE, 3);


    //double **P = matrix_transpose(PT, 3, 3);
    double **pontos_sensor_obtidos = matrix_mult(P, rX, 3, 3, 3, 3);
    for(uint8_t line = 0; line < 3; line++){
        for(uint8_t column = 0; column < 3; column++){
            pontos_sensor_obtidos[line][column] = pontos_sensor_obtidos[line][column] / pontos_sensor_obtidos[2][column];
        }
    }
    printf("pontos_sensor_obtidos\n");
    matrix_print(pontos_sensor_obtidos, 3, 3);
    //matrix_free(P, 3);
    matrix_free(pontos_sensor_obtidos, 3);

    matrix_free(rX, 3);
    matrix_free(sX, 3);
    matrix_free(rx4, 3);
    matrix_free(sx4, 3);
    matrix_free(sX_inv, 3);
    matrix_free(F, 3);
    matrix_free(rX_inv, 3);
    matrix_free(G, 3);
    matrix_free(E, 3);
    matrix_free(rXT_inv, 3);
    matrix_free(sXT, 3);
    matrix_free(EsXT, 3);

    double **PT_inv = matrix_inverse(PT, 3, 3);

    printf("PT_inv\n");
    matrix_print(PT_inv, 3, 3);

    double **xh = (double**) malloc(3 * sizeof(double));
    for(uint8_t line = 0; line < 3; line++){
        xh[line] = (double*) malloc(1 * sizeof(double));
        xh[line][0] = K[line][2];
    }
    printf("xh\n");
    matrix_print(xh, 3, 1);

    //double **rxh = matrix_mult(PT, xh, 3, 3, 3, 1);
    //double **rxh = matrix_mult(P_inv, xh, 3, 3, 3, 1);
    //double **rxh = matrix_mult(PT_inv, xh, 3, 3, 3, 1);//artigo
    double **rxh = matrix_mult(P, xh, 3, 3, 3, 1);//
    printf("rxh\n");
    matrix_print(rxh, 3, 1);

    double **lr = (double**) malloc(3 * sizeof(double*));
    for(uint8_t line = 0; line < 3; line++){
        lr[line] = (double*) malloc(1 * sizeof(double));
        lr[line][0] = 2 == line;
    }

    //double **lim = matrix_mult(P, lr, 3, 3, 3, 1);
    double **lim = matrix_mult(PT_inv, lr, 3, 3, 3, 1);
    printf("lim\n");
    matrix_print(lim, 3, 1);

    //double **rlo = matrix_mult(P_inv, lr, 3, 3, 3, 1);
    double **rlo = matrix_mult(PT, lr, 3, 3, 3, 1);
    printf("rlo\n");
    matrix_print(rlo, 3, 1);

    //double dim = 1 / sqrt(pow(lim[0][0] / lim[2][0], 2) + pow(lim[1][0] / lim[2][0], 2));
    double dim = 1 / sqrt(pow(rlo[0][0] / rlo[2][0], 2) + pow(rlo[1][0] / rlo[2][0], 2));

    printf("dim\n%f\n", dim);

    double theta = atan((K[0][0] / dim) * pixelSize);
    printf("theta\n%f\n", theta);

    double d01 = (rxh[0][0] / rxh[2][0]) * (lim[0][0] / lim[2][0]);
    double d02 = (rxh[1][0] / rxh[2][0]) * (lim[1][0] / lim[2][0]);
    double d03 = pow((lim[0][0] / lim[2][0]), 2) + pow((lim[1][0] / lim[2][0]), 2);
    double d0 = (d01 + d02 + 1) / sqrt(d03);
    if(d0 < 0){
        d0 = -d0;
    }

    /*double d0 = abs(((rxh[0][0] / rxh[2][0]) * (rlo[0][0] / rlo[2][0]) +
                     (rxh[1][0] / rxh[2][0]) * (rlo[1][0] / rlo[2][0])) /
                    (sqrt(pow((rlo[0][0] / rlo[2][0]), 2) + pow((rlo[1][0] / rlo[2][0]), 2))));
    */
    printf("d0\n%f\n", d0);

    double alpha = atan( - lim[1][0] / lim[0][0]);
    printf("alpha\n%f\n", alpha);

    double or1 = (rxh[0][0] / rxh[2][0]) * (lim[0][0] / lim[2][0]);
    double or2 = (rxh[1][0] / rxh[2][0]) * (lim[1][0] / lim[2][0]);
    double or = or1 + or2 + 1;

    double Xor;
    double Yor;

    if((or / (lim[0][0] / lim[2][0])) < 0){
        Xor = 1;
    }else{
        Xor = -1;
    }

    if((or / (lim[1][0] / lim[2][0])) < 0){
        Yor = 1;
    }else{
        Yor = -1;
    }

    double xc = d0 * pow(sin(theta), 2) * cos(alpha);
    if(xc < 0){
        xc = -xc;
    }
    xc = Xor * xc + rxh[0][0] / rxh[2][0];
    printf("xc\n%f\n", xc);
    double yc = d0 * pow(sin(theta), 2) * sin(alpha);
    if(yc < 0){
        yc = -yc;
    }
    yc = Yor * yc + rxh[1][0] / rxh[2][0];
    printf("yc\n%f\n", yc);
    double zc = d0 * sin(theta) * cos(theta);
    printf("zc\n%f\n", zc);



    matrix_free(P, 3);
    matrix_free(PT, 3);
    matrix_free(PT_inv, 3);
    matrix_free(P_inv, 3);
    matrix_free(rxh, 3);
    matrix_free(xh, 3);

    return NULL;
}

void p4p_fischler1981_test(){
    uint8_t n = 0;
    do{
        putchar('-');
    }while(++n!=0);
    printf("p4p_fischler1981_test\n");

    double **K = (double**) malloc(3 * sizeof(double*));
    double **pontos_real = (double**) malloc(4 * sizeof(double*));
    double **pontos_sensor = (double**) malloc(4 * sizeof(double*));
    for(uint8_t line = 0; line < 4; line++){
        if(line < 3){
            K[line] = (double*) malloc(3 * sizeof(double));
        }
        pontos_sensor[line] = (double*) malloc(3 * sizeof(double));
        pontos_real[line] = (double*) malloc(4 * sizeof(double));
    }

    K[0][0] = 3048;K[0][1] = 0;K[0][2] = 0;
    K[1][0] = 0;K[1][1] = 3048;K[1][2] = 0;
    K[2][0] = 0;K[2][1] = 0;K[2][2] = 1;


    pontos_sensor[0][0] = -30;pontos_sensor[0][1] = 80;pontos_sensor[0][2] = 1;
    pontos_sensor[1][0] = -100;pontos_sensor[1][1] = -20;pontos_sensor[1][2] = 1;
    pontos_sensor[2][0] = 140;pontos_sensor[2][1] = 50;pontos_sensor[2][2] = 1;
    pontos_sensor[3][0] = -40;pontos_sensor[3][1] = -240;pontos_sensor[3][2] = 1;

    pontos_real[0][0] = -0.071263;pontos_real[0][1] = 0.029665;pontos_real[0][2] = 0;pontos_real[0][3] = 1;
    pontos_real[1][0] = -0.053033;pontos_real[1][1] = -0.006379;pontos_real[1][2] = 0;pontos_real[1][3] = 1;
    pontos_real[2][0] = -0.014063;pontos_real[2][1] = 0.061579;pontos_real[2][2] = 0;pontos_real[2][3] = 1;
    pontos_real[3][0] =  0.080120;pontos_real[3][1] = -0.030305;pontos_real[3][2] = 0;pontos_real[3][3] = 1;

    double pixelSize = 0.3048 / K[0][0];

    //p4p_fischler1981(K, pixelSize, pontos_real, pontos_sensor);
    p4p_fischler1981_v2(K, pixelSize, pontos_real, pontos_sensor);

    n = 0;
    do{
        putchar('-');
    }while(++n!=0);
    printf("p4p_fischler1981_test\n");



    K[0][0] = 2988.603737;K[0][1] = 40.688782;K[0][2] = 2175.006015;
    K[1][0] = 0;K[1][1] = 2977.833129;K[1][2] = 1344.845743;
    K[2][0] = 0;K[2][1] = 0;K[2][2] = 1;
//P1
//z[0][0] = 0;z[1][0] = -0.3;z[2][0] = 0.9;
    //4
    pontos_sensor[0][0] = 1834;pontos_sensor[0][1] = 1105;pontos_sensor[0][2] = 1;
    //5
    pontos_sensor[1][0] = 1596;pontos_sensor[1][1] = 2143;pontos_sensor[1][2] = 1;
    //6
    pontos_sensor[2][0] = 1036;pontos_sensor[2][1] = 1960;pontos_sensor[2][2] = 1;
    //7
    pontos_sensor[3][0] = 1031;pontos_sensor[3][1] = 1295;pontos_sensor[3][2] = 1;

    pontos_real[0][0] = 0.227;pontos_real[0][1] = -0.015;pontos_real[0][2] = 0.15;pontos_real[0][3] = 1;
    //5
    pontos_real[1][0] = 0.237;pontos_real[1][1] = 0.315;pontos_real[1][2] = 0.15;pontos_real[1][3] = 1;
    //6
    pontos_real[2][0] = 0.459;pontos_real[2][1] = 0.328;pontos_real[2][2] = 0.15;pontos_real[2][3] = 1;
    //7
    pontos_real[3][0] = 0.507;pontos_real[3][1] = 0.11;pontos_real[3][2] = 0.15;pontos_real[3][3] = 1;

    //pixelSize = 1.12e-6;;

    for(uint8_t i = 0; i < 4; i++){

    }

    pixelSize = 3.333e-5;
    //p4p_fischler1981(K, pixelSize, pontos_real, pontos_sensor);
    p4p_fischler1981_v2(K, pixelSize, pontos_real, pontos_sensor);

    matrix_free(K, 3);
    matrix_free(pontos_real, 4);
    matrix_free(pontos_sensor, 4);
}
