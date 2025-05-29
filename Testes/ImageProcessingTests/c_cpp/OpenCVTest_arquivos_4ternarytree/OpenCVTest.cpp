// OpenCVTest.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//


#include <iostream>
#include <cstdlib>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "ImageProcessing.h"


cv::Mat resizeImg(cv::Mat image, int* width, int* height) {
    if (width == NULL && height == NULL) {
        return image;
    }
    
    int w = image.cols;
    int h = image.rows;
    float proportion = (float)w / (float)h;
    
    int newWidth;
    int newHeight;

    if (width == NULL) {
        newHeight = *height;
        newWidth = (int)(proportion * ((float)*height));
    }
    else {
        if (height == NULL) {
            newWidth = *width;
            newHeight = (int)((float)*width / proportion);
        }
        else {
            newWidth = *width;
            newHeight = *height;
        }
    }
    cv::Mat r;
    cv::resize(image, r, cv::Size(newWidth, newHeight), cv::INTER_LINEAR);
    return r;
}

//deve ser usado apenas quando é usado malloc, calloc ou realloc
void freeVar(void* var) {
    if (var != NULL) {
        free(var);
        var = NULL;
    }
}

uint8_t** cvMat2Byte(cv::Mat image) {
    uint8_t** ui8Img = NULL;
    if (!image.empty()) {
        int w = image.cols;
        int h = image.rows;

        int i, j, aux;
        
        ui8Img = (uint8_t**)malloc(h * sizeof(uint8_t*));
        for (i = 0; i < h; i++) {
            ui8Img[i] = (uint8_t*)malloc(w * sizeof(uint8_t));
        }
        
        /*
        ui8Img = new uint8_t**[h];
        for (i = 0; i < h; i++) {
            ui8Img[i] = (uint8_t*)malloc(w * sizeof(uint8_t));
        }
        */
        uint8_t* pixelPtr = (uint8_t*)image.data;
        //https://stackoverflow.com/questions/7899108/opencv-get-pixel-channel-value-from-mat-image
        
        aux = 0;
        for (i = 0; i < h; i++) {
            for (j = 0; j < w; j++) {
                //std::cout << "["<<i<<","<<j<<"] - " << (int) pixelPtr[aux] << std::endl;
                ui8Img[i][j] = pixelPtr[aux++];
                //std::cout << "[" << i << "," << j << "] - " << (int)ui8Img[i][j] << std::endl;
            }
        }
        std::cout << "[" << i << "," << j << "] - " << "Done" << std::endl;
    }
    return ui8Img;
}



int main()
{
    int a = 1000;
    int* widthWindow;
    int* heightWindow;
    widthWindow = NULL;
    heightWindow = &a;

    std::cout << "Hello World!\n";

    auto filename = "../../../SourceFiles/test2.png";
    cv::Mat imagem = cv::imread(filename);
    cv::Mat gsimg;
    cv::Mat aux;
    cv::Mat blurImg;
    cv::Mat bwImg;

    aux = resizeImg(imagem, widthWindow, heightWindow);
    //cv::namedWindow("img", cv::WINDOW_AUTOSIZE);
    cv::imshow("img", aux);
    //cv::waitKey(0);
    aux.release();

    cv::cvtColor(imagem, gsimg, cv::COLOR_BGR2GRAY);

    aux = resizeImg(gsimg, widthWindow, heightWindow);
    cv::imshow("gsimg", aux);
    //cv::waitKey();
    aux.release();
/*
    cv::blur(gsimg, blurImg, cv::Size(100,100));
    aux = resizeImg(blurImg, widthWindow, heightWindow);
    cv::imshow("blurImg", aux);
    //cv::waitKey();
    aux.release();
*/
    blurImg = gsimg.clone();
    cv::threshold(blurImg, bwImg, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    aux = resizeImg(bwImg, widthWindow, heightWindow);
    cv::imshow("bwImg", aux);
    cv::waitKey();
    aux.release();

    ImageProcessing imgprocs;
    imgprocs.setImage(&bwImg);

    std::list<Blob*> blobs;
    std::list<Blob*>::iterator it;
    blobs = imgprocs.findBlobs();
    for (it = blobs.begin(); it != blobs.end(); ++it) {
        std::cout << "new blob" << std::endl;
        (*it)->diplayPixelTree();
        (*it)->freeTree();
    }

    uint8_t** ui8img =  cvMat2Byte(bwImg);

    for (int i = 0; i < bwImg.rows; i++) {
        free(ui8img[i]);
    }
    free(ui8img);
    ui8img = NULL;

    imagem.release();
    gsimg.release();

    //freeVar(heightWindow);
    heightWindow = NULL;
    //freeVar(widthWindow);
    widthWindow = NULL;

    cv::destroyAllWindows();
    system("pause");
    return 0;
}



// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar: 
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln
