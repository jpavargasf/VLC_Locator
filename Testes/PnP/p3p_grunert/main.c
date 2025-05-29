#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#define BISECTION_SPECIALIZED 1

#include "Perspective_n_Point.h"
//#include "biblioteca_polinomio.h"
#include "matrix.h"



int main()
{
    srand(time(NULL));
    printf("P3P Grunert!\n");
    //matrix_test();
    //test_p6p_p4p();
    //test_p6p_p4p_v2();
    //biblioteca_polinomio_test();
    //p3p_grunert_test();
    //p4p_grunert_test();
    //Rt_test();

    //p4p_grunert_test_v2();
    //for(uint8_t i = 0; i < 10; i++){
    //    printf("__________________________________________________\n");
    //}
    p4p_grunert_test_v2_ideal();



    //simularP6P_P4P();

    return 0;
}
