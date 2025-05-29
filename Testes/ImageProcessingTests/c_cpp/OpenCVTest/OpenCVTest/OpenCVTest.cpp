// OpenCVTest.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//


#include <iostream>
#include <cstdlib>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "ImageProcessing.h"


void resizeImage(cv::Mat *matImage, unsigned int value, bool valueIsWidth) {

    if (value == 0) return;

    int w = matImage->cols;
    int h = matImage->rows;
    float proportion = (float)w / (float)h;

    int newWidth;
    int newHeight;

    if (valueIsWidth) {
        newWidth = value;
        newHeight = (int)((float)newWidth / proportion);
    }
    else {
        newHeight = value;
        newWidth = (int)(proportion * ((float)newHeight));
    }


    cv::resize(*matImage, *matImage, cv::Size(newWidth, newHeight), cv::INTER_LINEAR);

}
/*
int* grayImgHistogram(cv::Mat img) {
    int* histogram = (int*)malloc(256 * sizeof(int));
    int i;
    for (i = 0; i <= 255; i++) {
        histogram[i] = 0;
    }
    
    int nPixels = img.rows * img.cols;
    for (i = 0; i < nPixels; i++) {
        histogram[img.data[i]]++;
    }
    return histogram;
}

int otsuThreshold(cv::Mat img) {
    if (img.empty())   return -1;

    int* hist = grayImgHistogram(img);



}
*/

int main()
{
    int a = 1000;


    std::cout << "Hello World!\n";

    //auto filename = "../../../SourceFiles/test2.png";
    std::string fileName = "../../../SourceFiles/03.jpg";

    cv::Mat img = cv::imread(fileName);
    resizeImage(&img, a, false);
    cv::imshow("original", img);
    cv::waitKey();
    cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
    cv::blur(img, img, cv::Size(25,25));
    cv::threshold(img, img, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    cv::imshow("bw", img);
    cv::waitKey();




    cv::SimpleBlobDetector::Params params;

    params.filterByColor = true;
    params.blobColor = 255;

    params.filterByArea = false;
    params.filterByCircularity = false;
    params.filterByConvexity = false;
    params.filterByInertia = false;

    cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create(params);


//    detector->detect()
    std::vector<cv::KeyPoint> keypoints;
    detector->detect(img, keypoints);

    std::cout<<keypoints.

    // Draw detected blobs as red circles.
    // DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures the size of the circle corresponds to the size of blob
    cv::Mat im_with_keypoints;
    cv::drawKeypoints(img, keypoints, im_with_keypoints, cv::Scalar(0, 0, 255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    cv::imshow("keypoints", im_with_keypoints);
    cv::waitKey();




    /*
    ImageProcessing* ip = new ImageProcessing(fileName);
    ip->resizeImage(a, false);
    ip->rgbWBlur2bw(100);
    ip->displayImg(0);
    ip->HighLightBlobs();
    ip->displayImg(0);
    delete ip;
    
    /*
    ImageProcessing* imgProc = new ImageProcessing(fileName);
    cv::Mat* img;
    imgProc->resizeImage(1000, false);
    img = imgProc->getImage();
    cv::imshow("original", *img);
    cv::waitKey();

    cv::Mat aux;
    cv::cvtColor(*img, aux, cv::COLOR_BGR2GRAY);
    delete img;

    cv::blur(aux, *img, cv::Size(100, 100));
    aux.release();
    cv::threshold(*img, aux, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    delete img;
    img = &aux;
    cv::imshow("original", *img);
    cv::waitKey();
    imgProc->setImage(img);
    cv::imshow("original", *(imgProc->getImage()));
    cv::waitKey();
    cv::Mat* blobH = imgProc->HighLightBlobs();
    cv::imshow("Highlighted Blob", *blobH);
    cv::waitKey();

    /*






    cv::Mat imagem = cv::imread(fileName);
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

    cv::blur(gsimg, blurImg, cv::Size(100,100));
    aux = resizeImg(blurImg, widthWindow, heightWindow);
    cv::imshow("blurImg", aux);
    //cv::waitKey();
    aux.release();

    //blurImg = gsimg.clone();
    cv::threshold(blurImg, bwImg, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    aux = resizeImg(bwImg, widthWindow, heightWindow);
    cv::imshow("bwImg", aux);
    cv::waitKey();
    //aux.release();

    ImageProcessing imgprocs;
    imgprocs.setImage(&aux);
    //imgprocs.setImage(&bwImg);

    std::list<Blob*> blobs;
    blobs = imgprocs.findBlobs();
    while (!blobs.empty()) {
        Blob* blob = blobs.front();
        Blob::Pixel topLeftPixel = blob->getTopLeftPixel();
        Blob::Pixel bottomRightPixel = blob->getBottomRightPixel();

        std::cout << "new Blob ->" << blob->getPixelCounter() << std::endl;
        std::cout << "topLeftPixel:[" << topLeftPixel.row << "," << topLeftPixel.col << "]" << std::endl;
        std::cout << "bottomRightPixel:[" << bottomRightPixel.row << "," << bottomRightPixel.col << "]" << std::endl;
        blobs.pop_front();
        delete blob;
    }

    ImageProcessing* imp2 = new ImageProcessing();
    cv::Mat* im;
    im = imgprocs.HighLightBlobs();
    imp2->setImage(im);
    cv::imshow("a", *im);
    cv::waitKey();
    // imp2->resizeImage(a, false);

    //cv::imshow("asd", *(imp2->getImage()));
    //cv::waitKey();
    //img.release();
    delete imp2;


/*
    uint8_t** ui8img =  cvMat2Byte(bwImg);

    for (int i = 0; i < bwImg.rows; i++) {
        free(ui8img[i]);
    }
    free(ui8img);
    ui8img = NULL;

    imagem.release();
    gsimg.release();
    bwImg.release();
    blurImg.release();
    */

    //cv::destroyAllWindows();
    //system("pause");
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
