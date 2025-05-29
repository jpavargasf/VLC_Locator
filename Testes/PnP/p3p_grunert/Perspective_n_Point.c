#include "Perspective_n_Point.h"
#include "matrix.h"

int test_p6p_p4p(){
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

int test_p6p_p4p_v2(){
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

    //p3
    pontos_real[0][0] = 0.3;pontos_real[0][1] = -0.6;pontos_real[0][2] = 0.155;pontos_real[0][3] = 1;
    //1,5k
    pontos_real[1][0] = 0;pontos_real[1][1] = 0;pontos_real[1][2] = 0;pontos_real[1][3] = 1;
    //pontos_real[1][0] = 0.5;pontos_real[1][1] = -0.6;pontos_real[1][2] = 0.155;pontos_real[1][3] = 1;
    //2k
    pontos_real[2][0] = 0.5;pontos_real[2][1] = 0;pontos_real[2][2] = 0;pontos_real[2][3] = 1;
    //2,5k
    pontos_real[3][0] = 0.5;pontos_real[3][1] = 0.5;pontos_real[3][2] = 0;pontos_real[3][3] = 1;
    //p1
    pontos_real[4][0] = 0.3;pontos_real[4][1] = -0.4;pontos_real[4][2] = 0.155;pontos_real[4][3] = 1;
    //p2
    pontos_real[5][0] = 0.5;pontos_real[5][1] = -0.4;pontos_real[5][2] = 0.155;pontos_real[5][3] = 1;

    ////2m x 0y 1.5m z mais ou menos
    //resposta 0.03, 0.15, 0.02

    //p3
    pontos_real[0][0] = -0.15;pontos_real[0][1] = 0.15;pontos_real[0][2] = 0.08;pontos_real[0][3] = 1;
    //1,5k
    pontos_real[1][0] = 0.45;pontos_real[1][1] = 0.15;pontos_real[1][2] = 0.08;pontos_real[1][3] = 1;
    //pontos_real[1][0] = 0.5;pontos_real[1][1] = -0.6;pontos_real[1][2] = 0.155;pontos_real[1][3] = 1;
    //2k
    pontos_real[2][0] = 0;pontos_real[2][1] = 0.3;pontos_real[2][2] = 0.01;pontos_real[2][3] = 1;
    //2,5k
    pontos_real[3][0] = 0;pontos_real[3][1] = 0;pontos_real[3][2] = 0.01;pontos_real[3][3] = 1;
    //p1
    pontos_real[4][0] = 0.3;pontos_real[4][1] = 0;pontos_real[4][2] = 0.01;pontos_real[4][3] = 1;
    //p2
    pontos_real[5][0] = 0.3;pontos_real[5][1] = 0.3;pontos_real[5][2] = 0.01;pontos_real[5][3] = 1;

    //1k
    pontos_real_teste[0][0] = 0;pontos_real_teste[0][1] = 0.5;pontos_real_teste[0][2] = 0;pontos_real_teste[0][3] = 1;
    //p4
    pontos_real_teste[1][0] = 0.5;pontos_real_teste[1][1] = -0.6;pontos_real_teste[1][2] = 0.155;pontos_real_teste[1][3] = 1;
    //pontos_real_teste[1][0] = 0;pontos_real_teste[1][1] = 0;pontos_real_teste[1][2] = 0;pontos_real_teste[1][3] = 1;

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
                //pontos_sensor[0][0] = 3434;pontos_sensor[0][1] = 1420;pontos_sensor[0][2] = 1;
                pontos_sensor[0][0] = 593;pontos_sensor[0][1] = 625;pontos_sensor[0][2] = 1;
                //2
                pontos_sensor[1][0] = 2275;pontos_sensor[1][1] = 730;pontos_sensor[1][2] = 1;
                //pontos_sensor[1][0] = 429;pontos_sensor[1][1] = 1057;pontos_sensor[1][2] = 1;
                //4
                pontos_sensor[2][0] = 1689;pontos_sensor[2][1] = 1758;pontos_sensor[2][2] = 1;
                //5
                pontos_sensor[3][0] = 2679;pontos_sensor[3][1] = 2470;pontos_sensor[3][2] = 1;
                //6
                pontos_sensor[4][0] = 952;pontos_sensor[4][1] = 861;pontos_sensor[4][2] = 1;
                //7
                pontos_sensor[5][0] = 771;pontos_sensor[5][1] = 1283;pontos_sensor[5][2] = 1;



                //3
                //pontos_sensor_teste[0][0] = 593;pontos_sensor_teste[0][1] = 625;pontos_sensor_teste[0][2] = 1;
                pontos_sensor_teste[0][0] = 3434;pontos_sensor_teste[0][1] = 1420;pontos_sensor_teste[0][2] = 1;
                //8
                pontos_sensor_teste[1][0] = 429;pontos_sensor_teste[1][1] = 1057;pontos_sensor_teste[1][2] = 1;
                //pontos_sensor_teste[1][0] = 2275;pontos_sensor_teste[1][1] = 730;pontos_sensor_teste[1][2] = 1;


                //p8
                //x = 1050 y = 1274
                //p3
                //x = 2685 y = 1942

                z[0][0] = 0;z[1][0] = 0.3;z[2][0] = 1.25;
                break;
            case 1:
                ///pontos ex celular, nao tem valor os pontos teste
                //1
                //pontos_sensor[0][0] = 3434;pontos_sensor[0][1] = 1420;pontos_sensor[0][2] = 1;
                pontos_sensor[0][0] = 1842;pontos_sensor[0][1] = 1900;pontos_sensor[0][2] = 1;
                //2
                pontos_sensor[1][0] = 2245;pontos_sensor[1][1] = 1620;pontos_sensor[1][2] = 1;
                //pontos_sensor[1][0] = 429;pontos_sensor[1][1] = 1057;pontos_sensor[1][2] = 1;
                //4
                pontos_sensor[2][0] = 1610;pontos_sensor[2][1] = 1717;pontos_sensor[2][2] = 1;
                //5
                pontos_sensor[3][0] = 1805;pontos_sensor[3][1] = 1474;pontos_sensor[3][2] = 1;
                //6
                pontos_sensor[4][0] = 2166;pontos_sensor[4][1] = 1867;pontos_sensor[4][2] = 1;
                //7
                pontos_sensor[5][0] = 1853;pontos_sensor[5][1] = 1853;pontos_sensor[5][2] = 1;



                //3
                pontos_sensor_teste[0][0] = 1735;pontos_sensor_teste[0][1] = 2360;pontos_sensor_teste[0][2] = 1;
                //8
                pontos_sensor_teste[1][0] = 606;pontos_sensor_teste[1][1] = 808;pontos_sensor_teste[1][2] = 1;


                //p8
                //x = 1050 y = 1274
                //p3
                //x = 2685 y = 1942

                z[0][0] = 2;z[1][0] = 0;z[2][0] = 1.5;
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



void p3p_grunert_test(){
    double **K = (double**) malloc(3 * sizeof(double*));
    for(uint8_t i = 0; i < 3; i++){
        K[i] = (double*) malloc(3 * sizeof(double));
    }
    K[0][0] = 2988.603737;K[0][1] = 40.688782;K[0][2] = 2175.006015;
    K[1][0] = 0;K[1][1] = 2977.833129;K[1][2] = 1344.845743;
    K[2][0] = 0;K[2][1] = 0;K[2][2] = 1;
    matrix_print(K, 3, 3);


    uint32_t **pontos_sensor;
    double **pontos_real;

    pontos_sensor = (uint32_t**) malloc(3 * sizeof(uint32_t*));
    pontos_real = (double**) malloc(3 * sizeof(double*));

    for(uint32_t i = 0; i < 3; i++){
        pontos_real[i] = (double*) malloc(4 * sizeof(double));
        pontos_sensor[i] = (uint32_t*) malloc(3 * sizeof(uint32_t));
    }

    //1
    pontos_real[0][0] = 0;pontos_real[0][1] = 0;pontos_real[0][2] = 0;pontos_real[0][3] = 1;
    //2
    pontos_real[1][0] = -0.047;pontos_real[1][1] = 0.163;pontos_real[1][2] = 0;pontos_real[1][3] = 1;
    //4
    pontos_real[2][0] = 0.227;pontos_real[2][1] = -0.015;pontos_real[2][2] = 0.15;pontos_real[2][3] = 1;

    //pontos referentes a P1
    //1
    pontos_sensor[0][0] = 2677;pontos_sensor[0][1] = 1328;pontos_sensor[0][2] = 1;
    //2
    pontos_sensor[1][0] = 2711;pontos_sensor[1][1] = 1865;pontos_sensor[1][2] = 1;
    //4
    pontos_sensor[2][0] = 1834;pontos_sensor[2][1] = 1105;pontos_sensor[2][2] = 1;

    //z[0][0] = -0.3;z[1][0] = 0;z[2][0] = 1;

    p3p_grunert(K, pontos_real, pontos_sensor);

    matrix_free(pontos_real, 3);
    matrix_free(pontos_sensor, 3);
    matrix_free(K, 3);
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

//matriz porque pode ter até 4 soluções
double **p3p_grunert(double **K, double **pontos_real, uint32_t **pontos_sensor){
    printf("p3p_grunert\n");
    if(K == NULL || pontos_real == NULL || pontos_sensor == NULL){
        return NULL;
    }
    double **sx = (double**) malloc(3 * sizeof(double*));
    for(uint8_t line = 0; line < 3; line++){
        sx[line] = (double*) malloc(3 * sizeof(double));
        for(uint8_t column = 0; column < 3; column++){
            sx[line][column] = (double) pontos_sensor[column][line];
        }
    }

    printf("sx\n");
    matrix_print(sx, 3, 3);
    double **rx = matrix_transpose(pontos_real, 3, 4);
    printf("rx\n");
    matrix_print(rx, 4, 3);

    printf("K\n");
    matrix_print(K, 3, 3);
    double **K_inv = matrix_inverse(K, 3, 3);
    printf("K_inv\n");
    matrix_print(K_inv, 3, 3);

    double **kx = matrix_mult(K_inv, sx, 3, 3, 3, 3);

    int sign_c;
    if(K[0][0] >= 0){
        sign_c = 1;
    }else{
        sign_c = -1;
    }


    double module[3];
    double **rXi_minus_rXj = (double**) malloc(3 * sizeof(double*));
    for(uint8_t line = 0; line < 3; line++){
        rXi_minus_rXj[line] = (double*) malloc(3 * sizeof(double));
    }
    int8_t rXi_minus_rXj_index = -1;
    //módulo ao quadrado
    double module2_rx_minus[3];
    //normaliza kx
    for(uint8_t column = 0; column < 3; column++){
        module[column] = 0;
        module2_rx_minus[column] = 0;
        for(uint8_t line = 0; line < 3; line++){
            module[column] += pow(kx[line][column], 2);
        }
        module[column] = sqrt(module[column]);
        for(uint8_t line = 0; line < 3; line++){
            if(module[column] != 0){
                kx[line][column] = sign_c * (kx[line][column] / module[column]);
            }
            //para kXi_plus_kXj
            for(uint8_t column2 = 0; column2 < column; column2++){
                rXi_minus_rXj[line][rXi_minus_rXj_index + column2] = rx[line][column] - rx[line][column2];
                module2_rx_minus[rXi_minus_rXj_index + column2] += pow(rXi_minus_rXj[line][rXi_minus_rXj_index + column2], 2);
            }
        }
        rXi_minus_rXj_index++;
    }
    printf("kx\n");
    matrix_print(kx, 3, 3);
    printf("rXi_minus_rXj\n");
    matrix_print(rXi_minus_rXj, 3, 3);
    //kXi_plus_kXj
    //0 - x2 - x1
    //1 - x3 - x1
    //2 - x3 - x2

    printf("module rXi_minus_rXj\n");
    for(uint8_t i = 0; i < 3; i++){
        module2_rx_minus[i] = sqrt(module2_rx_minus[i]);
        printf("%f\n", module2_rx_minus[i]);
        //module[i] = pow(module[i], 2);
    }

    //double a = module2_rx_minus[2];
    //double b = module2_rx_minus[1];
    //double c = module2_rx_minus[0];

    //calcula os angulos alpha, beta e gama
    //double cos_alpha = (module2_kx_plus[2] - pow());

    double **kxi_point_kxj = (double**) malloc(1 * sizeof(double*));
    kxi_point_kxj[0] = (double*) malloc(3 * sizeof(double));
    for(uint8_t i = 0; i < 3; i++){
        kxi_point_kxj[0][i] = 0;
    }
    for(uint8_t column1 = 0; column1 < 2; column1++){
        for(uint8_t column2 = column1 + 1; column2 < 3; column2++){
            uint8_t index = (column1 + 1) * (column2 - 1);
            for(uint8_t line = 0; line < 3; line++){
                kxi_point_kxj[0][index] += kx[line][column1] * kx[line][column2];
            }
        }
    }
    printf("kxi_point_kxj\n");
    matrix_print(kxi_point_kxj, 1, 3);
    //0 - x1x2
    //1 - x1x3
    //2 - x2x3

    //modulo de kxi é 1 porque foi normalizado
    double cos_alpha = kxi_point_kxj[0][2];
    double cos_beta = kxi_point_kxj[0][1];
    double cos_gama = kxi_point_kxj[0][0];

    double a = module2_rx_minus[2];
    double b = module2_rx_minus[1];
    double c = module2_rx_minus[0];

    double a2 = pow(a, 2);
    double b2 = pow(b, 2);
    double c2 = pow(c, 2);

    double *p = (double*) malloc(5 * sizeof(double));

    //para auxiliar
    double a2c2b2_m = (a2 - c2) / b2;
    double a2c2b2_p = (a2 + c2) / b2;
    double cos2_a = pow(cos_alpha, 2);
    double cos2_b = pow(cos_beta, 2);
    double cos2_g = pow(cos_gama, 2);

    ////A4 ou C4
    p[0] = pow((a2c2b2_m - 1), 2) - 4 * (c2 / b2) * cos2_a;

    //A3 ou C3
    p[1] = 4 * (a2c2b2_m * (1 - a2c2b2_m) * cos_beta -
                (1 - a2c2b2_p) * cos_alpha * cos_gama +
                2 * (c2 / b2) * cos2_a * cos_beta);

    //A2 ou C2
    p[2] = 2 * (pow(a2c2b2_m, 2) - 1 + 2 * pow(a2c2b2_m, 2) * cos2_b +
                2 * (1 - c2 / b2) * cos2_a -
                4 * a2c2b2_p * cos_alpha * cos_beta * cos_gama +
                2 * (1 - a2 / b2) * cos2_g);

    //A1 ou C1
    p[3] = 4 * ( - a2c2b2_m * (1 + a2c2b2_m) * cos_beta +
                2 * (a2 / b2) * cos2_g * cos_beta -
                (1 - a2c2b2_p) * cos_alpha * cos_gama);

    //A0 ou C0
    p[4] = pow((1 + a2c2b2_m), 2) - 4 * (a2 / b2) * cos2_g;

    print_polinomio(p, 4);

    //double *r = bisection_method(p, 4, 1e-5);
    double **r = global_newton_method(p, 4, 1e-10);
    for(uint8_t i = 0; i < 4; i++){
        if(r[i] == NULL)    continue;
        printf("root %d = %f\n", i, r[i][0]);
    }


    double **solution = (double**) malloc(4 * sizeof(double*));


    //double s1[4];
    //double s2[4];
    //double s3[4];
    for(uint8_t i = 0; i < 4; i++){
        solution[i] = (double*) malloc(3 * sizeof(double));
        if(r[i] == NULL)    goto loop_p3p_grunert_no_solution;
        double aux = b2 / (1 + pow(r[i][0], 2) - 2 * r[i][0] * cos_beta);
        if(aux < 0 || r[i][0] < 0){
loop_p3p_grunert_no_solution:
            free(solution[i]);
            solution[i] = NULL;
            continue;
        }
        ///s1[i] = sqrt(aux);
        solution[i][0] = sqrt(aux);
        //s3[i] = r[i][0] * s1[i];
        solution[i][2] = r[i][0] * solution[i][0];

        //printf("s1 = %f\ns3 = %f\n", s1[i], s3[i]);

        double *polinomio_s2 = (double*) malloc(3 * sizeof(double));
        polinomio_s2[0] = 1;
        //polinomio_s2[1] = -2 * cos_alpha * s3[i];
        polinomio_s2[1] = -2 * cos_alpha * solution[i][2];
        //polinomio_s2[2] = pow(s3[i], 2) - a2;
        polinomio_s2[2] = pow(solution[i][2], 2) - a2;

        printf("polinomio_s2\n");
        print_polinomio(polinomio_s2, 2);
        //double *s2_i = bisection_method(polinomio_s2, 2, 1e-5);
        double delta = pow(polinomio_s2[1], 2) - 4 * polinomio_s2[0] * polinomio_s2[2];

        printf("delta = %f\n", delta);
        if(delta < 0){
            goto loop_p3p_grunert_no_solution;
        }
        delta = sqrt(delta);
        //double r1 = (-polinomio_s2[1] + delta) / 2;
        //s2[i] = (-polinomio_s2[1] + delta) / 2;
        solution[i][1] = (-polinomio_s2[1] + delta) / 2;
        //printf("s2 = %f\n", s2[i]);


        //printf("s2_1 = %f\ts2_2 = %f\n", s2_i[0], s2_i[1]);

        //free(s2_i);

        free(polinomio_s2);
        free(r[i]);
    }

    free(r);

    for(uint8_t i = 0; i < 4; i++){
        printf("Solucao %d:", i + 1);
        if(solution[i] == NULL){
            printf("NULL");
        }else{
            for(uint8_t j = 0; j < 3; j++){
                printf("s%d = %f\t", j + 1, solution[i][j]);
            }
        }
        putchar('\n');
    }

    free(p);
    matrix_free(kxi_point_kxj, 1);
    matrix_free(rXi_minus_rXj, 3);
    matrix_free(sx, 3);
    matrix_free(rx, 4);
    matrix_free(K_inv, 3);
    matrix_free(kx, 3);

    return solution;
}

void **p4p_grunert(double **K, double **pontos_real, uint32_t **pontos_sensor){
    printf("p4p_grunert\n");

    printf("pontos 1, 2 e 3\n");
    double **solution_1 = p3p_grunert(K, pontos_real, pontos_sensor);

    uint8_t index_ps = rand()%3;
    double *pr_aux = pontos_real[index_ps];
    uint32_t *ps_aux = pontos_sensor[index_ps];
    pontos_real[index_ps] = pontos_real[3];
    pontos_sensor[index_ps] = pontos_sensor[3];

    printf("pontos ");
    for(uint8_t i = 0; i < 4; i++){
        if(index_ps == i){
            continue;
        }
        printf("%d, ", i + 1);
    }
    putchar('\n');
    double **solution_2 = p3p_grunert(K, pontos_real, pontos_sensor);

    pontos_real[index_ps] = pr_aux;
    pontos_sensor[index_ps] = ps_aux;


    matrix_free(solution_1, 4);
    matrix_free(solution_2, 4);

    return NULL;

}

void **p4p_grunert_v2(double **K, double **pontos_real, uint32_t **pontos_sensor){
    printf("p4p_grunert\n");

    printf("p3p_grunert\n");
    if(K == NULL || pontos_real == NULL || pontos_sensor == NULL){
        return NULL;
    }
    double **sx = (double**) malloc(3 * sizeof(double*));
    for(uint8_t line = 0; line < 3; line++){
        sx[line] = (double*) malloc(3 * sizeof(double));
        for(uint8_t column = 0; column < 3; column++){
            sx[line][column] = (double) pontos_sensor[column][line];
        }
    }

    printf("sx\n");
    matrix_print(sx, 3, 3);
    double **rx = matrix_transpose(pontos_real, 3, 4);
    printf("rx\n");
    matrix_print(rx, 4, 3);

    printf("K\n");
    matrix_print(K, 3, 3);
    double **K_inv = matrix_inverse(K, 3, 3);
    printf("K_inv\n");
    matrix_print(K_inv, 3, 3);

    double **kx = matrix_mult(K_inv, sx, 3, 3, 3, 3);

    int sign_c;
    if(K[0][0] >= 0){
        sign_c = 1;
    }else{
        sign_c = -1;
    }


    double module[3];
    double **rXi_minus_rXj = (double**) malloc(3 * sizeof(double*));
    for(uint8_t line = 0; line < 3; line++){
        rXi_minus_rXj[line] = (double*) malloc(3 * sizeof(double));
    }
    int8_t rXi_minus_rXj_index = -1;
    //módulo ao quadrado
    double module2_rx_minus[3];
    //normaliza kx
    for(uint8_t column = 0; column < 3; column++){
        module[column] = 0;
        module2_rx_minus[column] = 0;
        for(uint8_t line = 0; line < 3; line++){
            module[column] += pow(kx[line][column], 2);
        }
        module[column] = sqrt(module[column]);
        for(uint8_t line = 0; line < 3; line++){
            if(module[column] != 0){
                kx[line][column] = sign_c * (kx[line][column] / module[column]);
            }
            //para kXi_plus_kXj
            for(uint8_t column2 = 0; column2 < column; column2++){
                rXi_minus_rXj[line][rXi_minus_rXj_index + column2] = rx[line][column] - rx[line][column2];
                module2_rx_minus[rXi_minus_rXj_index + column2] += pow(rXi_minus_rXj[line][rXi_minus_rXj_index + column2], 2);
            }
        }
        rXi_minus_rXj_index++;
    }
    printf("kx\n");
    matrix_print(kx, 3, 3);
    printf("rXi_minus_rXj\n");
    matrix_print(rXi_minus_rXj, 3, 3);
    //kXi_plus_kXj
    //0 - x2 - x1
    //1 - x3 - x1
    //2 - x3 - x2

    printf("module rXi_minus_rXj\n");
    for(uint8_t i = 0; i < 3; i++){
        module2_rx_minus[i] = sqrt(module2_rx_minus[i]);
        printf("%f\n", module2_rx_minus[i]);
        //module[i] = pow(module[i], 2);
    }

    //double a = module2_rx_minus[2];
    //double b = module2_rx_minus[1];
    //double c = module2_rx_minus[0];

    //calcula os angulos alpha, beta e gama
    //double cos_alpha = (module2_kx_plus[2] - pow());

    double **kxi_point_kxj = (double**) malloc(1 * sizeof(double*));
    kxi_point_kxj[0] = (double*) malloc(3 * sizeof(double));
    for(uint8_t i = 0; i < 3; i++){
        kxi_point_kxj[0][i] = 0;
    }
    for(uint8_t column1 = 0; column1 < 2; column1++){
        for(uint8_t column2 = column1 + 1; column2 < 3; column2++){
            uint8_t index = (column1 + 1) * (column2 - 1);
            for(uint8_t line = 0; line < 3; line++){
                kxi_point_kxj[0][index] += kx[line][column1] * kx[line][column2];
            }
        }
    }
    printf("kxi_point_kxj\n");
    matrix_print(kxi_point_kxj, 1, 3);
    //0 - x1x2
    //1 - x1x3
    //2 - x2x3

    //modulo de kxi é 1 porque foi normalizado
    double cos_alpha = kxi_point_kxj[0][2];
    double cos_beta = kxi_point_kxj[0][1];
    double cos_gama = kxi_point_kxj[0][0];

    double a = module2_rx_minus[2];
    double b = module2_rx_minus[1];
    double c = module2_rx_minus[0];

    double a2 = pow(a, 2);
    double b2 = pow(b, 2);
    double c2 = pow(c, 2);

    double *p = (double*) malloc(5 * sizeof(double));

    //para auxiliar
    double a2c2b2_m = (a2 - c2) / b2;
    double a2c2b2_p = (a2 + c2) / b2;
    double cos2_a = pow(cos_alpha, 2);
    double cos2_b = pow(cos_beta, 2);
    double cos2_g = pow(cos_gama, 2);

    ////A4 ou C4
    p[0] = pow((a2c2b2_m - 1), 2) - 4 * (c2 / b2) * cos2_a;

    //A3 ou C3
    p[1] = 4 * (a2c2b2_m * (1 - a2c2b2_m) * cos_beta -
                (1 - a2c2b2_p) * cos_alpha * cos_gama +
                2 * (c2 / b2) * cos2_a * cos_beta);

    //A2 ou C2
    p[2] = 2 * (pow(a2c2b2_m, 2) - 1 + 2 * pow(a2c2b2_m, 2) * cos2_b +
                2 * (1 - c2 / b2) * cos2_a -
                4 * a2c2b2_p * cos_alpha * cos_beta * cos_gama +
                2 * (1 - a2 / b2) * cos2_g);

    //A1 ou C1
    p[3] = 4 * ( - a2c2b2_m * (1 + a2c2b2_m) * cos_beta +
                2 * (a2 / b2) * cos2_g * cos_beta -
                (1 - a2c2b2_p) * cos_alpha * cos_gama);

    //A0 ou C0
    p[4] = pow((1 + a2c2b2_m), 2) - 4 * (a2 / b2) * cos2_g;

    print_polinomio(p, 4);

    //double *r = bisection_method(p, 4, 1e-5);
    double **r = global_newton_method(p, 4, 1e-10);
    for(uint8_t i = 0; i < 4; i++){
        if(r[i] == NULL)    continue;
        printf("root %d = %f\n", i, r[i][0]);
    }


    double **solution = (double**) malloc(4 * sizeof(double*));


    //double s1[4];
    //double s2[4];
    //double s3[4];
    for(uint8_t i = 0; i < 4; i++){
        solution[i] = (double*) malloc(3 * sizeof(double));
        if(r[i] == NULL)    goto loop_p3p_grunert_no_solution;
        double aux = b2 / (1 + pow(r[i][0], 2) - 2 * r[i][0] * cos_beta);
        if(aux < 0 || r[i][0] < 0){
loop_p3p_grunert_no_solution:
            free(solution[i]);
            solution[i] = NULL;
            continue;
        }
        ///s1[i] = sqrt(aux);
        solution[i][0] = sqrt(aux);
        //s3[i] = r[i][0] * s1[i];
        solution[i][2] = r[i][0] * solution[i][0];

        //printf("s1 = %f\ns3 = %f\n", s1[i], s3[i]);

        double *polinomio_s2 = (double*) malloc(3 * sizeof(double));
        polinomio_s2[0] = 1;
        //polinomio_s2[1] = -2 * cos_alpha * s3[i];
        polinomio_s2[1] = -2 * cos_alpha * solution[i][2];
        //polinomio_s2[2] = pow(s3[i], 2) - a2;
        polinomio_s2[2] = pow(solution[i][2], 2) - a2;

        printf("polinomio_s2\n");
        print_polinomio(polinomio_s2, 2);
        //double *s2_i = bisection_method(polinomio_s2, 2, 1e-5);
        double delta = pow(polinomio_s2[1], 2) - 4 * polinomio_s2[0] * polinomio_s2[2];

        printf("delta = %f\n", delta);
        if(delta < 0){
            goto loop_p3p_grunert_no_solution;
        }
        delta = sqrt(delta);
        //double r1 = (-polinomio_s2[1] + delta) / 2;
        //s2[i] = (-polinomio_s2[1] + delta) / 2;
        solution[i][1] = (-polinomio_s2[1] + delta) / 2;
        //printf("s2 = %f\n", s2[i]);


        //printf("s2_1 = %f\ts2_2 = %f\n", s2_i[0], s2_i[1]);

        //free(s2_i);

        free(polinomio_s2);
        free(r[i]);
    }

    free(r);

    double ***kX = (double ***) malloc(4 * sizeof(double**));

    for(uint8_t i = 0; i < 4; i++){
        printf("Solucao %d:", i + 1);
        if(solution[i] == NULL){
            printf("NULL\n");
            kX[i] = NULL;
        }else{
            for(uint8_t j = 0; j < 3; j++){
                printf("s%d = %f\t", j + 1, solution[i][j]);
            }
            putchar('\n');
            kX[i] = (double**) malloc(3 * sizeof(double));
            for(uint8_t line = 0; line < 3; line++){
                kX[i][line] = (double *) malloc(3 * sizeof(double));
                for(uint8_t column = 0; column < 3; column++){
                    kX[i][line][column] = solution[i][column] * kx[line][column];
                }
            }
            printf("kX\n");
            matrix_print(kX[i], 3, 3);
            //double ***Rt = optimal_rotation_translation(rx, kX[i], 3, 3);
            double ***Rt = optimal_rotation_translation_3D(rx, kX[i], 3, 3);
            if(Rt != NULL){
                printf("R\n");
                matrix_print(Rt[0], 3, 3);
                printf("Z\n");
                matrix_print(Rt[1], 3, 1);
                double **P = projection_matrix(K, Rt[0], Rt[1]);
                printf("P\n");
                matrix_print(P, 3, 4);

                double **PrX = matrix_mult(P, rx, 3, 4, 4, 3);

                //normaliza pontos
                for(uint8_t column = 0; column < 3; column++){
                    for(uint8_t line = 0; line < 3; line++){
                        PrX[line][column] = PrX[line][column] / PrX[2][column];
                    }
                }
                printf("rx\n");
                matrix_print(rx, 4, 3);
                printf("PrX dos 3 pontos\n");
                matrix_print(PrX, 3, 3);

                double **x4 = (double**) malloc(4 * sizeof(double*));
                for(uint8_t line = 0; line < 4; line++){
                    x4[line] = (double*) malloc(1 * sizeof(double));
                    x4[line][0] = pontos_real[3][line];
                }
                double **Px4 = matrix_mult(P, x4, 3, 4, 4, 1);
                for(uint8_t line = 0; line < 3; line++){
                    Px4[line][0] = Px4[line][0] / Px4[2][0];
                }
                printf("x4\n");
                matrix_print(x4, 4, 1);
                printf("Px4\n");
                matrix_print(Px4, 3, 1);
                matrix_free(x4, 4);
                matrix_free(Px4, 3);


                matrix_free(PrX, 3);



                matrix_free(P, 3);
                matrix_free(Rt[0], 3);
                matrix_free(Rt[1], 3);
                free(Rt);

            }
        }
    }

    for(uint8_t i = 0; i < 3; i++){
        if(kX[i] != NULL){
            matrix_free(kX[i], 3);
        }
    }
    free(kX);



    free(p);
    matrix_free(kxi_point_kxj, 1);
    matrix_free(rXi_minus_rXj, 3);
    matrix_free(sx, 3);
    matrix_free(rx, 4);
    matrix_free(K_inv, 3);
    matrix_free(kx, 3);

    matrix_free(solution, 4);
    return NULL;

}


void p4p_grunert_test(){
    printf("p4p_grunert_test\n");

    double **K = (double**) malloc(3 * sizeof(double*));
    double **pontos_real = (double**) malloc(4 * sizeof(double*));
    uint32_t **pontos_sensor = (uint32_t**) malloc(4 * sizeof(uint32_t*));
    for(uint8_t line = 0; line < 4; line++){
        if(line < 3){
            K[line] = (double*) malloc(3 * sizeof(double));
        }
        pontos_sensor[line] = (uint32_t*) malloc(3 * sizeof(uint32_t));
        pontos_real[line] = (double*) malloc(4 * sizeof(double));
    }



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



    //p4p_grunert(K, pontos_real, pontos_sensor);
    p4p_grunert_v2(K, pontos_real, pontos_sensor);
    matrix_free(K, 3);
    matrix_free(pontos_real, 4);
    matrix_free(pontos_sensor, 4);

}

double ***optimal_rotation_translation(double **A, double **B, uint32_t n_pontos, uint32_t dimensions){
    if(A == NULL || B == NULL || n_pontos < dimensions || dimensions == 0){
        return NULL;
    }
    printf("entering optimal_rotation_translation\n");
    printf("A\n");
    matrix_print(A, dimensions, n_pontos);
    printf("B\n");
    matrix_print(B, dimensions, n_pontos);

    double **centroid_A = centroid(A, dimensions, n_pontos);
    double **centroid_B = centroid(B, dimensions, n_pontos);

    printf("centroid_A\n");
    matrix_print(centroid_A, dimensions, 1);
    printf("centroid_B\n");
    matrix_print(centroid_B, dimensions, 1);

    double **A_copy = matrix_copy(A, dimensions, n_pontos);
    double **B_copy = matrix_copy(B, dimensions, n_pontos);

    for(uint8_t line = 0; line < dimensions; line++){
        for(uint8_t column = 0; column < n_pontos; column++){
            A_copy[line][column] = A_copy[line][column] - centroid_A[line][0];
            B_copy[line][column] = B_copy[line][column] - centroid_B[line][0];
        }
    }

    printf("A - centroid_A\n");
    matrix_print(A_copy, dimensions, n_pontos);
    printf("B - centroid_B\n");
    matrix_print(B_copy, dimensions, n_pontos);

    double **Bc_T = matrix_transpose(B_copy, dimensions, n_pontos);
    matrix_free(B_copy, dimensions);


    double **H = matrix_mult(A_copy, Bc_T, dimensions, n_pontos, n_pontos, dimensions);
    matrix_free(Bc_T, n_pontos);
    matrix_free(A_copy, dimensions);

    printf("H\n");
    matrix_print(H, dimensions, dimensions);

    //traco nao funcionou para ter a rotacao
    /*
    double lambda = 1e-5;
    double traca = 0;
    for(uint32_t i = 0; i < dimensions; i++){
        traca += H[i][i];
    }
    for(uint32_t i = 0; i < dimensions; i++){
        H[i][i] += traca * lambda;
    }
    printf("H + lambda * traca\n");
    matrix_print(H, dimensions, dimensions);
*/

    double ***svd = svd_decomposition(H, dimensions, dimensions);
    matrix_free(H, dimensions);
    double **UT = matrix_transpose(svd[0], dimensions, dimensions);

    double **R = matrix_mult(svd[2], UT, dimensions, dimensions, dimensions, dimensions);

    double *R_determinant = matrix_determinant(R, dimensions, dimensions);

    printf("R\n");
    matrix_print(R, dimensions, dimensions);
    printf("determinant = %f\n", *R_determinant);

    //caso especial de reflexão
    if(*R_determinant < 0){
        //multiplicar a ultima coluna de V por -1
        for(uint32_t i = 0; i < dimensions; i++){
            svd[2][i][dimensions - 1] = -svd[2][i][dimensions - 1];
        }
        matrix_free(R, dimensions);
        R = matrix_mult(svd[2], UT, dimensions, dimensions, dimensions, dimensions);
    }
    free(R_determinant);
    matrix_free(UT, dimensions);
    matrix_free(svd[0], dimensions);
    matrix_free(svd[1], dimensions);
    matrix_free(svd[2], dimensions);
    free(svd);
    //encontrar t

    //checa se os vetores de R tem modulo 1

    for(uint32_t column = 0; column < dimensions; column++){
        double module = 0;
        for(uint32_t line = 0; line < dimensions; line++){
            module += pow(R[line][column], 2);
        }
        module = sqrt(module);
        if(module != 1){
            if(module < eps){
                /*
                //escolher um vetor em todas as direcoes e remover a direcao dos
                //outros vetores
                //iniciar vetor
                printf("modulo errado\ngrand-schmidt\n");
                double aux = 1 / sqrt(dimensions);
                for(uint32_t line = 0; line < dimensions; line++){
                    R[line][column] = aux;
                }
                double *internal_product_memmory = (double*) malloc((dimensions - 1) * sizeof(double));
                uint32_t index_c = 0;
                for(uint32_t c = 0; c < dimensions; c++){
                    if(c == column){
                        continue;
                    }
                    internal_product_memmory[index_c++] = internal_product(R, column, R, c, dimensions);
                }
                module = 0;
                for(uint32_t line = 0; line < dimensions; line++){
                    index_c = 0;
                    for(uint32_t c = 0; c < dimensions; c++){
                        if(c == column){
                            continue;
                        }
                        R[line][column] = R[line][column] - internal_product_memmory[index_c++] * R[line][c];
                    }
                    module += pow(R[line][column], 2);
                }
                module = sqrt(module);
                if(module > eps){
                    for(uint32_t line = 0; line < dimensions; line++){
                        R[line][column] = R[line][column] / module;
                    }
                }

                free(internal_product_memmory);
                printf("R\n");
                matrix_print(R, dimensions, dimensions);
                */
            }else{
                for(uint32_t line = 0; line < dimensions; line++){
                    R[line][column] = R[line][column] / module;
                }
            }
        }
    }



    double **aux_t = matrix_mult(R, centroid_A, dimensions, dimensions, dimensions, 1);
    double **t = (double **) malloc(dimensions * sizeof(double*));
    for(uint32_t i = 0; i < dimensions; i++){
        t[i] = (double*) malloc(sizeof(double));
        t[i][0] = centroid_B[i][0] - aux_t[i][0];
    }
    matrix_free(aux_t, dimensions);
    matrix_free(centroid_A, dimensions);
    matrix_free(centroid_B, dimensions);

    double ***Rt = (double***) malloc(2 * sizeof(double**));
    Rt[0] = R;
    Rt[1] = t;

    printf("exiting optimal_rotation_translation\n");

    return Rt;
}

double ***optimal_rotation_translation_3D(double **A, double **B, uint32_t n_pontos, uint32_t dimensions){
    if(A == NULL || B == NULL || n_pontos < dimensions || dimensions != 3){
        return NULL;
    }
    //printf("entering optimal_rotation_translation\n");
    //printf("A\n");
    //matrix_print(A, dimensions, n_pontos);
    //printf("B\n");
    //matrix_print(B, dimensions, n_pontos);

    double **centroid_A = centroid(A, dimensions, n_pontos);
    double **centroid_B = centroid(B, dimensions, n_pontos);

    //printf("centroid_A\n");
    //matrix_print(centroid_A, dimensions, 1);
    //printf("centroid_B\n");
    //matrix_print(centroid_B, dimensions, 1);

    double **A_copy = matrix_copy(A, dimensions, n_pontos);
    double **B_copy = matrix_copy(B, dimensions, n_pontos);

    for(uint8_t line = 0; line < dimensions; line++){
        for(uint8_t column = 0; column < n_pontos; column++){
            A_copy[line][column] = A_copy[line][column] - centroid_A[line][0];
            B_copy[line][column] = B_copy[line][column] - centroid_B[line][0];
        }
    }

    //printf("A - centroid_A\n");
    //matrix_print(A_copy, dimensions, n_pontos);
    //printf("B - centroid_B\n");
    //matrix_print(B_copy, dimensions, n_pontos);

    double **Bc_T = matrix_transpose(B_copy, dimensions, n_pontos);
    matrix_free(B_copy, dimensions);


    double **H = matrix_mult(A_copy, Bc_T, dimensions, n_pontos, n_pontos, dimensions);
    //double **H = matrix_mult(Bc_T, A_copy, 3, 3, 3, 3);
    matrix_free(Bc_T, n_pontos);
    matrix_free(A_copy, dimensions);

    //printf("H\n");
    //matrix_print(H, dimensions, dimensions);

    //traco nao funcionou para ter a rotacao
    /*
    double lambda = 1e-5;
    double traca = 0;
    for(uint32_t i = 0; i < dimensions; i++){
        traca += H[i][i];
    }
    for(uint32_t i = 0; i < dimensions; i++){
        H[i][i] += traca * lambda;
    }
    printf("H + lambda * traca\n");
    matrix_print(H, dimensions, dimensions);
*/

    double ***svd = svd_decomposition(H, dimensions, dimensions);
    //if(svd == NULL){
        //printf("svd NULL\n");
    //}
    matrix_free(H, dimensions);
    double **UT = matrix_transpose(svd[0], dimensions, dimensions);
    //double **VT = matrix_transpose(svd[2], dimensions, dimensions);
    //printf("svd\nU\n");
    //matrix_print(svd[0], dimensions, dimensions);
    //printf("Sigma\n");
    //matrix_print(svd[1], dimensions, dimensions);
    //printf("V\n");
    //matrix_print(svd[2], dimensions, dimensions);

    double **R = matrix_mult(svd[2], UT, dimensions, dimensions, dimensions, dimensions);
    //double **R = matrix_mult(svd[0], VT, dimensions, dimensions, dimensions, dimensions);

    double *R_determinant = matrix_determinant(R, dimensions, dimensions);

    //printf("R\n");
    //matrix_print(R, dimensions, dimensions);
    //printf("determinant = %f\n", *R_determinant);

    //caso especial de reflexão
    if(*R_determinant < 0){
        //multiplicar a ultima coluna de V por -1
        for(uint32_t i = 0; i < dimensions; i++){
            svd[2][i][dimensions - 1] = -svd[2][i][dimensions - 1];
            //VT[dimensions - 1][i] = -VT[dimensions - 1][i];
        }
        matrix_free(R, dimensions);
        R = matrix_mult(svd[2], UT, dimensions, dimensions, dimensions, dimensions);
        //R = matrix_mult(svd[0], VT, dimensions, dimensions, dimensions, dimensions);
    }
    free(R_determinant);
    matrix_free(UT, dimensions);
    //matrix_free(VT, dimensions);
    matrix_free(svd[0], dimensions);
    matrix_free(svd[1], dimensions);
    matrix_free(svd[2], dimensions);
    free(svd);
    //encontrar t

    //checa se os vetores de R tem modulo 1

    for(uint32_t column = 0; column < dimensions; column++){
        double module = 0;
        for(uint32_t line = 0; line < dimensions; line++){
            module += pow(R[line][column], 2);
        }
        module = sqrt(module);
        if(module != 1){
            if(module < eps){
                uint8_t cross_product_index[2];
                uint8_t index = 0;
                for(uint8_t i = 0; i < 3; i++){
                    if(i != column){
                        cross_product_index[index++] = i;
                    }
                }
                for(uint8_t line1 = 0; line1 < 3; line1++){
                    for(uint8_t line2 = 0; line2 < 3; line2++){
                        if(line1 == line2){
                            continue;
                        }
                        //definir a linha de onde cairá o resultado
                        uint8_t soma = line1 + line2;
                        double signal;
                        uint8_t comp;
                        switch(soma){
                        case 1:
                            index = 2;
                            comp = 0;
                            break;
                        case 2:
                            index = 1;
                            comp = 2;
                            break;
                        case 3:
                            index = 0;
                            comp = 1;
                            break;
                        default:
                            break;
                        }
                        if(line1 == comp){
                            signal = 1;
                        }else{
                            signal = -1;
                        }
                        R[index][column] += signal * R[line1][cross_product_index[0]] * R[line2][cross_product_index[1]];
                    }
                }
                //printf("erro_coordenada degenerativa em R\n");
                //printf("novo R\n");
                //matrix_print(R, 3, 3);
                R_determinant = matrix_determinant(R, 3, 3);
                //printf("R_determinant = %f\n", *R_determinant);
                if(*R_determinant < 0){
                    for(uint8_t line = 0; line < 3; line++){
                        R[line][column] = -R[line][column];
                    }
                    //printf("novo R\n");
                    //matrix_print(R, 3, 3);
                    free(R_determinant);
                    R_determinant = matrix_determinant(R, 3, 3);
                    //printf("R_determinant = %f\n", *R_determinant);
                }
                free(R_determinant);
            }
        }
    }




    double **aux_t = matrix_mult(R, centroid_A, dimensions, dimensions, dimensions, 1);
    double **t = (double **) malloc(dimensions * sizeof(double*));
    for(uint32_t i = 0; i < dimensions; i++){
        t[i] = (double*) malloc(sizeof(double));
        t[i][0] = centroid_B[i][0] - aux_t[i][0];
    }
    matrix_free(aux_t, dimensions);
    matrix_free(centroid_A, dimensions);
    matrix_free(centroid_B, dimensions);

    double ***Rt = (double***) malloc(2 * sizeof(double**));
    Rt[0] = R;
    Rt[1] = t;

    //printf("exiting optimal_rotation_translation\n");

    return Rt;
}

double **projection_matrix(double **K, double **R, double **Z){
    if(K == NULL || R == NULL || Z == NULL){
        return NULL;
    }

    //double **KR = matrix_mult(K, R, 3, 3, 3, 3);
    double **I3Z = (double**) malloc(3 * sizeof(double*));
    for(uint8_t line = 0; line < 3; line++){
        I3Z[line] = (double*) malloc(4 * sizeof(double));
        for(uint8_t column = 0; column < 4; column++){
            if(column < 3){
                //I3Z[line][column] = line == column;
                I3Z[line][column] = R[line][column];
            }else{
                I3Z[line][column] = -Z[line][0];
            }
        }
    }
    //double **P = matrix_mult(KR, I3Z, 3, 3, 3, 4);
    double **P = matrix_mult(K, I3Z, 3, 3, 3, 4);
    //matrix_free(KR, 3);
    matrix_free(I3Z, 3);
    return P;
}

void Rt_test(){
    printf("Rt_test\n");
    double **a = matrix_create_random(3, 3, 0, 10);


    double **r = (double**) malloc(3 * sizeof(double*));
    for(uint8_t i = 0; i < 3; i++){
        r[i] = (double*) malloc(3 * sizeof(double));
        for(uint8_t j = 0; j  <3; j++){
            r[i][j] = 0;
        }
    }
    r[2][2] = -1;
    r[1][0] = 1;
    r[0][1] = 1;

    double **b = matrix_mult(r, a, 3, 3, 3, 3);

    printf("a\n");
    matrix_print(a, 3, 3);
    printf("r\n");
    matrix_print(r, 3, 3);
    printf("b\n");
    matrix_print(b, 3, 3);

    double ***rt = optimal_rotation_translation_3D(a, b, 3, 3);
    printf("r obtido\n");
    matrix_print(rt[0], 3, 3);
    printf("t obtido\n");
    matrix_print(rt[1], 3, 1);


    matrix_free(rt[0], 3);
    matrix_free(rt[1], 3);
    free(rt);

    matrix_free(a, 3);
    matrix_free(b, 3);
    matrix_free(r, 3);

}


//p3p_grunert_v2
//K = matriz de calibracao
//rX = vetor de pontos real no formato [p1 p2 p3] em coordenadas homogeneas
//sX = vetor de pontos sensor no formato [s1 s2 s3] em coordenadas homogeneas
double **p3p_grunert_v2(double **K, double **rX, uint32_t **sX){
    printf("p3p_grunert_v2\n");
    if(K == NULL || rX == NULL || sX == NULL){
        return NULL;
    }

    //copia a matriz sX para sx e ficar no formato double
    double **sx = (double**) malloc(3 * sizeof(double*));
    for(uint8_t i = 0; i < 3; i++){
        sx[i] = (double*) malloc(3 * sizeof(double));
        for(uint8_t j = 0; j < 3; j++){
            sx[i][j] = (double) sX[i][j];
        }
    }

    printf("sX\n");
    matrix_print_int(sX, 3, 3);
    printf("rX\n");
    matrix_print(rX, 4, 3);

    printf("K\n");
    matrix_print(K, 3, 3);
    double **K_inv = matrix_inverse(K, 3, 3);
    printf("K_inv\n");
    matrix_print(K_inv, 3, 3);

    double **kx = matrix_mult(K_inv, sx, 3, 3, 3, 3);

    int sign_c;
    if(K[0][0] >= 0){
        sign_c = -1;
    }else{
        sign_c = 1;
    }


    double module[3];
    double **rXi_minus_rXj = (double**) malloc(3 * sizeof(double*));
    for(uint8_t line = 0; line < 3; line++){
        rXi_minus_rXj[line] = (double*) malloc(3 * sizeof(double));
    }
    int8_t rXi_minus_rXj_index = -1;
    //módulo ao quadrado
    double module2_rx_minus[3];
    //normaliza kx
    for(uint8_t column = 0; column < 3; column++){
        module[column] = 0;
        module2_rx_minus[column] = 0;
        for(uint8_t line = 0; line < 3; line++){
            module[column] += pow(kx[line][column], 2);
        }
        module[column] = sqrt(module[column]);
        for(uint8_t line = 0; line < 3; line++){
            if(module[column] != 0){
                kx[line][column] = sign_c * (kx[line][column] / module[column]);
            }
            //para kXi_plus_kXj
            for(uint8_t column2 = 0; column2 < column; column2++){
                rXi_minus_rXj[line][rXi_minus_rXj_index + column2] = rX[line][column] - rX[line][column2];
                module2_rx_minus[rXi_minus_rXj_index + column2] += pow(rXi_minus_rXj[line][rXi_minus_rXj_index + column2], 2);
            }
        }
        rXi_minus_rXj_index++;
    }
    printf("kx\n");
    matrix_print(kx, 3, 3);
    printf("rXi_minus_rXj\n");
    matrix_print(rXi_minus_rXj, 3, 3);
    //kXi_plus_kXj
    //0 - x2 - x1
    //1 - x3 - x1
    //2 - x3 - x2

    printf("module rXi_minus_rXj\n");
    for(uint8_t i = 0; i < 3; i++){
        module2_rx_minus[i] = sqrt(module2_rx_minus[i]);
        printf("%f\n", module2_rx_minus[i]);
        //module[i] = pow(module[i], 2);
    }

    //double a = module2_rx_minus[2];
    //double b = module2_rx_minus[1];
    //double c = module2_rx_minus[0];

    //calcula os angulos alpha, beta e gama
    //double cos_alpha = (module2_kx_plus[2] - pow());

    double **kxi_point_kxj = (double**) malloc(1 * sizeof(double*));
    kxi_point_kxj[0] = (double*) malloc(3 * sizeof(double));
    for(uint8_t i = 0; i < 3; i++){
        kxi_point_kxj[0][i] = 0;
    }
    for(uint8_t column1 = 0; column1 < 2; column1++){
        for(uint8_t column2 = column1 + 1; column2 < 3; column2++){
            uint8_t index = (column1 + 1) * (column2 - 1);
            for(uint8_t line = 0; line < 3; line++){
                kxi_point_kxj[0][index] += kx[line][column1] * kx[line][column2];
            }
        }
    }
    printf("kxi_point_kxj\n");
    matrix_print(kxi_point_kxj, 1, 3);
    //0 - x1x2
    //1 - x1x3
    //2 - x2x3

    //modulo de kxi é 1 porque foi normalizado
    double cos_alpha = kxi_point_kxj[0][2];
    double cos_beta = kxi_point_kxj[0][1];
    double cos_gama = kxi_point_kxj[0][0];
    printf("cos_alpha = %f\tcos_beta = %f\tcos_gama = %f\n", cos_alpha, cos_beta, cos_gama);

    double a = module2_rx_minus[2];
    double b = module2_rx_minus[1];
    double c = module2_rx_minus[0];

    double a2 = pow(a, 2);
    double b2 = pow(b, 2);
    double c2 = pow(c, 2);

    double *p = (double*) malloc(5 * sizeof(double));

    //para auxiliar
    double a2c2b2_m = (a2 - c2) / b2;
    double a2c2b2_p = (a2 + c2) / b2;
    double cos2_a = pow(cos_alpha, 2);
    double cos2_b = pow(cos_beta, 2);
    double cos2_g = pow(cos_gama, 2);

    ////A4 ou C4
    p[0] = pow((a2c2b2_m - 1), 2) - 4 * (c2 / b2) * cos2_a;

    //A3 ou C3
    p[1] = 4 * (a2c2b2_m * (1 - a2c2b2_m) * cos_beta -
                (1 - a2c2b2_p) * cos_alpha * cos_gama +
                2 * (c2 / b2) * cos2_a * cos_beta);

    //A2 ou C2
    p[2] = 2 * (pow(a2c2b2_m, 2) - 1 + 2 * pow(a2c2b2_m, 2) * cos2_b +
                2 * (1 - c2 / b2) * cos2_a -
                4 * a2c2b2_p * cos_alpha * cos_beta * cos_gama +
                2 * (1 - a2 / b2) * cos2_g);

    //A1 ou C1
    p[3] = 4 * ( - a2c2b2_m * (1 + a2c2b2_m) * cos_beta +
                2 * (a2 / b2) * cos2_g * cos_beta -
                (1 - a2c2b2_p) * cos_alpha * cos_gama);

    //A0 ou C0
    p[4] = pow((1 + a2c2b2_m), 2) - 4 * (a2 / b2) * cos2_g;

    print_polinomio(p, 4);

    //double *r = bisection_method(p, 4, 1e-5);
    double **r = global_newton_method(p, 4, 1e-10);
    for(uint8_t i = 0; i < 4; i++){
        if(r[i] == NULL)    continue;
        printf("root %d = %f\n", i, r[i][0]);
    }


    double **solution = (double**) malloc(4 * sizeof(double*));


    //double s1[4];
    //double s2[4];
    //double s3[4];
    for(uint8_t i = 0; i < 4; i++){
        solution[i] = (double*) malloc(3 * sizeof(double));
        if(r[i] == NULL)    goto loop_p3p_grunert_no_solution;
        double aux = b2 / (1 + pow(r[i][0], 2) - 2 * r[i][0] * cos_beta);
        if(aux < 0 || r[i][0] < 0){
loop_p3p_grunert_no_solution:
            free(solution[i]);
            solution[i] = NULL;
            continue;
        }
        ///s1[i] = sqrt(aux);
        solution[i][0] = sqrt(aux);
        //s3[i] = r[i][0] * s1[i];
        solution[i][2] = r[i][0] * solution[i][0];

        //printf("s1 = %f\ns3 = %f\n", s1[i], s3[i]);

        double *polinomio_s2 = (double*) malloc(3 * sizeof(double));
        polinomio_s2[0] = 1;
        //polinomio_s2[1] = -2 * cos_alpha * s3[i];
        polinomio_s2[1] = -2 * cos_alpha * solution[i][2];
        //polinomio_s2[2] = pow(s3[i], 2) - a2;
        polinomio_s2[2] = pow(solution[i][2], 2) - a2;

        printf("polinomio_s2\n");
        print_polinomio(polinomio_s2, 2);
        //double *s2_i = bisection_method(polinomio_s2, 2, 1e-5);
        double delta = pow(polinomio_s2[1], 2) - 4 * polinomio_s2[0] * polinomio_s2[2];

        printf("delta = %f\n", delta);
        if(delta < 0){
            goto loop_p3p_grunert_no_solution;
        }
        delta = sqrt(delta);
        //double r1 = (-polinomio_s2[1] + delta) / 2;
        //s2[i] = (-polinomio_s2[1] + delta) / 2;
        solution[i][1] = (-polinomio_s2[1] + delta) / 2;
        //printf("s2 = %f\n", s2[i]);


        //printf("s2_1 = %f\ts2_2 = %f\n", s2_i[0], s2_i[1]);

        //free(s2_i);

        free(polinomio_s2);
        free(r[i]);
    }

    free(r);

    for(uint8_t i = 0; i < 4; i++){
        printf("Solucao %d:", i + 1);
        if(solution[i] == NULL){
            printf("NULL");
        }else{
            for(uint8_t j = 0; j < 3; j++){
                printf("s%d = %f\t", j + 1, solution[i][j]);
            }
        }
        putchar('\n');
    }

    free(p);
    matrix_free(kxi_point_kxj, 1);
    matrix_free(rXi_minus_rXj, 3);
    matrix_free(sx, 3);
    //matrix_free(rx, 4);
    matrix_free(K_inv, 3);
    matrix_free(kx, 3);

    return solution;
}


//descobre a distancia dos pontos para a camera
//
//dio = vetor vertical contendo os valores iniciais de distancia do ponto ate origem do celular
//
//theta = angulo entre os vetores dos pontos
//  matriz simetrica cujos indexes representam os vetores em que o angulo foi medido
//
//dij = matriz simetrica com valores de distancia entre os pontos i e j
//
//thera e dij constantes
double **p4p_dio_gauss_newton(double **dio, double **cos_theta, double **dij){
    printf("entrando p4p_gauss_newton\n");

    if(dio == NULL || cos_theta == NULL || dij == NULL){
        return NULL;
    }

    double **r = matrix_create_double(6, 1);
    double **bn = matrix_copy(dio, 4, 1);
    double **bn1 = matrix_create_double(4, 1);
    double **J = matrix_create_double(6, 4);

    printf("bn\n");
    matrix_print(bn, 4, 1);

    double erro;
    double sum_erro2;
    uint32_t n = 0;

    do{
        //atualiza os valores da funcao
        uint8_t function_index = 0;
        sum_erro2 = 0;
        for(uint8_t i = 0; i < 4; i++){
            for(uint8_t j = i + 1; j < 4; j++){
                r[function_index][0] = pow(bn[i][0], 2) + pow(bn[j][0], 2) - 2 * bn[i][0] * bn[j][0] * cos_theta[i][j] - pow(dij[i][j], 2);
                sum_erro2 += pow(r[function_index][0], 2);

                //calcula o jacobiano
                for(uint8_t column = 0; column < 4; column++){
                    if(column != i && column != j){
                        J[function_index][column] = 0;
                    }else{

                        uint8_t index;
                        if(column == i){
                            index = j;
                        }else{
                            index = i;
                        }
                        //printf("function_index = %d\tcolumn = %d\ti = %d\tj = %d\tindex = %d\n", function_index, column, i, j, index);
                        J[function_index][column] = 2 * (bn[column][0] - bn[index][0] * cos_theta[i][j]);
                    }
                }

                function_index++;
            }
        }
        //printf("r\n");
        //matrix_print(r, 6, 1);

        //printf("J\n");
        //matrix_print(J, 6, 4);

        double **JT = matrix_transpose(J, 6, 4);
        double **JT_J = matrix_mult(JT, J, 4, 6, 6, 4);
        double **JT_J_inv = matrix_inverse(JT_J, 4, 4);
        double **JT_J_inv_JT = matrix_mult(JT_J_inv, JT, 4, 4, 4, 6);
        double **JT_J_inv_JT_r = matrix_mult(JT_J_inv_JT, r, 4, 6, 6, 1);

        //atualiza o bn1
        //double erro = 0;
        erro = 0;
        for(uint8_t i = 0; i < 4; i++){
            bn1[i][0] = bn[i][0] - JT_J_inv_JT_r[i][0];
            bn[i][0] = bn1[i][0];
            erro += pow(JT_J_inv_JT_r[i][0], 2);
        }
        erro = sqrt(erro);
        //printf("bn1\n");
        //matrix_print(bn1, 4, 1);
        printf("n = %d\terro = %f\tsum_erro^2 = %f\n", ++n, erro, sum_erro2);



        matrix_free(JT, 4);
        matrix_free(JT_J, 4);
        matrix_free(JT_J_inv, 4);
        matrix_free(JT_J_inv_JT, 4);
        matrix_free(JT_J_inv_JT_r, 4);

    }while(erro > 10e-10);
    matrix_free(bn, 4);
    //matrix_free(bn1, 4);
    //bn1 = NULL;
    matrix_free(J, 6);
    matrix_free(r, 6);

    printf("bn1\n");
    matrix_print(bn1, 4, 1);
    printf("saindo p4p_gauss_newton\n");
    return bn1;
}

//Xoi = iniciais do valor da posicao
//rX = posicao dos pontos no mundo real
//dio = distancia ate os pontos do mundo real
double **p4p_Xo_gauss_newton(double **Xoi, double **rX, double **dio){
    if(rX == NULL || dio == NULL){
        return NULL;
    }

    double **Xon = matrix_copy(Xoi, 3, 1);
    double **Xon1 = matrix_create_double(3, 1);
    double **J = matrix_create_double(4, 3);
    double **r = matrix_create_double(4, 1);

    double **rX_euclid = matrix_copy(rX, 3, 4);
    for(uint8_t j = 0; j < 4; j++){
        for(uint8_t i = 0; i < 3; i++){
            rX_euclid[i][j] = rX_euclid[i][j] / rX[3][j];
        }
    }

    printf("rX_euclid\n");
    matrix_print(rX_euclid, 3, 4);
    printf("Xoi\n");
    matrix_print(Xon, 3, 1);

    double **dio2 = matrix_create_double(4, 1);
    for(uint8_t i = 0; i < 4; i++){
        dio2[i][0] = pow(dio[i][0], 2);
    }

    double erro;
    double sum_erro2;
    uint32_t n = 0;

    do{
        sum_erro2 = 0;
        for(uint8_t i = 0; i < 4; i++){
            r[i][0] = 0;
            for(uint8_t dim = 0; dim < 3; dim++){
                double x_x1 = Xon[dim][0] - rX_euclid[dim][i];
                r[i][0] += pow(x_x1, 2);
                J[i][dim] = 2 * x_x1;
            }
            r[i][0] = r[i][0] - dio2[i][0];
            sum_erro2 += pow(r[i][0], 2);
        }
        printf("r\n");
        matrix_print(r, 4, 1);
        printf("J\n");
        matrix_print(J, 4, 3);

        double **JT = matrix_transpose(J, 4, 3);
        double **JT_J = matrix_mult(JT, J, 3, 4, 4, 3);
        double **JT_J_inv = matrix_inverse(JT_J, 3, 3);
        double **JT_J_inv_JT = matrix_mult(JT_J_inv, JT, 3, 3, 3, 4);
        double **JT_J_inv_JT_r = matrix_mult(JT_J_inv_JT, r, 3, 4, 4, 1);

        //atualiza o bn1
        //double erro = 0;
        erro = 0;
        for(uint8_t i = 0; i < 3; i++){
            Xon1[i][0] = Xon[i][0] - JT_J_inv_JT_r[i][0];
            Xon[i][0] = Xon1[i][0];
            erro += pow(JT_J_inv_JT_r[i][0], 2);
        }
        erro = sqrt(erro);
        printf("Xon1\n");
        matrix_print(Xon1, 3, 1);
        printf("n = %d\terro = %f\tsum_erro^2 = %f\n", ++n, erro, sum_erro2);

        matrix_free(JT, 3);
        matrix_free(JT_J, 3);
        matrix_free(JT_J_inv, 3);
        matrix_free(JT_J_inv_JT, 3);
        matrix_free(JT_J_inv_JT_r, 3);

    }while(erro > 10e-10);


    matrix_free(rX_euclid, 3);
    matrix_free(r, 4);
    matrix_free(J, 4);
    matrix_free(Xon, 3);
    matrix_free(dio2, 4);

    return Xon1;
}

//usa o marquad da wikipedia
//incompleto
double **p4p_Xo_Levenberg_Marquardt(double **Xoi, double **rX, double **dio){
    printf("p4p_Xo_Levenberg_Marquardt\n");
    printf("incompleto\n");
    if(rX == NULL || dio == NULL){
        return NULL;
    }

    double **Xon = matrix_copy(Xoi, 3, 1);
    double **Xon1 = matrix_create_double(3, 1);
    double **J = matrix_create_double(4, 3);
    double **r = matrix_create_double(4, 1);

    double **rX_euclid = matrix_copy(rX, 3, 4);
    for(uint8_t j = 0; j < 4; j++){
        for(uint8_t i = 0; i < 3; i++){
            rX_euclid[i][j] = rX_euclid[i][j] / rX[3][j];
        }
    }

    printf("rX_euclid\n");
    matrix_print(rX_euclid, 3, 4);
    printf("Xoi\n");
    matrix_print(Xon, 3, 1);

    double **dio2 = matrix_create_double(4, 1);
    for(uint8_t i = 0; i < 4; i++){
        dio2[i][0] = pow(dio[i][0], 2);
    }

    double erro;
    double sum_erro2;
    uint32_t n = 0;

    do{
        sum_erro2 = 0;
        for(uint8_t i = 0; i < 4; i++){
            r[i][0] = 0;
            for(uint8_t dim = 0; dim < 3; dim++){
                double x_x1 = Xon[dim][0] - rX_euclid[dim][i];
                r[i][0] += pow(x_x1, 2);
                J[i][dim] = 2 * x_x1;
            }
            r[i][0] = r[i][0] - dio2[i][0];
            sum_erro2 += r[i][0];
        }
        printf("r\n");
        matrix_print(r, 4, 1);
        printf("J\n");
        matrix_print(J, 4, 3);

        double **JT = matrix_transpose(J, 4, 3);
        double **JT_J = matrix_mult(JT, J, 3, 4, 4, 3);
        double **JT_J_inv = matrix_inverse(JT_J, 3, 3);
        double **JT_J_inv_JT = matrix_mult(JT_J_inv, JT, 3, 3, 3, 4);
        double **JT_J_inv_JT_r = matrix_mult(JT_J_inv_JT, r, 3, 4, 4, 1);

        //atualiza o bn1
        //double erro = 0;
        erro = 0;
        for(uint8_t i = 0; i < 3; i++){
            Xon1[i][0] = Xon[i][0] - JT_J_inv_JT_r[i][0];
            Xon[i][0] = Xon1[i][0];
            erro += pow(JT_J_inv_JT_r[i][0], 2);
        }
        erro = sqrt(erro);
        printf("Xon1\n");
        matrix_print(Xon1, 3, 1);
        printf("n = %d\terro = %f\tsum_erro^2 = %f\n", ++n, erro, sum_erro2);

        matrix_free(JT, 3);
        matrix_free(JT_J, 3);
        matrix_free(JT_J_inv, 3);
        matrix_free(JT_J_inv_JT, 3);
        matrix_free(JT_J_inv_JT_r, 3);

    }while(erro > 10e-10);


    matrix_free(rX_euclid, 3);
    matrix_free(r, 4);
    matrix_free(J, 4);
    matrix_free(Xon, 3);
    matrix_free(dio2, 4);

    return Xon1;
}


//todos os pontos com mesmo z
double ***p3p_Xo_direct_planar(double **dio, double **rX){
    printf("p3p_Xo_direct_planar\n");
    if(dio == NULL || rX == NULL){
        return NULL;
    }

    printf("dio\n");
    matrix_print(dio, 3, 1);
    printf("rX\n");
    matrix_print(rX, 3, 3);

    double ***Xo = NULL;



/*
    double **sistema = matrix_create_double(2, 3);

    for(uint8_t line = 0; line < 2; line++){
        sistema[line][2] = 0;
        for(uint8_t column = 0; column < 2; column++){
            sistema[line][column] = rX[column][line] - rX[column][2];
            sistema[line][2] += pow(rX[column][2], 2) - pow(rX[column][line], 2);
        }
        sistema[line][2] += pow(dio[line][0], 2) - pow(dio[2][0], 2);
        sistema[line][2] = sistema[line][2] / 2;
    }
    printf("sistema\n");
    matrix_print(sistema, 2, 3);
    //checar se
    if(sistema[0][0] == 0){
        if(sistema[1][0] == 0){
            goto p3p_Xo_direct_planar_end;
        }
        double *aux = sistema[0];
        sistema[0] = sistema[1];
        sistema[1] = aux;
    }
    double deny = sistema[0][0] * sistema[1][1] - sistema[0][1] * sistema[1][0];
    if(deny == 0){
        goto p3p_Xo_direct_planar_end;
    }
    double numy = sistema[0][0] * sistema[1][2] - sistema[0][2] * sistema[1][0];
    double y = numy / deny;
    double x = (sistema[0][2] - sistema[0][1] * y) / sistema[0][0];
*/
    //Ax = b
    double **A = matrix_create_double(2, 2);
    double **b = matrix_create_double(2, 1);
    for(uint8_t i = 0; i < 2; i++){
        b[i][0] = pow(dio[i][0], 2) - pow(dio[2][0], 2);
        for(uint8_t j = 0; j < 2; j++){
            A[i][j] = 2 * (rX[j][i] - rX[j][2]);
            b[i][0] += pow(rX[j][2], 2) - pow(rX[j][i], 2);
        }
    }

    printf("A\n");
    matrix_print(A, 2, 2);
    printf("b\n");
    matrix_print(b, 2, 1);
    double **A_inv = matrix_inverse(A, 2, 2);
    double **XY = matrix_mult(A_inv, b, 2, 2, 2, 1);
    double x = XY[0][0];
    double y = XY[1][0];
    printf("XY\n");
    matrix_print(XY, 2, 1);
    matrix_free(A_inv, 2);
    matrix_free(XY, 2);

    //eq de z, utilizar o ponto 3
    double a = 1;
    double bb = - 2 * rX[2][2];
    double c = pow(rX[2][2], 2) - pow(dio[2][0], 2) + pow(x - rX[0][2], 2) + pow(y - rX[1][2], 2);

    double delta = pow(bb, 2) - 4 * a * c;
    if(delta < 1){
        printf("unvalid z\n");
        goto p3p_Xo_direct_planar_end;
    }
    delta = sqrt(delta);
    double z[2];
    z[0] = (-bb - delta) / (2 * a);
    z[1] = (-bb + delta) / (2 * a);

    Xo = (double***) malloc(2 * sizeof(double**));
    Xo[0] = matrix_create_double(3, 1);
    Xo[1] = matrix_create_double(3, 1);
    for(uint8_t i = 0; i < 2; i++){
        Xo[i][0][0] = x;
        Xo[i][1][0] = y;
        Xo[i][2][0] = z[i];
        printf("Xo %d\n", i);
        matrix_print(Xo[i], 3, 1);
    }


p3p_Xo_direct_planar_end:

    //matrix_free(sistema, 2);
    matrix_free(A, 2);
    matrix_free(b, 2);

    return Xo;
}

double **p4p_Xo_direct(double **dio, double **rX){
    printf("p4p_Xo_direct\n");
    if(dio == NULL || rX == NULL){
        return NULL;
    }
    double **dio_copy = matrix_copy(dio, 4, 1);
    double **rX_copy = matrix_copy(rX, 4, 4);
    for(uint8_t column = 0; column < 4; column++){
        for(uint8_t dim = 0; dim < 4; dim++){
            rX_copy[dim][column] = rX_copy[dim][column] / rX_copy[3][column];
        }
    }
    double ****Xo;
    Xo = (double ****) malloc(2 * sizeof(double***));
    Xo[0] = p3p_Xo_direct_planar(dio_copy, rX_copy);

    //nao ha necessidade de trocar novamente, entao posso 'perder' esse ponto
    uint8_t ponto = rand() % 3;
    dio_copy[ponto][0] = dio_copy[3][0];
    for(uint8_t i = 0; i < 3; i++){
        rX_copy[i][ponto] = rX_copy[i][3];
    }
    Xo[1] = p3p_Xo_direct_planar(dio_copy, rX_copy);

    for(uint8_t i = 0; i < 2; i++){
        if(Xo[i] == NULL){
            continue;
        }
        for(uint8_t j = 0; j < 2; j++){
            matrix_free(Xo[i][j], 3);
        }
        free(Xo[i]);
    }
    free(Xo);


    return NULL;
}

double ***p4p_grunert_gauss_newton(double **K, double **rX, uint32_t **sX){
    double **solution_1 = p3p_grunert_v2(K, rX, sX);

    //trocar o quarto ponto com qualquer
    //uint8_t ponto = rand() % 3;
    uint8_t ponto;
    //ver qual ponto teve o menor variacao
    double menor_var;
    uint8_t n_sol;
    for(uint8_t i = 0; i < 3; i++){
        double mean = 0;
        n_sol = 0;
        for(uint8_t sol = 0; sol < 4; sol++){
            if(solution_1[sol] == NULL){
                continue;
            }
            mean += solution_1[sol][i];
            n_sol++;
        }
        if(n_sol != 0){
            mean = mean / n_sol;
            double var = 0;
            for(uint8_t sol = 0; sol < 4; sol++){
                if(solution_1[sol] == NULL){
                    continue;
                }
                double aux = solution_1[sol][i] - mean;
                aux = pow(aux, 2);
                var += aux;
            }
            if(i == 0 || var < menor_var){
                ponto = i;
                menor_var = var;
            }
        }

    }

    for(uint8_t line = 0; line < 3; line++){
        double aux = rX[line][ponto];
        rX[line][ponto] = rX[line][3];
        rX[line][3] = aux;

        aux = (double) sX[line][ponto];
        sX[line][ponto] = sX[line][3];
        sX[line][3] = (uint32_t) aux;
    }

    double **solution_2 = p3p_grunert_v2(K, rX, sX);

    //retornando ao estado original
    for(uint8_t line = 0; line < 3; line++){
        double aux = rX[line][ponto];
        rX[line][ponto] = rX[line][3];
        rX[line][3] = aux;

        aux = (double) sX[line][ponto];
        sX[line][ponto] = sX[line][3];
        sX[line][3] = (uint32_t) aux;
    }

    //printando solucao
    for(uint8_t index = 0; index < 2; index++){
        double **vetor;
        if(index == 0){
            printf("solution_1\n");
            vetor = solution_1;
        }else{
            printf("solution_2\n");
            printf("sem ponto %d\n", ponto);
            vetor = solution_2;
        }
        for(uint8_t line = 0; line < 4; line++){
            if(vetor[line] == NULL){
                printf("[NULL]\n");
                continue;
            }
            putchar('[');
            for(uint8_t column = 0; column < 3; column++){
                printf("%f", vetor[line][column]);
                if(column < 3){
                    putchar(',');
                }
            }
            putchar(']');
            putchar('\n');
        }
    }

    double **error_matrix = matrix_create_double(4, 4);
    double menor_erro;
    uint8_t i_n1, i_n2;
    uint8_t iniciado = 0;
    for(uint8_t n1 = 0; n1 < 4; n1++){
        if(solution_1[n1] == NULL){
            continue;
        }
        for(uint8_t n2 = 0; n2 < 4; n2++){
            if(solution_2[n2] == NULL){
                continue;
            }
            error_matrix[n1][n2] = 0;
            double erro_atual = 0;
            for(uint8_t ns = 0; ns < 3; ns++){
                if(ns == ponto){
                    continue;
                }
                double s1ms2 = solution_1[n1][ns] - solution_2[n2][ns];
                //erro_atual += pow(solution_1[n1][ns] - solution_2[n2][ns], 2);
                //error_matrix[n1][n2] += pow(solution_1[n1][ns] - solution_2[n2][ns], 2);
                erro_atual += pow(s1ms2, 2);
                error_matrix[n1][n2] += pow(s1ms2, 2);
            }
            if(iniciado == 0 || (erro_atual < menor_erro)){
                iniciado = 1;
                menor_erro = erro_atual;
                i_n1 = n1;
                i_n2 = n2;
            }
        }
    }
    printf("n1 = %d\tn2 = %d\n", i_n1, i_n2);

    printf("error_matrix\n");
    matrix_print(error_matrix, 4, 4);
    matrix_free(error_matrix, 4);


    double **dio = (double**) malloc(4 * sizeof(double*));
    for(uint8_t i = 0; i < 4; i++){
        dio[i] = (double*) malloc(sizeof(double));
        if(i != ponto && i != 3){
            dio[i][0] = (solution_1[i_n1][i] + solution_2[i_n2][i]) / 2;
        }
    }
    dio[ponto][0] = solution_1[i_n1][ponto];
    dio[3][0] = solution_2[i_n2][ponto];
    printf("dio\n");
    matrix_print(dio, 4, 1);

    //distancia entre os pontos
    double **dij = matrix_create_double(4, 4);
    for(uint8_t i = 0; i < 4; i++){
        dij[i][i] = 0;
        for(uint8_t j = i + 1; j < 4; j++){
            dij[i][j] = 0;
            for(uint8_t dim = 0; dim < 3; dim++){
                dij[i][j] += pow(rX[dim][i] / rX[3][i] - rX[dim][j] / rX[3][j], 2);
            }
            dij[i][j] = sqrt(dij[i][j]);
            dij[j][i] = dij[i][j];
        }
    }
    printf("dij\n");
    matrix_print(dij, 4, 4);

    //calculando cos entre os angulos formados pelos vetores apontando aos pontos
    double **ksx = get_kxs(K, sX, 4);

    printf("ksx\n");
    matrix_print(ksx, 3, 4);

    double **cos_theta = get_cos_matrix_vectos(ksx, 4);
    printf("cos_theta\n");
    matrix_print(cos_theta, 4, 4);

    ///lembrar de tirar isso depois
    //printf("deixando dio como um\n");
    //for(uint8_t i = 0; i < 4; i++){
    //    dio[i][0] = 1;
    //}

    double **dio_final = p4p_dio_gauss_newton(dio, cos_theta, dij);
    //double **dio_final = matrix_copy(dio, 4, 1);
    //double **Xoi = matrix_create_double(3, 1);
    //for(uint8_t i = 0; i < 3; i++){
    //    Xoi[i][0] = 1;
    //}
    //Xoi[0][0] = 0;Xoi[1][0] = -0.3;Xoi[2][0] = 0.9;
    //Xoi[0][0] = 0.3;Xoi[1][0] = 0.3;Xoi[2][0] = 1;

    double **Xoi = get_Xo(dio_final, rX, ksx, 4);

    double **R = get_R(Xoi, dio_final, rX, ksx, 4);
    double *determinante = matrix_determinant(R, 3, 3);
    printf("R\n");
    matrix_print(R, 3, 3);
    printf("determinante = ");
    if(determinante == NULL){
        printf("NULL\n");
    }else{
        printf("%f\n", *determinante);
    }
    //matrix_free(R, 3);
    //Xo nao esta dando um resultado muito bom
    //double **Xo = p4p_Xo_gauss_newton(Xoi, rX, dio_final);

    //double **Xo3 = p4p_Xo_Levenberg_Marquardt(Xoi, rX, dio_final);
    //matrix_free(Xo3, 3);

    //direct vai  muito errado, talvez de como ordem para Xoi
    //double **Xo2 = p4p_Xo_direct(dio, rX);
    //matrix_free(Xo2, 3);

    //descobrindo o sinal de Xoi



    //matrix_free(Xo, 3);
    //matrix_free(Xoi, 3);

    matrix_free(dio_final, 4);

    matrix_free(cos_theta, 4);

    matrix_free(ksx, 3);

    matrix_free(dij, 4);
    matrix_free(dio, 4);

    matrix_free(solution_1, 4);
    matrix_free(solution_2, 4);

    double ***Xo_R = (double***) malloc(2 * sizeof(double**));
    Xo_R[0] = Xoi;
    Xo_R[1] = R;

    return Xo_R;

    //return NULL;
}

double ***p4p_grunert_gauss_newton_v2(double **K, double **rX, uint32_t **sX){
    printf("p4p_grunert_gauss_newton_v2\n");
    double **solution_1 = p3p_grunert_v2(K, rX, sX);

    double ***P = get_projection_matrix(solution_1, K, sX, rX, 3);

    double **rx4 = (double**) malloc(4 * sizeof(double*));
    for(uint8_t i = 0; i < 4; i++){
        rx4[i] = (double*) malloc(sizeof(double));
        rx4[i][0] = rX[i][3];
    }

    double **error = (double**) malloc(4 * sizeof(double*));
    for(uint8_t i = 0; i < 4; i++){
        if(P[i] == NULL){
            error[i] = NULL;
            continue;
        }
        error[i] = (double*) malloc(sizeof(double));
        error[i][0] = 0;

        double **sx4 = matrix_mult(P[i], rx4, 3, 4, 4, 1);
        printf("sx4 i = %d\n", i);
        matrix_print(sx4, 3, 1);
        for(uint8_t dim = 0; dim < 2; dim++){
            double aux = (double) (sX[dim][3] / sX[2][3]);
            aux = aux - (sx4[dim][0] / sx4[2][0]);
            aux = pow(aux, 2);
            printf("aux = %f\n", aux);
            error[i][0] += aux;
            //error[i][0] += pow(((double)sX[dim][3] / (double)sX[2][3]) - (sx4[dim][0] / sx4[2][0]), 2);
        }
        printf("a\n");
        matrix_free(sx4, 3);
    }
    uint8_t index_menor_erro = 0;
    while(error[index_menor_erro] == NULL){
        index_menor_erro++;
        if(index_menor_erro == 4){
            free(P);
            free(error);
            matrix_free(solution_1, 4);
            return NULL;
        }
    }
    for(uint8_t i = index_menor_erro + 1; i < 4; i++){
        if(error[i] != NULL && error[i] < error[index_menor_erro]){
            index_menor_erro = i;
        }
    }

    double **ksx = get_kxs(K, sX, 3);

    double **Xo = (double**) malloc(3 * sizeof(double*));
    for(uint8_t dim = 0; dim < 3; dim++){
        Xo[dim] = (double*) malloc(sizeof(double));
        Xo[dim][0] = 0;
        for(uint8_t i = 0; i < 3; i++){
            Xo[dim][0] += (rX[dim][i] / rX[3][i]) - solution_1[index_menor_erro][i] * ksx[dim][i];
        }
        Xo[dim][0] = Xo[dim][0] / 3;
    }

    double **R = get_R_v2(Xo, solution_1[index_menor_erro], rX, ksx, 3);

    double ***Xo_R = (double***) malloc(2 * sizeof(double**));
    Xo_R[0] = Xo;
    Xo_R[1] = R;

    matrix_free(ksx, 3);
    for(uint8_t i = 0; i < 4; i++){
        matrix_free(P[i], 3);
    }

    free(P);
    matrix_free(error, 4);
    matrix_free(solution_1, 4);

    return Xo_R;
}

void p4p_grunert_test_v2(){

    printf("p4p_grunert_test\n");

    double **K = (double**) malloc(3 * sizeof(double*));
    double **rX = (double**) malloc(4 * sizeof(double*));
    uint32_t **sX = (uint32_t**) malloc(3 * sizeof(uint32_t*));
    for(uint8_t line = 0; line < 4; line++){
        if(line < 3){
            K[line] = (double*) malloc(3 * sizeof(double));
            sX[line] = (uint32_t*) malloc(4 * sizeof(uint32_t));
        }
        rX[line] = (double*) malloc(4 * sizeof(double));
    }


/*
    K[0][0] = 2988.603737;K[0][1] = 40.688782;K[0][2] = 2175.006015;
    K[1][0] = 0;K[1][1] = 2977.833129;K[1][2] = 1344.845743;
    K[2][0] = 0;K[2][1] = 0;K[2][2] = 1;
*/

    K[0][0] = 2997.26561678079;K[0][1] = 0;K[0][2] = 1969.05834609630;
    K[1][0] = 0;K[1][1] = 2995.58260131049;K[1][2] = 1478.29861618836;
    K[2][0] = 0;K[2][1] = 0;K[2][2] = 1;

    //K[0][0] = 3500;
    //K[1][1] = K[0][0];

/*
    K[0][0] = 3000;K[0][1] = 0;K[0][2] = 2000;
    K[1][0] = 0;K[1][1] = 3000;K[1][2] = 1500;
    K[2][0] = 0;K[2][1] = 0;K[2][2] = 1;
*/
//P1
//z[0][0] = 0;z[1][0] = -0.3;z[2][0] = 0.9;
/*
    //4
    sX[0][0] = 1834;sX[1][0] = 1105;sX[2][0] = 1;
    //5
    sX[0][1] = 1596;sX[1][1] = 2143;sX[2][1] = 1;
    //6
    sX[0][2] = 1036;sX[1][2] = 1960;sX[2][2] = 1;
    //7
    sX[0][3] = 1031;sX[1][3] = 1295;sX[2][3] = 1;

    rX[0][0] = 0.227;rX[1][0] = -0.015;rX[2][0] = 0.15;rX[3][0] = 1;
    //5
    rX[0][1] = 0.237;rX[1][1] = 0.315;rX[2][1] = 0.15;rX[3][1] = 1;
    //6
    rX[0][2] = 0.459;rX[1][2] = 0.328;rX[2][2] = 0.15;rX[3][2] = 1;
    //7
    rX[0][3] = 0.507;rX[1][3] = 0.11;rX[2][3] = 0.15;rX[3][3] = 1;
*/

/*
    sX[0][0] = 1103;sX[1][0] = 1181;sX[2][0] = 1;
    //5
    sX[0][1] = 1444;sX[1][1] = 1894;sX[2][1] = 1;
    //6
    sX[0][2] = 2012;sX[1][2] = 1937;sX[2][2] = 1;
    //7
    sX[0][3] = 1651;sX[1][3] = 1031;sX[2][3] = 1;

    rX[0][0] = 0;rX[1][0] = 0.5;rX[2][0] = 0.01;rX[3][0] = 1;
    //5
    rX[0][1] = 0;rX[1][1] = 0;rX[2][1] = 0.01;rX[3][1] = 1;
    //6
    rX[0][2] = 0.5;rX[1][2] = 0;rX[2][2] = 0.01;rX[3][2] = 1;
    //7
    rX[0][3] = 0.5;rX[1][3] = 0.5;rX[2][3] = 0.01;rX[3][3] = 1;
*/
 //aproximadamente 0.5 em y e 1 em z
 //0.3, 0.4, 1.6
    sX[0][0] = 1777;sX[1][0] = 1447;sX[2][0] = 1;
    //5
    sX[0][1] = 2010;sX[1][1] = 2199;sX[2][1] = 1;
    //6
    sX[0][2] = 2631;sX[1][2] = 2291;sX[2][2] = 1;
    //7
    sX[0][3] = 2351;sX[1][3] = 1286;sX[2][3] = 1;

    rX[0][0] = 0;rX[1][0] = 0.5;rX[2][0] = 0.01;rX[3][0] = 1;
    //5
    rX[0][1] = 0;rX[1][1] = 0;rX[2][1] = 0.01;rX[3][1] = 1;
    //6
    rX[0][2] = 0.5;rX[1][2] = 0;rX[2][2] = 0.01;rX[3][2] = 1;
    //7
    rX[0][3] = 0.5;rX[1][3] = 0.5;rX[2][3] = 0.01;rX[3][3] = 1;

//[0, 0.3, 1.25]


/*
    double **Xo = matrix_create_double(3, 1);
    Xo[0][0] = 0;
    Xo[1][0] = 0.3;
    Xo[2][0] = 1.25;
    //sX[0][0] = 952;sX[1][0] = 861;sX[2][0] = 1;
    sX[0][0] = 3434;sX[1][0] = 1420;sX[2][0] = 1;
    //5
    sX[0][1] = 2275;sX[1][1] = 730;sX[2][1] = 1;
    //6
    sX[0][2] = 1689;sX[1][2] = 1758;sX[2][2] = 1;
    //7
    sX[0][3] = 2679;sX[1][3] = 2470;sX[2][3] = 1;

    //rX[0][0] = 0.3;rX[1][0] = -0.4;rX[2][0] = 0.155;rX[3][0] = 1;
    rX[0][0] = 0;rX[1][0] = 0.5;rX[2][0] = 0;rX[3][0] = 1;
    //5
    rX[0][1] = 0;rX[1][1] = 0;rX[2][1] = 0;rX[3][1] = 1;
    //6
    rX[0][2] = 0.5;rX[1][2] = 0;rX[2][2] = 0;rX[3][2] = 1;
    //7
    rX[0][3] = 0.5;rX[1][3] = 0.5;rX[2][3] = 0;rX[3][3] = 1;
    calibrateCamerav2(Xo, sX, rX);
    matrix_free(Xo, 3);
*/

/*
    //sX[0][0] = 952;sX[1][0] = 861;sX[2][0] = 1;
    sX[0][0] = 952;sX[1][0] = 861;sX[2][0] = 1;
    //5
    sX[0][1] = 771;sX[1][1] = 1283;sX[2][1] = 1;
    //6
    sX[0][2] = 593;sX[1][2] = 625;sX[2][2] = 1;
    //7
    sX[0][3] = 429;sX[1][3] = 1057;sX[2][3] = 1;

    //rX[0][0] = 0.3;rX[1][0] = -0.4;rX[2][0] = 0.155;rX[3][0] = 1;
    rX[0][0] = 0.3;rX[1][0] = -0.4;rX[2][0] = 0.155;rX[3][0] = 1;
    //5
    rX[0][1] = 0.5;rX[1][1] = -0.4;rX[2][1] = 0.155;rX[3][1] = 1;
    //6
    rX[0][2] = 0.3;rX[1][2] = -0.6;rX[2][2] = 0.155;rX[3][2] = 1;
    //7
    rX[0][3] = 0.5;rX[1][3] = -0.6;rX[2][3] = 0.155;rX[3][3] = 1;
*/
/*
    //(0.5, 0, mais ou menos 1 metro de altura acho sla)
    sX[0][0] = 2399;sX[1][0] = 1257;sX[2][0] = 1;
    //5
    sX[0][1] = 2654;sX[1][1] = 1851;sX[2][1] = 1;
    //6
    sX[0][2] = 1944;sX[1][2] = 1503;sX[2][2] = 1;
    //7
    sX[0][3] = 2156;sX[1][3] = 2060;sX[2][3] = 1;

    //rX[0][0] = 0.3;rX[1][0] = -0.4;rX[2][0] = 0.155;rX[3][0] = 1;
    rX[0][0] = 0.3;rX[1][0] = -0.4;rX[2][0] = 0.16;rX[3][0] = 1;
    //5
    rX[0][1] = 0.5;rX[1][1] = -0.4;rX[2][1] = 0.16;rX[3][1] = 1;
    //6
    rX[0][2] = 0.3;rX[1][2] = -0.6;rX[2][2] = 0.16;rX[3][2] = 1;
    //7
    rX[0][3] = 0.5;rX[1][3] = -0.6;rX[2][3] = 0.16;rX[3][3] = 1;
*/
/*
//0.5, -0.6, z desconhecido
    sX[0][0] = 1685;sX[1][0] = 615;sX[2][0] = 1;
    //5
    sX[0][1] = 2317;sX[1][1] = 1372;sX[2][1] = 1;
    //6
    sX[0][2] = 955;sX[1][2] = 1253;sX[2][2] = 1;
    //7
    sX[0][3] = 1587;sX[1][3] = 2021;sX[2][3] = 1;

    //rX[0][0] = 0.3;rX[1][0] = -0.4;rX[2][0] = 0.155;rX[3][0] = 1;
    rX[0][0] = 0.3;rX[1][0] = -0.4;rX[2][0] = 0.16;rX[3][0] = 1;
    //5
    rX[0][1] = 0.5;rX[1][1] = -0.4;rX[2][1] = 0.16;rX[3][1] = 1;
    //6
    rX[0][2] = 0.3;rX[1][2] = -0.6;rX[2][2] = 0.16;rX[3][2] = 1;
    //7
    rX[0][3] = 0.5;rX[1][3] = -0.6;rX[2][3] = 0.16;rX[3][3] = 1;
    */

/*
    sX[0][0] = 1868;sX[1][0] = 653;sX[2][0] = 1;
    //5
    sX[0][1] = 1146;sX[1][1] = 1367;sX[2][1] = 1;
    //6
    sX[0][2] = 1760;sX[1][2] = 2176;sX[2][2] = 1;
    //7
    sX[0][3] = 2587;sX[1][3] = 1467;sX[2][3] = 1;
    rX[0][0] = 0;rX[1][0] = 0.5;rX[2][0] = 0;rX[3][0] = 1;
    //5
    rX[0][1] = 0;rX[1][1] = 0;rX[2][1] = 0;rX[3][1] = 1;
    //6
    rX[0][2] = 0.5;rX[1][2] = 0;rX[2][2] = 0;rX[3][2] = 1;
    //7
    rX[0][3] = 0.5;rX[1][3] = 0.5;rX[2][3] = 0;rX[3][3] = 1;
*/

printf("sX ant\n");
matrix_print_int(sX, 3, 4);
    for(uint8_t i = 0; i < 2; i++){
        for(uint8_t j = 0; j < 4; j++){
            //rX[i][j] = 100 * rX[i][j];
            if(i == 0){
                //uint16_t aux = sX[i][j];
                //sX[i][j] = sX[1][j];
                //sX[1][j] = aux;
            }
        }
    }
/*
    for(uint8_t j = 0; j < 4; j++){
        sX[1][j] = 4000 - sX[0][j];
        sX[0][j] = 3000 - sX[1][j];
    }
*/
printf("sX dep\n");
matrix_print_int(sX, 3, 4);
/*
    sX[0][0] = 1868;sX[1][0] = 653;sX[2][0] = 1;
    //5
    sX[0][1] = 1146;sX[1][1] = 1367;sX[2][1] = 1;
    //6
    sX[0][2] = 1760;sX[1][2] = 2176;sX[2][2] = 1;
    //7
    sX[0][3] = 2587;sX[1][3] = 1467;sX[2][3] = 1;
*/
    printf("vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv\n1111111111111111111111111111111111111111111111111111\n\n\n");

    double **Xo_R1 = p4p_grunert_gauss_newton(K, rX, sX);
    printf("Xo\n");
    matrix_print(Xo_R1[0], 3, 1);
    printf("R\n");
    matrix_print(Xo_R1[1], 3, 3);

    matrix_free(Xo_R1[0], 3);
    matrix_free(Xo_R1[1], 3);
    free(Xo_R1);


    printf("vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv\n22222222222222222222222222222222222222222222222222222222222\n\n\n");
    double **Xo_R = p4p_grunert_gauss_newton_v2(K, rX, sX);

    printf("Xo\n");
    matrix_print(Xo_R[0], 3, 1);
    printf("R\n");
    matrix_print(Xo_R[1], 3, 3);

    matrix_free(Xo_R[0], 3);
    matrix_free(Xo_R[1], 3);
    free(Xo_R);
    //matrix_print(K, 3, 3);
    //matrix_print(rX, 4, 4);
    //matrix_print_int(sX, 3, 4);
    matrix_free(K, 3);
    matrix_free(rX, 4);
    matrix_free(sX, 3);


    return;
}

double **get_kxs(double **K, uint32_t **sX, uint8_t n_pontos){
    if(K == NULL || sX == NULL || n_pontos == 0){
        return NULL;
    }

    double **K_inv = matrix_inverse(K, 3, 3);
    double **sx = matrix_uint32_t_to_double(sX, 3, n_pontos);

    double **ksx = matrix_mult(K_inv, sx, 3, 3, 3, n_pontos);

    double sign;
    if(K[0][0] > 0){
        sign = -1;
    }else{
        sign = 1;
    }

    //printf("ksx_int\n");
    //matrix_print(ksx, 3, n_pontos);

    for(uint8_t i = 0; i < n_pontos; i++){
        //por algum motivo nao funciona assim
        //double module = module_of_vector_matrix(ksx, 3, i);
        double module = 0;
        for(uint8_t dim = 0; dim < 3; dim++){
            module += pow(ksx[dim][i], 2);
        }
        module = sqrt(module);
        //printf("module %f\n", module);
        for(uint8_t line = 0; line < 3; line++){
            ksx[line][i] = sign * ksx[line][i] / module;
        }
    }

    matrix_free(K_inv, 3);
    matrix_free(sx, 3);

    return ksx;
}

//retorna o cosseno do angulo entre os vetores
//indice i e j da matriz reotrno representa os vetores de coluna da matrix orizinal
double **get_cos_matrix_vectos(double **matrix, uint8_t n_pontos){
    if(matrix == 0 || n_pontos == 0){
        return NULL;
    }

    double **cos_theta = matrix_create_double(n_pontos, n_pontos);
    for(uint8_t i = 0; i < n_pontos; i++){
        cos_theta[i][i] = 1;
        for(uint8_t j = i + 1; j < n_pontos; j++){
            cos_theta[i][j] = 0;

            double module_i = 0;
            double module_j = 0;
            for(uint8_t dim = 0; dim < 3; dim++){
                module_i += pow(matrix[dim][i], 2);
                module_j += pow(matrix[dim][j], 2);
                cos_theta[i][j] += matrix[dim][i] * matrix[dim][j];
            }
            module_i = sqrt(module_i);
            module_j = sqrt(module_j);
            cos_theta[i][j] = cos_theta[i][j] / (module_i * module_j);

            cos_theta[j][i] = cos_theta[i][j];
        }
    }
    return cos_theta;
}


void p4p_grunert_test_v2_ideal(){

    printf("p4p_grunert_test_v2_ideal\n");

    double **K = matrix_create_double(3, 3);
    double **rX = matrix_create_double(4, 4);







    K[0][0] = 3000;K[0][1] = 0;K[0][2] = 2000;
    K[1][0] = 0;K[1][1] = 3000;K[1][2] = 1500;
    K[2][0] = 0;K[2][1] = 0;K[2][2] = 1;

    //double **Xo = matrix_create_double(3, 1);
    //Xo[0][0] = d;Xo[1][0] = d;Xo[2][0] = 1;
    double **Xo = matrix_create_random(3, 1, 0, 5);
    if(Xo[2][0] < 0){
        Xo[2][0] = -Xo[2][0];
    }
    //Xo[2][0] = 1.5;
    //Xo[0][0] = 0.187686;Xo[1][0] = 2.712291;Xo[2][0] = 18.231479;

/*
    //p3
    Xo[0][0] = 0.5;Xo[1][0] = 0.5;Xo[2][0] = 1.5;
    //p1
    Xo[0][0] = 0.5;Xo[1][0] = 1;Xo[2][0] = 1;
    //p2
    Xo[0][0] = 0;Xo[1][0] = 1;Xo[2][0] = 1;
    //p4
    Xo[0][0] = 0.5;Xo[1][0] = 0.6;Xo[2][0] = 1.165;
    //p5
    Xo[0][0] = 0;Xo[1][0] = 0.3;Xo[2][0] = 1.2;
*/
    //esse ponto aqui da problema em R
    //Xo[0][0] = 2.363582;Xo[1][0] = 0.230629;Xo[2][0] = 2.959823;


    //agora por causa da rotacao, se eu deixar Xo com negativo
    //vai dar sX negativo tambem e dar erro


    double **R = matrix_identity(3);
    R[0][0] = 0;R[1][1] = 0;R[2][2] = 0;
    //R[0][1] = 1;R[1][0] = 1;R[2][2] = -1;
    R[1][0] = 1;R[2][1] = 1;R[0][2] = 1;

    R[0][0] = 0.5;     R[0][1] = -0.1464;  R[0][2] = 0.8536;
    R[1][0] = 0.5;     R[1][1] =  0.8536;  R[1][2] = -0.1464;
    R[2][0] = -0.7071; R[2][1] =  0.5;     R[2][2] = 0.5;


    R[0][0] = 0.3536;  R[0][1] = -0.5732; R[0][2] = 0.7392;
R[1][0] = 0.6124;  R[1][1] =  0.7392; R[1][2] = 0.2803;
R[2][0] = -0.7071; R[2][1] =  0.3536; R[2][2] = 0.6124;


R[0][0] = -0.1268;  R[0][1] = -0.9268;  R[0][2] =  0.3536;
R[1][0] =  0.7803;  R[1][1] =  0.1268;  R[1][2] =  0.6124;
R[2][0] = -0.6124;  R[2][1] =  0.3536;  R[2][2] =  0.7071;


    double d = 0.3;
    double dy = 1 * d;

    rX[0][0] = 0;rX[1][0] = 0;rX[2][0] = 0;rX[3][0] = 1;
    //5
    rX[0][1] = d;rX[1][1] = 0;rX[2][1] = 0;rX[3][1] = 1;
    //6
    rX[0][2] = 0;rX[1][2] = dy;rX[2][2] = 0;rX[3][2] = 1;
    //7
    rX[0][3] = d;rX[1][3] = dy;rX[2][3] = 0;rX[3][3] = 1;

    double **P = projection_matrix(K, R, Xo);

    double **sX = matrix_mult(P, rX, 3, 4, 4, 4);
    //normaliza sX
    for(uint8_t i = 0; i < 4; i++){
        for(uint8_t dim = 0; dim < 3; dim++){
            sX[dim][i] = sX[dim][i] / sX[2][i];
        }
    }
    printf("sX\n");
    matrix_print(sX, 3, 4);
    uint32_t max_erro_sx = 26;
    //transformar para int
    uint32_t **sX_int = (uint32_t**) malloc(3 * sizeof(uint32_t*));
    for(uint8_t i = 0; i < 3; i++){
        sX_int[i] = (uint32_t*) malloc(4 * sizeof(uint32_t));
        for(uint8_t j = 0; j < 4; j++){
            sX_int[i][j] = (uint32_t) sX[i][j];

            //erro
            //if(i != 2){
            if(i == 1){//erro apenas em y, considerando linhas do rolling shutter
                uint32_t aux = rand()%max_erro_sx;
                aux = max_erro_sx -1;
                if(rand()%2){
                    sX_int[i][j] += aux;
                }else{
                    if(aux > sX_int[i][j]){
                        sX_int[i][j] = 0;
                    }else{
                        sX_int[i][j] -= aux;
                    }
                    //sX_int[i][j] -= rand()%100;
                    //if(sX_int[i][j])
                }
                //sX_int[i][j] += rand()%100;
            }
        }
    }

    printf("erro sX\n");
    double** esx = matrix_create_double(3, 4);
    for(uint8_t i = 0; i < 3; i++){
        for(uint8_t j = 0; j < 4; j++){
            esx[i][j] = sX[i][j] - sX_int[i][j];
            //if(esx[i][j] < 0){
            //    esx[i][j] = -esx[i][j];
           // }
        }
    }
    matrix_print(esx, 3, 4);
    matrix_free(esx, 3);

    printf("K\n");
    matrix_print(K, 3, 3);
    printf("Xo\n");
    matrix_print(Xo, 3, 1);
    printf("R\n");
    matrix_print(R, 3, 3);
    printf("rX\n");
    matrix_print(rX, 4, 4);
    printf("P\n");
    matrix_print(P, 3, 4);
    printf("sX\n");
    //matrix_print(sX, 3, 4);
    matrix_print_int(sX_int, 3, 4);

    //double ***Xo_R = p4p_grunert_gauss_newton(K, rX, sX_int);
    double ***Xo_R = p4p_grunert_gauss_newton_v2(K, rX, sX_int);

    printf("Xo obtido\n");
    matrix_print(Xo_R[0], 3, 1);
    printf("Xo real\n");
    matrix_print(Xo, 3, 1);
    double erro = 0;
    for(uint8_t i = 0; i < 3; i++){
        erro += pow(Xo_R[0][i][0] - Xo[i][0], 2);
    }
    erro = sqrt(erro);
    printf("erro = %f\n", erro);

    matrix_free(Xo_R[0], 3);
    matrix_free(Xo_R[1], 3);
    free(Xo_R);


    //matrix_print(K, 3, 3);
    //matrix_print(rX, 4, 4);
    //matrix_print_int(sX, 3, 4);
    matrix_free(K, 3);
    matrix_free(rX, 4);
    matrix_free(sX, 3);
    matrix_free(Xo, 3);
    matrix_free(R, 3);
    matrix_free(P, 3);
    for(uint8_t i = 0; i < 3; i++){
        free(sX_int[i]);
    }
    free(sX_int);

    return;
}

double **get_Xo(double **dio, double **rX, double **KsX, uint8_t n_pontos){
    printf("get_Xo\n");
    if(dio == NULL || rX == NULL || KsX == NULL || n_pontos == 0){
        return NULL;
    }
    double **Xo = matrix_create_double(3, 1);
    double **Xon = matrix_create_double(3, n_pontos);

    for(uint8_t dim = 0; dim < 3; dim++){
        Xo[dim][0] = 0;
        for(uint8_t i = 0; i < n_pontos; i++){
            Xon[dim][i] = rX[dim][i] - KsX[dim][i] * dio[i][0];
            Xo[dim][0] += rX[dim][i] - KsX[dim][i] * dio[i][0];
        }
        Xo[dim][0] = Xo[dim][0] / n_pontos;
    }

    printf("Xon\n");
    matrix_print(Xon, 3, n_pontos);

    printf("Xo\n");
    matrix_print(Xo, 3, 1);

    matrix_free(Xon, 3);
    return Xo;
}

double **get_R(double **Xo, double **dio, double **rX, double **KsX, uint8_t n_pontos){
    //printf("get_R\n");
    if(dio == NULL || rX == NULL || KsX == NULL || n_pontos < 3){
        return NULL;
    }

    double **rtx = matrix_create_double(3, n_pontos);
    double **ksx = matrix_create_double(3, n_pontos);

    //rtx tem que transladar ainda
    //ksx tem que escalar
    for(uint8_t i = 0; i < n_pontos; i++){
        for(uint8_t dim = 0; dim < 3; dim++){
            rtx[dim][i] = (rX[dim][i] / rX[3][i]) - Xo[dim][0];
            ksx[dim][i] = KsX[dim][i] * dio[i][0];
        }
    }

    double **rtxT = matrix_transpose(rtx, 3, n_pontos);
    double **rtx_rtxT = matrix_mult(rtx, rtxT, 3, n_pontos, n_pontos, 3);
    double **rtx_rtxT_inv = matrix_inverse(rtx_rtxT, 3, 3);

    double **ksx_rtxT = matrix_mult(ksx, rtxT, 3, n_pontos, n_pontos, 3);
    double **R = matrix_mult(ksx_rtxT, rtx_rtxT_inv, 3, 3, 3, 3);

    for(uint8_t i = 0; i < 3; i++){
        double module = 0;
        for(uint8_t dim = 0; dim < 3; dim++){
            module += pow(R[dim][i], 2);
        }
        module = sqrt(module);
        if(module != 0){
            for(uint8_t dim = 0; dim < 3; dim++){
                R[dim][i] = R[dim][i] / module;
            }
        }
    }

    matrix_free(rtxT, n_pontos);
    matrix_free(rtx_rtxT, 3);
    matrix_free(rtx_rtxT_inv, 3);
    matrix_free(ksx_rtxT, 3);
    matrix_free(rtx, 3);
    matrix_free(ksx, 3);

    return R;
}

double **calibrateCamerav2(double **Xo, uint32_t **sX, double **rX){
    printf("calibrateCamerav2\n");
    if(Xo == NULL || sX == NULL || rX == NULL){
        return NULL;
    }

    double **vectors = matrix_create_double(3, 4);

    for(uint8_t i = 0; i < 4; i++){
        double module = 0;
        for(uint8_t dim = 0; dim < 3; dim++){
            vectors[dim][i] = Xo[dim][0] - (rX[dim][i] / rX[3][i]);
            module += pow(vectors[dim][i], 2);
        }
        module = sqrt(module);

        for(uint8_t dim = 0; dim < 3; dim++){
            vectors[dim][i] = vectors[dim][i] / module;
        }

    }


    printf("Xo\n");
    matrix_print(Xo, 3, 1);
    printf("rX\n");
    matrix_print(rX, 4, 4);
    printf("vectors\n");
    matrix_print(vectors, 3, 4);

    double **A = matrix_create_double(4, 4);
    for(uint8_t i = 0; i < 4; i++){
        for(uint8_t j = 0; j < 4; j++){
            A[i][j] = 0;
        }
    }
    A[0][0] = sX[0][2] / sX[2][2];
    A[0][1] = 1;
    A[1][2] = sX[1][2] / sX[2][2];
    A[1][3] = 1;

    A[2][0] = sX[0][3] / sX[2][3];
    A[2][1] = 1;
    A[3][2] = sX[1][3] / sX[2][3];
    A[3][3] = 1;

    double **v = matrix_create_double(4, 1);
    v[0][0] = vectors[0][2] / vectors[2][2];
    v[1][0] = vectors[1][2] / vectors[2][2];

    v[2][0] = vectors[0][3] / vectors[2][3];
    v[3][0] = vectors[1][3] / vectors[2][3];


    double **A_inv = matrix_inverse(A, 4, 4);

    double **sol = matrix_mult(A_inv, v, 4, 4, 4, 1);

    printf("A\n");
    matrix_print(A, 4, 4);
    printf("v\n");
    matrix_print(v, 4, 1);
    printf("sol\n");
    matrix_print(sol, 4, 1);

    sol[0][0] = sol[2][0];

    double **K_inv = matrix_create_double(3, 3);
    for(uint8_t i = 0; i < 3; i++){
        for(uint8_t j = 0; j < 3; j++){
            K_inv[i][j] = 0;
        }
    }

    K_inv[0][0] = sol[0][0];
    K_inv[0][2] = sol[1][0];
    K_inv[1][1] = sol[2][0];
    K_inv[1][2] = sol[3][0];
    K_inv[2][2] = 1;

    printf("K_inv\n");
    matrix_print(K_inv, 3, 3);

    double **K = matrix_inverse(K_inv, 3, 3);
    printf("K\n");
    matrix_print(K, 3, 3);

    matrix_free(K, 3);

    matrix_free(K_inv, 3);



    matrix_free(A_inv, 4);
    matrix_free(sol, 4);

    matrix_free(v, 4);

    matrix_free(A, 4);

    matrix_free(vectors, 3);


    return NULL;
}

double ***get_projection_matrix(double **solutions, double **K, double **sX, double **rX, uint8_t n_pontos){
    printf("get_projection_matrix\n");
    if(solutions == NULL || K == NULL || sX == NULL || rX == NULL || n_pontos != 3){
        return NULL;
    }
    double **ksx = get_kxs(K, sX, 3);

    double ***P = (double***) malloc(4 * sizeof(double**));

    for(uint8_t i = 0; i < 4; i++){
            printf("i = %d\n", i);
        if(solutions[i] == NULL){
            P[i] = NULL;
            continue;
        }
        double **Xo = matrix_create_double(3, 1);
        for(uint8_t dim = 0; dim < 3; dim++){
            Xo[dim][0] = 0;
            for(uint8_t n = 0; n < n_pontos; n++){
                Xo[dim][0] += (rX[dim][n] / rX[3][n]) - solutions[i][n] * ksx[dim][n];
            }
            Xo[dim][0] = Xo[dim][0] / n_pontos;
        }
        double **R = get_R_v2(Xo, solutions[i], rX, ksx, 3);

        printf("R\n");
        matrix_print(R, 3, 3);

        double **I3Xo = (double**) malloc(3 * sizeof(double*));
        for(uint8_t line = 0; line < 3; line++){
            I3Xo[line] = (double*) malloc(4 * sizeof(double));
            for(uint8_t column = 0; column < 3; column++){
                I3Xo[line][column] = line == column;
            }
            I3Xo[line][3] = -Xo[line][0];
        }

        double **RI3Xo = matrix_mult(R, I3Xo, 3, 3, 3, 4);

        P[i] = matrix_mult(K, RI3Xo, 3, 3, 3, 4);

        printf("Projection Matrix %d\n", i);
        matrix_print(P[i], 3, 4);

        matrix_free(RI3Xo, 3);
        matrix_free(I3Xo, 3);
        matrix_free(Xo, 3);
        matrix_free(R, 3);
    }

    return P;
 }


 double **get_R_v2(double **Xo, double *solution, double **rX, double **KsX, uint8_t n_pontos){
    if(Xo == NULL || solution == NULL || rX == NULL || KsX == NULL || n_pontos != 3){
        return NULL;
    }


    //rtx = rx transladado
    double **rtx = matrix_create_double(3, n_pontos);

    //pontos na coordenada da camera
    double **ksx = matrix_create_double(3, n_pontos);

    //rtx tem que transladar ainda
    //ksx tem que escalar
    for(uint8_t i = 0; i < n_pontos; i++){
        for(uint8_t dim = 0; dim < 3; dim++){
            rtx[dim][i] = (rX[dim][i] / rX[3][i]) - Xo[dim][0];
            ksx[dim][i] = KsX[dim][i] * solution[i];
        }
    }
    double **rtx_inv = matrix_inverse(rtx, 3, 3);
    double **R = matrix_mult(ksx, rtx_inv, 3, 3, 3, 3);

    matrix_free(rtx, 3);
    matrix_free(ksx, 3);
    matrix_free(rtx_inv, 3);


    //checnado inconsistencias em R
    uint8_t vetor_nulo = 0;


    //modulo
    for(uint8_t i = 0; i < 3; i++){
        double module = 0;
        for(uint8_t dim = 0; dim < 3; dim++){
            module += pow(R[dim][i], 2);
        }
        module = sqrt(module);
        if(module == 0){
            vetor_nulo = vetor_nulo | (1 << i);
        }else{
            for(uint8_t dim = 0; dim < 3; dim++){
                R[dim][i] = R[dim][i] / module;
            }
        }
    }

    //checa vetores nulos
    if(vetor_nulo){
        uint8_t n = 0;
        uint8_t index = 0;
        for(uint8_t i = 0; i < 3; i++){
            if(vetor_nulo & (1 << i)){
                n++;
                index = i;
            }
        }
        //if(vetor_nulo == 0b00000111 || vetor_nulo == 0b00000110 ||
        //   vetor_nulo == 0b00000101 || vetor_nulo == 0b00000011){
        if(n > 1){
            matrix_free(R, 3);
            return NULL;
        }else{
            uint8_t index1 = 0;
            uint8_t index2 = 0;
            switch(vetor_nulo){
            case 1:
                index1 = 1;
                index2 = 2;
                break;
            case 2:
                index1 = 2;
                index2 = 0;
                break;
            case 4:
                index1 = 0;
                index2 = 1;
                break;
            default:
                break;
            }
            R[0][index] = R[1][index1] * R[2][index2] - R[2][index1] * R[1][index2];
            R[1][index] = R[2][index1] * R[0][index2] - R[0][index1] * R[2][index2];
            R[2][index] = R[0][index1] * R[1][index2] - R[1][index1] * R[0][index2];
        }
    }
/*
    double ***svd = svd_decomposition(R, 3, 3);
    double **VT = matrix_transpose(svd[2], 3, 3);
    double **R2 = matrix_mult(svd[0], VT, 3, 3, 3, 3);
    if(R2 != NULL){
        double *determinante = matrix_determinant(R2, 3, 3);
        if(*determinante < 0){
            for(uint8_t dim = 0; dim < 3; dim++){
                VT[dim][2] = -VT[dim][2];
            }
            matrix_free(R2, 3);
            R2 = matrix_mult(svd[0], VT, 3, 3, 3, 3);
        }
        free(determinante);
        matrix_free(R, 3);
        R = R2;
    }
    matrix_free(VT, 3);
    matrix_free(svd[0], 3);
    matrix_free(svd[1], 3);
    matrix_free(svd[2], 3);
    free(svd);
*/
    return R;
 }

 //nem sempre funciona porque uint nao tem negativo
 void simularP6P_P4P(){

    double erro_atual = 0;
    double max_erro = 50;
    double delta_erro = 1;
    uint32_t samples_per_erro = 100;
    double tamanho_quarto = 3;

    uint32_t n_pontos = max_erro / delta_erro;

    double *erroP4P = (double*) malloc(n_pontos * sizeof(double));
    //double *erroP4P_sem_gauss;
    double *erroP6P = (double*) malloc(n_pontos * sizeof(double));

    double **rx4 = matrix_create_double(4, 4);
    rx4[0][0] = 0;   rx4[1][0] = 0.3; rx4[2][0] = 0;   rx4[3][0] = 1;
    rx4[0][1] = 0;   rx4[1][1] = 0;   rx4[2][1] = 0;   rx4[3][1] = 1;
    rx4[0][2] = 0.3; rx4[1][2] = 0;   rx4[2][2] = 0;   rx4[3][2] = 1;
    rx4[0][3] = 0.3; rx4[1][3] = 0.3; rx4[2][3] = 0;   rx4[3][3] = 1;

    double **rx6_function = matrix_create_double(6, 4);
    rx6_function[0][0] = 0;   rx6_function[0][1] = 0.3; rx6_function[0][2] = 0;   rx6_function[0][3] = 1;
    rx6_function[1][0] = 0;   rx6_function[1][1] = 0;   rx6_function[1][2] = 0;   rx6_function[1][3] = 1;
    rx6_function[2][0] = 0.3; rx6_function[2][1] = 0;   rx6_function[2][2] = 0;   rx6_function[2][3] = 1;
    rx6_function[3][0] = 0.3; rx6_function[3][1] = 0.3; rx6_function[3][2] = 0;   rx6_function[3][3] = 1;
    rx6_function[4][0] = -0.15; rx6_function[4][1] = 0.15; rx6_function[4][2] = 0.07;   rx6_function[4][3] = 1;
    rx6_function[5][0] = 0.45; rx6_function[5][1] = 0.15; rx6_function[5][2] = 0.07;   rx6_function[5][3] = 1;

    double **rx6_mult = matrix_create_double(4, 6);
    for(uint8_t i = 0; i < 6; i++){
        for(uint8_t j = 0; j < 4; j++){
            rx6_mult[j][i] = rx6_function[i][j];
        }
    }

    double **K = matrix_create_double(3, 3);
    K[0][0] = 3000;K[0][1] = 0;K[0][2] = 2000;
    K[1][0] = 0;K[1][1] = 3000;K[1][2] = 1500;
    K[2][0] = 0;K[2][1] = 0;K[2][2] = 1;

    double **R = matrix_identity(3);


    for(uint32_t i = 0; i < n_pontos; i++){
        erroP6P[i] = 0;
        erroP4P[i] = 0;


        for(uint32_t j = 0; j < samples_per_erro; j++){
            double **Xo = matrix_create_random(3, 1, 0.1, 3);
            if(Xo[2][0] < 0){
                Xo[2][0] = -Xo[2][0];
            }

            //R
            switch(rand()%5){
            case 0:
                R[0][0] = 1;    R[0][1] = 0;    R[0][2] = 0;
                R[1][0] = 0;    R[1][1] =  1;   R[1][2] = 0;
                R[2][0] = 0;    R[2][1] =  0;   R[2][2] = 1;
                break;
            case 1:
                R[0][0] = 0;    R[0][1] = 0;    R[0][2] = 1;
                R[1][0] = 1;    R[1][1] =  0;   R[1][2] = 0;
                R[2][0] = 0;    R[2][1] =  1;   R[2][2] = 0;
                break;
            case 2:
                R[0][0] = 0;    R[0][1] = -1;    R[0][2] = 0;
                R[1][0] = 1;    R[1][1] =  0;   R[1][2] = 0;
                R[2][0] = 0;    R[2][1] =  0;   R[2][2] = 1;
                break;/*
            case 3:
                R[0][0] = -1;    R[0][1] = 0;    R[0][2] = 0;
                R[1][0] = 0;    R[1][1] =  0;   R[1][2] = 1;
                R[2][0] = 0;    R[2][1] =  1;   R[2][2] = 0;
                break;
            case 4:
                R[0][0] = -1;   R[0][1] = 0;    R[0][2] = 0;
                R[1][0] = 0;    R[1][1] =  0;   R[1][2] = 1;
                R[2][0] = 0;    R[2][1] =  1;   R[2][2] = 0;
                break;
            case 5:
                R[0][0] = 0;    R[0][1] = 0;    R[0][2] = 1;
                R[1][0] = 0;    R[1][1] =  1;   R[1][2] = 0;
                R[2][0] = -1;   R[2][1] =  0;   R[2][2] = 0;
                break;*/
            case 3:
                R[0][0] = 0.5;     R[0][1] = -0.1464;  R[0][2] = 0.8536;
                R[1][0] = 0.5;     R[1][1] =  0.8536;  R[1][2] = -0.1464;
                R[2][0] = -0.7071; R[2][1] =  0.5;     R[2][2] = 0.5;
                break;
            case 4:
                R[0][0] = 0.3536;  R[0][1] = -0.5732; R[0][2] = 0.7392;
                R[1][0] = 0.6124;  R[1][1] =  0.7392; R[1][2] = 0.2803;
                R[2][0] = -0.7071; R[2][1] =  0.3536; R[2][2] = 0.6124;
                break;
            case 8:
                R[0][0] = -0.1268;  R[0][1] = -0.9268;  R[0][2] =  0.3536;
                R[1][0] =  0.7803;  R[1][1] =  0.1268;  R[1][2] =  0.6124;
                R[2][0] = -0.6124;  R[2][1] =  0.3536;  R[2][2] =  0.7071;
                break;
            default:
                break;
            }

            double **P = projection_matrix(K, R, Xo);

            double **sx4 = matrix_mult(P, rx4, 3, 4, 4, 4);
            for(uint8_t ii = 0; ii < 4; ii++){
                for(uint8_t dim = 0; dim < 3; dim++){
                    sx4[dim][ii] = sx4[dim][ii] / sx4[2][ii];
                }
            }
            printf("sx4aaaaaaaa\n");
            matrix_print(sx4, 3 ,4);


            double **sx6 = matrix_mult(P, rx6_mult, 3, 4, 4, 6);
            for(uint8_t ii = 0; ii < 6; ii++){
                for(uint8_t dim = 0; dim < 3; dim++){
                    sx6[dim][ii] = sx6[dim][ii] / sx6[2][ii];
                }
            }

            uint32_t **sx4_int = matrix_create_random_int(3, 4, 0, 0, 1);
            uint32_t **sx6_int = matrix_create_random_int(6, 3, 0, 0, 1);

            //p4p erro
            for(uint8_t ii = 0; ii < 4; ii++){
                uint32_t angulo = rand()%360;
                double rad = (double)angulo / (double)360;
                rad = rad * 2 * 3.14159265359;

                double x = erro_atual * cos(rad);
                double y = erro_atual * sin(rad);
                //if(ii!=1){
                //    x = 0;y = 0;
                //}

                if((sx4[0][ii] + x) < 0){
                    sx4_int[0][ii] = 0;
                }else{
                    sx4_int[0][ii] = (uint32_t) sx4[0][ii] + x;
                }

                if((sx4[1][ii] + y) < 0){
                    sx4_int[1][ii] = 0;
                }else{
                    sx4_int[1][ii] = (uint32_t) sx4[1][ii] + y;
                }
                sx4_int[2][ii] = (uint32_t)sx4[2][ii];
            }

            printf("sx4aaaaaaaa\n");
            matrix_print_int(sx4_int, 3 ,4);

            //p6p_erro
            for(uint8_t ii = 0; ii < 6; ii++){
                uint32_t angulo = rand()%360;
                double rad = (double)angulo / (double)360;
                rad = rad * 2 * 3.14159265359;

                double x = erro_atual * cos(rad);
                double y = erro_atual * sin(rad);

                //if(ii!=1){
                //    x = 0;y = 0;
                //}


                if((sx6[0][ii] + x) < 0){
                    sx6_int[ii][0] = 0;
                }else{
                    sx6_int[ii][0] = sx6[0][ii] + x;
                }

                if((sx6[1][ii] + y) < 0){
                    sx6_int[ii][1] = 0;
                }else{
                    sx6_int[ii][1] = sx6[1][ii] + y;
                }
                sx6_int[ii][2] = (uint32_t)sx6[2][ii];
            }

            //double ***xo_r = p4p_grunert_gauss_newton(K, rx4, sx4_int);
            double ***xo_r = p4p_grunert_gauss_newton_v2(K, rx4, sx4_int);

            double ***krz = p6p_dlt(sx6_int, rx6_function);

            double erro_3dp6p = 0;
            double erro_3dp4p = 0;
            for(uint8_t ii = 0; ii < 3; ii++){
                erro_3dp6p += pow(krz[2][ii][0] - Xo[ii][0], 2);
                erro_3dp4p += pow(xo_r[0][ii][0] - Xo[ii][0], 2);
            }
            erro_3dp6p = sqrt(erro_3dp6p);
            erro_3dp4p = sqrt(erro_3dp4p);
            erroP6P[i] += erro_3dp6p;
            erroP4P[i] += erro_3dp4p;


            matrix_free(P, 3);
            matrix_free(Xo, 3);
            matrix_free(sx4, 3);
            matrix_free(sx6, 3);
            matrix_free(sx4_int, 3);
            matrix_free(sx6_int, 6);
            matrix_free(krz[0], 3);
            matrix_free(krz[1], 3);
            matrix_free(krz[2], 3);
            free(krz);
            matrix_free(xo_r[0], 3);
            matrix_free(xo_r[1], 3);
            free(xo_r);
        }
        erro_atual += delta_erro;

        erroP6P[i] = erroP6P[i] / samples_per_erro;
        erroP4P[i] = erroP4P[i] / samples_per_erro;

    }

    /////////////////////////////////////////////////////////////////////////
    //printando
    erro_atual = 0;
    printf("erro_pixels = [");
    for(uint32_t i = 0; i < n_pontos; i++){
        printf("%f", erro_atual);
        erro_atual += delta_erro;
        if(i != (n_pontos - 1)){
            printf(",");
        }
    }
    printf("]\n\n");

    printf("erroP4P = [");
    for(uint32_t i = 0; i < n_pontos; i++){
        printf("%f", erroP4P[i]);
        if(i != (n_pontos - 1)){
            printf(",");
        }
    }
    printf("]\n\n");

    printf("erroP6P = [");
    for(uint32_t i = 0; i < n_pontos; i++){
        printf("%f", erroP6P[i]);
        if(i != (n_pontos - 1)){
            printf(",");
        }
    }
    printf("]\n\n");

    matrix_free(rx4, 4);
    matrix_free(rx6_function, 6);
    matrix_free(rx6_mult, 4);
    matrix_free(R, 3);
    matrix_free(K, 3);

    free(erroP4P);
    free(erroP6P);

 }
