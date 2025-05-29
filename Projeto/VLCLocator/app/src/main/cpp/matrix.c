//
// Created by João on 27/03/2025.
//
#include "matrix.h"

uint8_t matrix_test(){
    srand(time(NULL));
    printf("Hello world!\n");

    double **A;
    uint32_t heightA = 12;
    uint32_t widthA = heightA;
    double **B;
    uint32_t heightB = widthA;
    uint32_t widthB = 4;
    //A = matrix_create_random(heightA, widthA, 0, 10);
    A = matrix_create_random_int(heightA, widthA, 1, -10, 10);
    B = matrix_create_random(heightB, widthB, 0, 10);
/*
    A[0][0] = 12;
    A[0][1] = -51;
    A[0][2] = 4;
    A[1][0] = 6;
    A[1][1] = 167;
    A[1][2] = -68;
    A[2][0] = -4;
    A[2][1] = 24;
    A[2][2] = -41;
*/
/*
    A[0][0] = 2;
    A[0][1] = 3;
    A[1][0] = 1;
    A[1][1] = 1;
    */
/*
    A[0][0] = 1.593500;
    A[0][1] = 1.444724;
    A[0][2] = 1.342031;
    A[1][0] = 4.886397;
    A[1][1] = 2.276951;
    A[1][2] = 0.339361;
    A[2][0] = 0.036927;
    A[2][1] = 3.027237;
    A[2][2] = 4.093690;
    */
/*
Eigenvalues of A:[6.256201, 1.133449, 0.574490]
Eigenvalue = 6.256201   Eigenvector = [0.507245, 0.708164, 1.000000]
Eigenvalue = 1.133449   Eigenvector = [0.159844, -0.979819, 1.000000]
Eigenvalue = 0.574490   Eigenvector = [0.337011, -1.166623, 1.000000]
*/
/*
    A[0][0] = 2;
    A[0][1] = 0;
    A[1][0] = 0;
    A[1][1] = 3;
*/
/*
    A[0][0] = 3;
    A[0][1] = 0;
    A[0][2] = 0;
    A[1][0] = 0;
    A[1][1] = 2;
    A[1][2] = 0;
    A[2][0] = 0;
    A[2][1] = 0;
    A[2][2] = 3;
*/
#ifdef PRINT_MATRIX
    printf("A\n");
    matrix_print(A, heightA, widthA);
    printf("B\n");
    matrix_print(B, heightB, widthB);
#endif // PRINT_MATRIX

    double **C;
    C = matrix_mult(A,B, heightA, widthA, heightB, widthB);
#ifdef PRINT_MATRIX
    printf("C = AB\n");
    matrix_print(C, heightA, widthB);
#endif // PRINT_MATRIX
    double **T;
    T = matrix_transpose(C, heightA, widthB);
#ifdef PRINT_MATRIX
    printf("T = C^T\n");
    matrix_print(T, widthB, heightA);
#endif // PRINT_MATRIX

    double **I;
    I = matrix_inverse(A, heightA, widthA);
#ifdef PRINT_MATRIX
    printf("I = A^-1\n");
    matrix_print(I, heightA, widthA);
#endif // PRINT_MATRIX
    //inversa
    double **AI;
    AI = matrix_mult(A,I, heightA, widthA, heightA, widthA);
#ifdef PRINT_MATRIX
    printf("AA^-1\n");
    matrix_print(AI, heightA, widthA);
#endif // PRINT_MATRIX
    //teste de troca de linha
/*
    double *aux = AI[0];
    AI[0] = AI[1];
    AI[1] = aux;
    printf("AI\n");
    matrix_print(AI, heightA, widthA);
*/

    //teste decomposicao qr
    double ***qr;
    qr = qr_decomposition(A, heightA, widthA);
#ifdef PRINT_MATRIX
    printf("QR{A} = \n");
    printf("Q\n");
    matrix_print(qr[0], heightA, widthA);
    printf("R\n");
    matrix_print(qr[1], heightA, widthA);
#endif // PRINT_MATRIX
    double **Ar;
    Ar = matrix_mult(qr[0], qr[1], heightA, widthA, heightA, widthA);
#ifdef PRINT_MATRIX
    printf("QR = \n");
    matrix_print(Ar, heightA, widthA);
#endif // PRINT_MATRIX
    printf("QR - ");
    if(matrix_equal(A, Ar, heightA, widthA, heightA, widthA)){
        printf("SUCESSO\n");
    }else{
        printf("FALHA\n");
    }


    double *lambda;
    lambda = eigenvalues(A, heightA, widthA);
#ifdef PRINT_MATRIX
    printf("Eigenvalues of A:[");
    for(uint32_t index = 0; index < heightA; index++){
        printf("%f", lambda[index]);
        if(index != heightA - 1){
            printf(", ");
        }
    }
    printf("]\n");

    for(uint32_t index = 0; index < heightA; index++){
        double **v;
        uint32_t counter = 0;
        v = eigenvector(A, heightA, widthA, lambda[index]);
        printf("Eigenvalue = %f\n",lambda[index]);
        do{
            if(v[counter] == NULL){
                break;
            }
            printf("\tEigenvector = [");
            for(uint32_t j = 0; j < heightA; j++){
                printf("%f", v[counter][j]);
                if(j != heightA - 1){
                    printf(", ");
                }
            }
            printf("]\n");
            counter++;
        }while(1);

        counter = 0;
        do{
            if(v[counter] == NULL){
                free(v);
                break;
            }
            free(v[counter]);
            counter++;
        }while(1);
    }
#endif // PRINT_MATRIX

    double ***svd = svd_decomposition(A, heightA, widthA);
#ifdef PRINT_MATRIX
    printf("SVD{A}\n");
    printf("S = \n");
    matrix_print(svd[0], heightA, heightA);
    printf("Sigma = \n");
    matrix_print(svd[1], heightA, widthA);
    printf("V = \n");
    matrix_print(svd[2], widthA, widthA);
#endif // PRINT_MATRIX

    double **aux_m = matrix_mult(svd[0], svd[1], heightA, heightA, heightA, widthA);
    double **VT = matrix_transpose(svd[2], widthA, widthA);
    double **svd_m = matrix_mult(aux_m, VT, heightA, widthA, widthA, widthA);
#ifdef PRINT_MATRIX
    printf("SVD multiplicado ( S * Sigma * V^T )\n");
    matrix_print(svd_m, heightA, widthA);
#endif // PRINT_MATRIX
    printf("SVD - ");
    if(matrix_equal(A, svd_m, heightA, widthA, heightA, widthA)){
        printf("SUCESSO\n");
    }else{
        printf("FALHA\n");
    }



    //teste svd com dimensões diferentes
    uint32_t height2 = 2;
    uint32_t width2 = 3;
    double **matriz = matrix_create_random_int(height2,width2,0,-10,10);

    /*
    matriz[0][0] = 8;
    matriz[0][1] = 8;
    matriz[0][2] = 8;
    matriz[1][0] = -3;
    matriz[1][1] = 3;
    matriz[1][2] = 0;
*/

    /*
    matriz[0][0] = 1;
    matriz[0][1] = -1;
    matriz[0][2] = 0;
    matriz[1][0] = -7;
    matriz[1][1] = -2;
    matriz[1][2] = 0;
    */
#ifdef PRINT_MATRIX
    printf("matriz = \n");
    matrix_print(matriz, height2, width2);
#endif // PRINT_MATRIX
    double ***svd2 = svd_decomposition(matriz, height2, width2);
#ifdef PRINT_MATRIX
    printf("SVD{matriz}\n");
    printf("S = \n");
    matrix_print(svd2[0], height2, height2);
    printf("Sigma = \n");
    matrix_print(svd2[1], height2, width2);
    printf("V = \n");
    matrix_print(svd2[2], width2, width2);
#endif // PRINT_MATRIX
    double **aux_m2 = matrix_mult(svd2[0], svd2[1], height2, height2, height2, width2);
    double **VT2 = matrix_transpose(svd2[2], width2, width2);
    double **svd_m2 = matrix_mult(aux_m2, VT2, height2, width2, width2, width2);
#ifdef PRINT_MATRIX
    printf("SVD multiplicado ( S * Sigma * V^T )\n");
    matrix_print(svd_m2, height2, width2);
#endif // PRINT_MATRIX
    printf("SVD - ");
    if(matrix_equal(matriz, svd_m2, height2, width2, height2, width2)){
        printf("SUCESSO\n");
    }else{
        printf("FALHA\n");
    }

    matrix_free(aux_m2, height2);
    aux_m2 = NULL;
    matrix_free(VT2, width2);
    VT2 = NULL;
    matrix_free(svd_m2, height2);
    svd_m2 = NULL;

    matrix_free(svd2[0], height2);
    matrix_free(svd2[1], height2);
    matrix_free(svd2[2], width2);
    free(svd2);
    svd2 = NULL;


    matrix_free(aux_m, heightA);
    aux_m = NULL;
    matrix_free(VT, widthA);
    VT = NULL;
    matrix_free(svd_m, heightA);
    svd_m = NULL;

    matrix_free(svd[0], heightA);
    matrix_free(svd[1], heightA);
    matrix_free(svd[2], widthA);
    free(svd);
    svd = NULL;


    free(lambda);
    lambda = NULL;

    matrix_free(Ar, heightA);
    matrix_free(qr[0], heightA);
    matrix_free(qr[1], heightA);
    free(qr);
    qr = NULL;

    matrix_free(AI, heightA);
    matrix_free(I, heightA);
    matrix_free(T, widthB);
    matrix_free(C, heightA);
    matrix_free(A, heightA);
    matrix_free(B, heightB);
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
    if(A == NULL || heightA == 0){
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
                    if(eigenval[line] >= 0){
                        svd[1][line][column] = sqrt(eigenval[line]);
                    }else{
                        //o exemplo que eu vi tinha residuo negativo
                        //printf("svd: eigenval < 0::%f\n", eigenval[line]);
                        svd[1][line][column] = 0;
                    }
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
void matrix_free_uint32_t(uint32_t** A, uint32_t heightA){
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

double **centroid(double **points, uint32_t dimensions, uint32_t n_points){
    if(points == NULL || n_points == 0 || dimensions == 0){
        return NULL;
    }
    double **p = (double **) malloc(dimensions * sizeof(double*));
    for(uint32_t dim = 0; dim < dimensions; dim++){
        p[dim] = (double*) malloc(sizeof(double));
        p[dim][0] = 0;
        for(uint32_t n = 0; n < n_points; n++){
            p[dim][0] += points[dim][n];
        }
        p[dim][0] = p[dim][0] / n_points;
    }
    return p;
}

double **matrix_copy(double **matrix, uint32_t height, uint32_t width){
    if(matrix == NULL || height == 0 || width == 0){
        return NULL;
    }
    double **A = (double **) malloc(height * sizeof(double*));
    for(uint32_t line = 0; line < height; line++){
        A[line] = (double*) malloc(width * sizeof(double));
        for(uint32_t column = 0; column < width; column++){
            A[line][column] = matrix[line][column];
        }
    }
    return A;
}

//tem sinal errado porque o determinante de Q pode ser mais ou menos 1
/*
double *matrix_determinant(double **matrix, uint32_t height, uint32_t width){
    if(height != width){
        return NULL;
    }
    double ***qr = qr_decomposition(matrix, height, width);
    if(qr == NULL){
        return NULL;
    }
    double *determinant = (double*) malloc(sizeof(double));
    *determinant = 1;
    for(uint8_t i = 0; i < height; i++){
        *determinant *= qr[1][i][i];
    }
    matrix_free(qr[0], height);
    matrix_free(qr[1], height);
    free(qr);
    return determinant;
}
*/
double *matrix_determinant(double **matrix, uint32_t height, uint32_t width){
    if(height != width || matrix == NULL || height == 0){
        return NULL;
    }
    double **A = matrix_copy(matrix, height, width);
    double *determinant = (double*) malloc(sizeof(double));
    //sinal inicial
    *determinant = 1;
    //primeiro: transformar a matriz em triangular superior
    for(uint32_t index = 0; index < height; index++){

        //checa se o elemento é não nulo
        if(A[index][index] == 0){
            //se é nulo, procura alguma linha abaixo que não seja nula
            for(uint32_t line = index + 1; line < height; line++){
                if(A[line][index] != 0){
                    //trocar a linha
                    double *aux = A[line];
                    A[line] = A[index];
                    A[index] = aux;

                    //inverte o sinal inicial
                    *determinant = -*determinant;
                    break;
                }
            }
        }

        //zera os elementos das linhas abaixo
        for(uint32_t line = index + 1; line < height; line++){
            if(A[line][index] != 0){
                double mult_factor = A[line][index] / A[index][index];
                for(uint32_t column = 0; column < width; column++){
                    A[line][column] = A[line][column] - mult_factor * A[index][column];
                }
            }
        }
    }
    //printf("matrix_determinant\n");
    //printf("matrix\n");
    //matrix_print(matrix, height, width);
    //printf("A\n");
    //matrix_print(A, height, width);


    //calcula o determinante
    for(uint32_t index = 0; index < height; index++){
        *determinant = *determinant * A[index][index];
    }
    //printf("determinant = %f\n", *determinant);
    matrix_free(A, height);

    return determinant;

}

double **cross_product(double **A, uint32_t columnA, double **B, uint32_t columnB, uint32_t dimension){
    if(A == NULL || B == NULL || dimension == 0){
        return NULL;
    }
    double **r = (double**) malloc(dimension * sizeof(double*));
    for(uint32_t line = 0; line < dimension; line++){
        r[line] = (double*) malloc(sizeof(double));
        r[line][0] = 0;
    }

    for(uint32_t line1 = 0; line1 < dimension; line1++){
        for(uint32_t line2 = 0; line2 < dimension; line2++){

        }
    }

}

double **matrix_create_double(uint32_t height, uint32_t width){
    double **A = NULL;

    if(height != 0 && width != 0){
        A = (double**) malloc(height * sizeof(double*));
        for(uint32_t i = 0; i < height; i++){
            A[i] = (double*) malloc(width * sizeof(double));
        }
    }

    return A;
}

double **matrix_uint32_t_to_double(uint32_t **matrix, uint32_t height, uint32_t width){
    if(matrix == NULL || height == 0 || width == 0){
        return NULL;
    }
    double **A = (double**) malloc(height * sizeof(double*));
    for(uint32_t i = 0; i < height; i++){
        A[i] = (double*) malloc(width * sizeof(double));
        for(uint32_t j = 0; j < width; j++){
            A[i][j] = (double) matrix[i][j];
        }
    }
    return A;
}

double **matrix_identity(uint32_t dimension){
    if(dimension == 0){
        return NULL;
    }
    double **matrix = (double**) malloc(dimension * sizeof(double*));
    for(uint32_t i = 0; i < dimension; i++){
        matrix[i] = (double*) malloc(dimension * sizeof(double));
        for(uint32_t j = 0; j < dimension; j++){
            matrix[i][j] = i == j;
        }
    }
    return matrix;
}
