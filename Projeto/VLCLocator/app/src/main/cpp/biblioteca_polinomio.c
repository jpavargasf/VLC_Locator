//
// Created by João on 27/03/2025.
//
#include "biblioteca_polinomio.h"

#include <time.h>
#include <math.h>
#include <stdio.h>

void biblioteca_polinomio_test(){
    srand(time(0));
    putchar('\n');
    printf("TESTE DA BIBLIOTECA DE POLINOMIO\n");
    printf("funcao dividir_polinomio: \n");

    double erro = 1e-5;
    uint32_t ordem = 0;
    double raiz = 0;
    double *p = NULL;

    switch(rand()%6){
        case 0:
            ordem = 2;
            raiz = -1;
            p = (double*) malloc((ordem + 1) * sizeof(double));
            p[0] = 1;p[1] = -9;p[2] = -10;
            break;
        case 1:
            ordem = 10;
            raiz = -1;
            p = (double*) malloc((ordem + 1) * sizeof(double));
            //for(uint8_t i = 0; i <= ordem; i++){
            //    p[i] = 0;
            //}
            //p[0] = 1; p[1] = -55; p[2] = 1320; p[3] = -18150; p[4] = 157773; p[5] = -902055; p[6] = 3416930; p[7] = -8409500; p[8] = 12753576; p[9] = -10628640; p[10] = 3628800;
            p[0] = 1; p[1] = 0; p[2] = -55; p[3] = 0; p[4] = 1023; p[5] = 0; p[6] = -7645; p[7] = 0; p[8] = 21076; p[9] = 0; p[10] = -14400;

            break;
        case 2:
            ordem = 4;
            raiz = 3;
            p = (double*) malloc((ordem + 1) * sizeof(double));
            p[0] = 1;p[1] = -10;p[2] = 35;p[3] = -50;p[4] = +24;
            break;
        case 3:
            ordem = 4;
            raiz = 3;
            p = (double*) malloc((ordem + 1) * sizeof(double));
            p[0] = 1; p[1] = -7; p[2] = 5; p[3] = 31; p[4] = -30;
            break;
        case 4:
            ordem = 4;
            raiz = 3;
            p = (double*) malloc((ordem + 1) * sizeof(double));
            p[0] = 1; p[1] = -2; p[2] = -13; p[3] = 14; p[4] = 24;
            break;
        case 5:
            ordem = 4;
            raiz = 3;
            p = (double*) malloc((ordem + 1) * sizeof(double));
            p[0] = 1; p[1] = 0; p[2] = -1700000; p[3] = 0; p[4] = 250000000000;
        default:
            break;
    }

    for(uint32_t i = 0; i <= ordem; i++){
        if(p[i] == 0){
            continue;
        }
        printf("%f",p[i]);
        if(i != ordem){
            printf("x^%d + ", ordem - i);
        }
    }
    putchar('\n');
    printf("dividido por x - (%f)\n", raiz);
    double *q = dividir_polinomio(p, ordem, raiz);

    if(q != NULL){


        for(uint32_t i = 0; i < ordem; i++){
            if(q[i] == 0){
                continue;
            }
            printf("%f", q[i]);
            if(i != ordem - 1){
                printf("x^%d + ", ordem - i - 1);
            }
        }
        printf("\nresto = %f\n", q[ordem]);

        //free(p);
        free(q);
    }


    printf("teste function_value x = 10\nObtido: %f\n", function_value(p, ordem, 10));


    double *intervalo = bisection_find_interval(p, ordem);
    printf("teste intervalo: [%f, %f]\n", intervalo[0], intervalo[1]);
    free(intervalo);

    double *roots = bisection_method(p, ordem, erro);
    printf("Teste do Método da Bisecção\nRaízes: [");
    for(uint32_t i = 0; i < ordem; i++){
        printf("%f", roots[i]);
        if(i != ordem - 1){
            printf(",");
        }else{
            printf("]\n");
        }
    }

    free(roots);

    printf("Teste Derivada\n");
    double *derivada = derivative(p, ordem);
    print_polinomio(derivada, ordem - 1);
    free(derivada);


    printf("Teste Global Newton Method\n");
    double **nmRoots = global_newton_method(p, ordem, erro);
    if(nmRoots == NULL){
        printf("NULL\n");
    }else{
        printf("[");
        for(uint32_t i = 0; i < ordem; i++){
            if(nmRoots[i] != NULL){
                printf("%f", nmRoots[i][0]);
                free(nmRoots[i]);
            }else{
                printf("NULL");
            }
            if(i != ordem - 1){
                printf(",");
            }else{
                printf("]\n");
            }
        }
        free(nmRoots);
    }


    free(p);




    printf("fim - TESTE DA BIBLIOTECA DE POLINOMIO\n");
}

double *dividir_polinomio(double *polinomio, uint32_t ordem, double raiz){
    if(polinomio == NULL || ordem <= 0){
        return NULL;
    }

    for(uint32_t j = 0; j <= ordem; j++){
        //printf("pol %d: %f\n", j, polinomio[j]);
    }
    double *q;

    q = (double*) malloc((ordem + 1) * sizeof(double));

    for(int32_t i = ordem; i >= 0; i--){
        //printf("pol:%f\n",polinomio[i]);
        q[ordem - i] = 0;
        for(uint32_t j = 0; j <= (ordem - i); j++){
            if(ordem - i - j > 0){
                q[ordem - i] += polinomio[j] * pow(raiz, ordem - i - j);
            }else{
                q[ordem - i] += polinomio[j];
                //printf("%f\n",polinomio[j]);
            }
        }
    }
    return q;
}

double *bisection_method(double *polinomio, uint32_t ordem, double erro){
    if(polinomio == NULL || ordem == 0){
        return NULL;
    }

    uint32_t ordem_atual = ordem;
    double *roots = (double*) malloc(ordem * sizeof(double));
    double *polinomio_atual = (double*) malloc((ordem + 1) * sizeof(double));
    for(uint32_t i = 0; i <= ordem; i++){
        polinomio_atual[i] = polinomio[i];
    }
    for(uint32_t i = 0; i < ordem; i++){
        //print_polinomio(polinomio_atual, ordem_atual);
        roots[i] = bisection_find_root(polinomio_atual, ordem_atual, erro);
        //printf("%d\t%f\n", i, roots[i]);
        double *polinomio_proximo = dividir_polinomio(polinomio_atual, ordem_atual, roots[i]);
        ordem_atual--;
        free(polinomio_atual);
        polinomio_atual = polinomio_proximo;
    }
    free(polinomio_atual);
    return roots;
}


double *bisection_find_interval(double *polinomio, uint32_t ordem){
    if(polinomio == NULL || ordem == 0){
        return NULL;
    }
    double *interval = (double*) malloc(2 * sizeof(double));
    double f_value[2];
    //passo
    double step;
    //para descobrir a ordem em que vai fazer a iteração
    double weighted_sum_even = 0;
    double weighted_sum_odd = 0;
    uint8_t it_index;

    //define o intervalo inicial
    interval[0] = 0;
    interval[1] = 0;
    for(uint32_t i = 0; i <= ordem; i++){
        uint32_t ordemAtual = ordem - i;
        if(ordemAtual % 2 == 1){
            weighted_sum_odd += polinomio[i] * (ordemAtual + 1);
        }else{
            weighted_sum_even += polinomio[i] * (ordemAtual + 1);
        }
        /*
        double atual = polinomio[i];
        if(atual < 0){
            atual = -atual;
        }
        if(atual > interval[1]){
            interval[1] = atual;
        }*/
    }

    interval[1] = polinomio[ordem] / polinomio[0];
    if(interval[1] < 0){
        interval[1] = - interval[1];
    }
    interval[1] = pow(interval[1], 1 / (double)ordem);

    interval[0] = -interval[1];

    f_value[0] = function_value(polinomio, ordem, interval[0]);
    f_value[1] = function_value(polinomio, ordem, interval[1]);
    if((f_value[0] > 0 && f_value[1] < 0) || (f_value[1] > 0 && f_value[0] < 0)){
        return interval;
    }

    step = 1 / (double)ordem;
    if(weighted_sum_even > 0 || weighted_sum_odd < 0){
        it_index = 0;
        step = -step;
    }else{
        it_index = 1;
    }
    interval[it_index] = interval[1 - it_index];


/*
    if(f_value[0] < 0){
        it_index = 1;
    }else{
        it_index = 0;
        step = -step;
    }*/
#ifdef BISECTION_SPECIALIZED
    /*
    double step_abs = step;
    if(step_abs < 0){
        step_abs = -step_abs;
    }

*/

    uint32_t n = 0;
    double n_max = 2 * interval[1 - it_index] / step;
    if(n_max < 0){
        n_max = -n_max;
    }
    //printf("nmax  = %d\n", (uint32_t) n_max);

#endif // BISECTION_SPECIALIZED

    do{
        interval[it_index] += step;
        f_value[it_index] = function_value(polinomio, ordem, interval[it_index]);
        //printf("n = %d\t[%f, %f]\t[%f, %f]\n",++n, f_value[0], f_value[1], interval[0], interval[1]);
#ifdef BISECTION_SPECIALIZED

        if(++n > (uint32_t)n_max){
            printf("switched\n");
            n = 0;
            interval[it_index] = interval[1 - it_index];
            if(step < 0){
                step = - step * step;
            }else{
                step = step * step;
            }
            n_max = 2 * interval[1 - it_index] / step;
            if(n_max < 0){
                n_max = -n_max;
            }
            //printf("nmax  = %d\n", (uint32_t)n_max);
        }
        /*
        if((interval[it_index] + interval[1 - it_index]) <= step_abs){
            if(step < 0){
                step = - step * step;
                step_abs = -step;
            }else{
                step = step * step;
                step_abs = step;
            }
            interval[it_index] = interval[1 - it_index];
        }
        */
#endif // BISECTION_SPECIALIZED
    }while(((f_value[0] < 0 && f_value[1] < 0) || (f_value[0] > 0 && f_value[1] > 0)) && (f_value[it_index] != 0));


    return interval;
}

double bisection_find_root(double *polinomio, uint32_t ordem, double erro){
    //assumindo que polinomio != NULL e ordem >= 1
    double *interval = bisection_find_interval(polinomio, ordem);
    double f_sup = function_value(polinomio, ordem, interval[1]);
    double f_inf = function_value(polinomio, ordem, interval[0]);
    double f_zero;
    double root;
    //uint32_t n = 0;


    if(f_sup == 0){
        root = interval[1];
        goto bisection_find_root_end;
    }
    if(f_inf == 0){
        root = interval[0];
        goto bisection_find_root_end;
    }
    if(f_sup < 0){
        double aux = f_sup;
        f_sup = f_inf;
        f_inf = aux;
        aux = interval[1];
        interval[1] = interval[0];
        interval[0] = aux;
    }

    do{
        //printf("[%f,%f] - ", interval[0], interval[1]);
        root = (interval[0] + interval[1]) / 2;
        f_zero = function_value(polinomio, ordem, root);
        if(f_zero > 0){
            interval[1] = root;
        }else{
            interval[0] = root;
            f_zero = -f_zero;
        }
        //printf("%d\t%f\t%f\n", n++, root, f_zero);
    }while(f_zero > erro);
    bisection_find_root_end:
    free(interval);
    return root;
}

double function_value(double *polinomio, uint32_t ordem, double x){
    double x_mult = 1;
    double val = 0;

    uint32_t i = ordem + 1;
    do{
        i--;
        val += polinomio[i] * x_mult;

        x_mult = x_mult * x;
    }while(i != 0);

    return val;
}

void print_polinomio(double *polinomio, uint32_t ordem){
    if(polinomio == NULL){
        return;
    }

    for(uint32_t i = 0; i <= ordem; i++){
        if(polinomio[i] == 0)   continue;
        printf("%f", polinomio[i]);
        if(i != ordem){
            printf("x^%d + ", ordem - i);
        }
    }
    printf("\n");
}

double *intervalo_todas_raizes(double *polinomio, uint32_t ordem){
    if(polinomio == NULL){

    }
}

//retorna as raizes reais
double **quartic_function_roots(double *polinomio, uint8_t ordem){
    if(polinomio == NULL || ordem != 4){
        return NULL;
    }
    double a = polinomio[0];
    double b = polinomio[1];
    double c = polinomio[2];
    double d = polinomio[3];
    double e = polinomio[4];

    double p = (8 * a * c - 3 * b * b) / (8 * a * a * a);

    double q = (b * b * b - 4 * a * b * c + 8 * a * a * d) / (8 * a * a * a);

    double delta0 = c * c - 3 * b * d + 12 * a * e;

    double delta1 = 2 * c * c * c - 9 * b * c * d + 27 * b * b * e + 27 * a * d * d - 72 * a * c * e;

    double aux1Q = pow(delta1, 2) - 4 * pow(delta0, 3);
    if(aux1Q < 0){
        return NULL;
    }
    aux1Q = sqrt(aux1Q);
    double aux2Q = (delta1 + aux1Q) / 2;
    if(aux2Q < 0){
        return NULL;
    }
    double Qzao = pow(aux2Q, (double) ((double)1 / (double)3));

    double auxS = - (2 / 3) * p + (1 / (3 * a)) * (Qzao + delta0 / Qzao);
    if(auxS < 0){
        return NULL;
    }
    double S = (1 / 2) * sqrt(auxS);
    return NULL;
}

double *derivative(double *polinomio, uint32_t ordem){
    if(polinomio == NULL){
        return NULL;
    }

    double *d;
    uint32_t nova_ordem;
    if(ordem == 0){
        nova_ordem = 0;
    }else{
        nova_ordem = ordem - 1;
    }

    d = (double*) malloc((nova_ordem + 1) * sizeof(double));
    for(uint32_t i = 0; i < (nova_ordem + 1); i++){
        d[i] = (ordem - i) * polinomio[i];
    }
    return d;
}

//para DBL_EPSILON
#include <float.h>

double **global_newton_method(double *polinomio, uint32_t ordem, double error){
    if(polinomio == NULL || ordem == 0){
        return NULL;
    }
    printf("global_newton_method\n");
    double *p = (double*) malloc((ordem + 1) * sizeof(double));
    for(uint32_t i = 0; i <= ordem; i++){
        p[i] = polinomio[i];
    }
    double **roots = (double**) malloc(ordem * sizeof(double*));
    for(uint32_t i = 0; i < ordem; i++){
        printf("Polinomio %d\n", i);


        print_polinomio(p, ordem - i);

        double *derivada = derivative(p, ordem - i);
        print_polinomio(derivada, ordem -i -1);

        double x = 0;
        double deltaX = 1 / error;
        double fx, fxd;
        //double abs_fx, abs_ft;
        double a;

        /*
        double x = polinomio[ordem] / polinomio[0];
        if(x < 0){
            x = -x;
        }
        x = sqrt(x, 1 / (double)ordem);

        if(((polinomio[ordem] < 0 && polinomio[0] < 0) || (polinomio[ordem] > 0 && polinomio[0] > 0)) &&
           ordem % 2 == 0)
           */
        fx = function_value(p, ordem -i, x);
        //abs_fx = fabs(fx);
        while(fabs(fx) > error && fabs(deltaX) > error){
            fxd = function_value(derivada, ordem -i - 1, x);
            if(fxd == 0){
                //fxd = error;
                fxd = DBL_EPSILON;
            }
            deltaX = fx / fxd;
            double t = x - deltaX;
            a = 1;
            double ft = function_value(p, ordem -i, t);
            while(fabs(ft) > fabs(fx)){
                a = a / 2;
                t = x - a * deltaX;
                ft = function_value(p, ordem -i, t);
            }
            deltaX = x - t;
            x = t;
            fx = ft;
        }


        free(derivada);
        printf("x = %f\n", x);
        if(fabs(fx) > error){
            printf("No real roots left\n");
            for(uint32_t j = i; j < ordem; j++){
                roots[j] = NULL;
            }
        }
        roots[i] = (double*) malloc(sizeof(double));
        roots[i][0] = x;

        double *p2 = dividir_polinomio(p, ordem - i, x);
        free(p);
        p = p2;
    }
    free(p);
    return roots;
}
