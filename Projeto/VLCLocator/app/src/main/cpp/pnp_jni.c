//
// Created by João on 28/03/2025.
//
#include <jni.h>

#include "Perspective_n_Point.h"

/*
extern "C" JNIEXPORT jdoubleArray JNICALL
Java_com_example_vlclocator_ImageProcessing_p4p_jni(
        JNIEnv* env,
        jobject /* this *//*,
        jintArray bloobCoordinates,
        jintArray mapping,
        jint nBlobs,
        jdoubleArray K,
        jdoubleArray pontos_real) {

    //adquire os vetores do java
    jdouble *pr = env->GetDoubleArrayElements(pontos_real, NULL);
    jdouble *K_array = env->GetDoubleArrayElements(K, NULL);

    jint *bloobCoord = env->GetIntArrayElements(bloobCoordinates, NULL);
    jint *map = env->GetIntArrayElements(mapping, NULL);

    double* center = (double*) malloc(8 * sizeof(double));

    for(uint32_t i = 0; i < nBlobs; i++){
        if(map[i] != -1){
            center[2 * map[i]] = (bloobCoord[4 * i] + bloobCoord[4 * i + 1]) / 2;
            center[2 * map[i] + 1] = (bloobCoord[4 * i + 2] + bloobCoord[4 * i + 3]) / 2;
        }
    }


    //cria jintArray para passar para o java
    jdoubleArray result = env->NewDoubleArray(8);

    //define os valores de jintArray como grayImage
    env->SetDoubleArrayRegion(result, 0, 8, center);

    //ReleaseIntArrayElements: Releases the native memory used by the original jintArray.
    env->ReleaseIntArrayElements(bloobCoordinates, bloobCoord, 0);
    env->ReleaseIntArrayElements(mapping, map, 0);

    env->ReleaseDoubleArrayElements(K, K_array, 0);
    env->ReleaseDoubleArrayElements(pontos_real, pr, 0);


    return result;
}
*/