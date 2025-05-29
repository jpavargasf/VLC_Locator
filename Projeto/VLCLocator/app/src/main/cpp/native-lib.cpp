#include <jni.h>
#include <string>
#include <list>

#include "biblioteca_polinomio.c"
#include "matrix.c"
#include "Perspective_n_Point.c"


//funcao de teste
extern "C" JNIEXPORT jstring JNICALL
Java_com_example_vlclocator_CameraActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


int *copyImage(int *image, uint32_t width, uint32_t height){
    int *imageCopy = NULL;
    if(image != NULL && width > 0 && height > 0){
        uint32_t nPixels = width * height;
        uint32_t index = 0;

        imageCopy = (int*) malloc(nPixels * sizeof(int));

        do{
            imageCopy[index] = image[index];
            index++;
        }while(index < nPixels);
    }
    return imageCopy;
}


extern "C" JNIEXPORT jintArray JNICALL
Java_com_example_vlclocator_ImageProcessing_img2gray(
        JNIEnv* env,
        jobject /* this */,
        jintArray img,
        jint width,
        jint height){

    //aparentemente NULL significa que não interessa se é cópia ou não
    int* originalImage = env->GetIntArrayElements(img, NULL);

    uint32_t nPixels = width * height;
    int* grayImage = (int*) malloc(nPixels * sizeof(int));
    uint32_t i = 0;
    uint8_t r;
    uint8_t b;
    uint8_t g;

    uint8_t grayValue;

    //a para campo 0xFF 00 00 00
    //Representa a do ARGB, referente à transparência a opacidade (0 a 255)
    uint32_t a;


    for(; i < nPixels; i++){
        //opacidade
        a = (originalImage[i] & 0xFF000000);

        //cores
        r = (originalImage[i] & 0x00FF0000) >> 16;
        g = (originalImage[i] & 0x0000FF00) >> 8;
        b = (originalImage[i] & 0x000000FF);

        //mesmo método do matlab
        grayValue = 0.299 * r + 0.587 * g + 0.114 * b;

        //grayImage[i] = (grayValue << 16) | (grayValue << 8) | (grayValue);


        grayImage[i] = a | (grayValue << 16) | (grayValue << 8) | (grayValue);

    }


    //cria jintArray para passar para o java
    jintArray result = env->NewIntArray(nPixels);

    //define os valores de jintArray como grayImage
    env->SetIntArrayRegion(result, 0, nPixels, grayImage);

    //ReleaseIntArrayElements: Releases the native memory used by the original jintArray.
    env->ReleaseIntArrayElements(img, originalImage, 0);
    return result;
}


bool checkIndexInBounds(int32_t wIndex, int32_t hIndex, uint32_t width, uint32_t height){
    if(hIndex < 0 || hIndex >= height ||
        wIndex < 0 || wIndex >= width){
        return false;
    }
    return true;
}

void applyBlurFilter(int* result, int* img, int width, int height,
                     int widthStart, int widthEnd, int heightStart, int heightEnd,
                     int deltaFilterStart, int deltaFilterEnd){
    for(uint32_t h = heightStart; h < heightEnd; h++){
        for(uint32_t w = widthStart; w < widthEnd; w++){
            uint32_t indexImg = w + h * width;
            uint32_t filterResult = 0;
            uint32_t filterDenominator = 0;

            for(int32_t hf = h - deltaFilterStart; hf < h + deltaFilterEnd; hf++){
                for(int32_t wf = w - deltaFilterStart; wf < w + deltaFilterEnd; wf++){
                    if(checkIndexInBounds(wf,hf,width,height)){
                        int32_t sIndexImgFilter = wf + hf * width;
                        filterResult += img[sIndexImgFilter] & 0x000000FF;
                        filterDenominator++;
                    }
                }
            }
            filterResult = (filterResult / filterDenominator) & 0x000000FF;
            result[indexImg] = (img[indexImg] & 0xFF000000) | filterResult << 16 | filterResult << 8 | filterResult;
        }
    }
}

//Comentarios: funcao feita para que rode o mais rápido possível, por isso o código é escrito em
//5 partes separadas ao invés de uma só
//img deve estar em grayscale
extern "C" JNIEXPORT jintArray JNICALL
Java_com_example_vlclocator_ImageProcessing_blurImg(
        JNIEnv* env,
        jobject /* this */,
        jintArray img,
        jint width,
        jint height,
        jint filterOrder){

    //aparentemente NULL significa que não interessa se é cópia ou não
    int* originalImg = env->GetIntArrayElements(img, NULL);
    int* blurredImg;

    uint32_t nPixels = width * height;

    blurredImg = (int*)malloc(nPixels * sizeof(int));

    uint32_t filterResult;
    uint32_t filterDenominator = filterOrder * filterOrder;

    uint32_t indexImg;
    uint32_t indexImgFilter;

    uint32_t deltaFilterStart = filterOrder / 2;
    uint32_t deltaFilterEnd = deltaFilterStart;
    //verifica se filterOrder é par
    if((deltaFilterStart + deltaFilterEnd) == filterOrder){
        deltaFilterStart = deltaFilterStart - 1;
    }


    uint32_t filterStart;
    uint32_t filterEnd;
    //mais rápido fazer primeiro a filtragem da região em que o filtro inteiro age para não ter
    //muitos ifs

    //posso melhorar os fors para o pixel atual e fazer do mesmo jeito que o filtro
    // for mais intern o para width e for externo para height
    //não exclua o código abaixo, está funcionando, só por segurança
/*
    for(uint32_t w = deltaFilterStart; w < width - deltaFilterEnd; w++){
        for(uint32_t h = deltaFilterStart; h < height - deltaFilterEnd; h++){
            indexImg = w + h * width;
            filterResult = 0;

            //filterStart = indexImg - deltaFilterStart - deltaFilterStart * width;
            //parte *width contando pelas linhas
            //parte +1 contando pelas colunas
            filterStart = indexImg - deltaFilterStart * (width + 1);
            filterEnd = indexImg + deltaFilterEnd * (width + 1);

            for(indexImgFilter = filterStart; indexImgFilter <= filterEnd; indexImgFilter = indexImgFilter + width - filterOrder){
                for(uint32_t filterCount = 0; filterCount < filterOrder; filterCount++){
                    filterResult += blurredImg[indexImgFilter] & 0x000000FF;
                    indexImgFilter++;
                }
            }
            filterResult = (filterResult / filterDenominator) & 0x000000FF;
            blurredImg[indexImg] = (blurredImg[indexImg] & 0xFF000000) | filterResult << 16 | filterResult << 8 | filterResult;
        }
    }
*/
    for(indexImg = deltaFilterStart * (width + 1) ; indexImg < nPixels - deltaFilterEnd * (width + 1); indexImg = indexImg + filterOrder){
        for(uint32_t wCounter = 0; wCounter < width - filterOrder; wCounter++){
            //indexImg = w + h * width;
            filterResult = 0;

            //filterStart = indexImg - deltaFilterStart - deltaFilterStart * width;
            //parte *width contando pelas linhas
            //parte +1 contando pelas colunas
            filterStart = indexImg - deltaFilterStart * (width + 1);
            filterEnd = indexImg + deltaFilterEnd * (width + 1);

            for(indexImgFilter = filterStart; indexImgFilter <= filterEnd; indexImgFilter = indexImgFilter + width - filterOrder){
                for(uint32_t filterCount = 0; filterCount < filterOrder; filterCount++){
                    filterResult += originalImg[indexImgFilter] & 0x000000FF;
                    indexImgFilter++;
                }
            }
            filterResult = (filterResult / filterDenominator) & 0x000000FF;
            blurredImg[indexImg] = (originalImg[indexImg] & 0xFF000000) | filterResult << 16 | filterResult << 8 | filterResult;

            indexImg++;
        }
    }


    //parte em que o filtro não passa totalmente
    /*
     *                      2
     * --------------------------------------------
     *      |                           |
     *      |                           |
     *      |                           |
     *   3  |                           |   4
     *      |                           |
     *      |                           |
     *      |                           |
     * --------------------------------------------
     *                      1
     *
     */
    //parte inferior
    /*
    for(uint32_t h = height - deltaFilterEnd; h < height; h++){
        for(uint32_t w = 0; w < width; w++){
            indexImg = w + h * width;
            filterResult = 0;
            filterDenominator = 0;

            for(int32_t hf = h - deltaFilterStart; hf < h + deltaFilterEnd; hf++){
                for(int32_t wf = w - deltaFilterStart; wf < w + deltaFilterEnd; wf++){
                    if(checkIndexInBounds(wf,hf,width,height)){
                        int32_t sIndexImgFilter = wf + hf * width;
                        filterResult += blurredImg[sIndexImgFilter] & 0x000000FF;
                        filterDenominator++;
                    }
                }
            }
            filterResult = (filterResult / filterDenominator) & 0x000000FF;
            blurredImg[indexImg] = (blurredImg[indexImg] & 0xFF000000) | filterResult << 16 | filterResult << 8 | filterResult;
        }
    }
*/
    //parte superior
    applyBlurFilter(blurredImg, originalImg, width, height,
                    0, width, height - deltaFilterEnd, height,
                    deltaFilterStart, deltaFilterEnd);
    //parte inferior
    applyBlurFilter(blurredImg, originalImg, width, height,
                    0, width, 0, deltaFilterStart,
                    deltaFilterStart, deltaFilterEnd);
    //parte esquerda
    applyBlurFilter(blurredImg, originalImg, width, height,
                    0, deltaFilterStart, deltaFilterStart, height - deltaFilterEnd,
                    deltaFilterStart, deltaFilterEnd);
    //parte direita
    applyBlurFilter(blurredImg, originalImg, width, height,
                    width - deltaFilterEnd, width, deltaFilterStart, height - deltaFilterEnd,
                    deltaFilterStart, deltaFilterEnd);
    //parte superior
/*    for(uint32_t h = 0; h < deltaFilterStart; h++){
        for(uint32_t w = 0; w < width; w++){
            indexImg = w + h * width;
            filterResult = 0;
            filterDenominator = 0;

            for(int32_t hf = h - deltaFilterStart; hf < h + deltaFilterEnd; hf++){
                for(int32_t wf = w - deltaFilterStart; wf < w + deltaFilterEnd; wf++){
                    if(checkIndexInBounds(wf,hf,width,height)){
                        int32_t sIndexImgFilter = wf + hf * width;
                        filterResult += blurredImg[sIndexImgFilter] & 0x000000FF;
                        filterDenominator++;
                    }
                }
            }
            filterResult = (filterResult / filterDenominator) & 0x000000FF;
            blurredImg[indexImg] = (blurredImg[indexImg] & 0xFF000000) | filterResult << 16 | filterResult << 8 | filterResult;
        }
    }
*/
/*
    for(uint32_t w = 0; w < width; w++){
        for(uint32_t h = 0; h < height; h++){
            indexImg = w + h * width;
            for(int32_t wFilter =  )
        }




    }
*/

    //cria jintArray para passar para o java
    jintArray result = env->NewIntArray(nPixels);

    //define os valores de jintArray como grayImage
    env->SetIntArrayRegion(result, 0, nPixels, blurredImg);

    //ReleaseIntArrayElements: Releases the native memory used by the original jintArray.
    env->ReleaseIntArrayElements(img, originalImg, 0);
    return result;
}

//retorna o histograma de uma imagem em grayscale
uint32_t *histogram(int *img, uint32_t nPixels){

    uint32_t *hist = (uint32_t*)malloc(256 * sizeof(uint32_t));
    uint32_t i;
    //zera todos os valores
    for(i = 0; i < 256; i++){
        hist[i] = 0;
    }
    for(i = 0; i < nPixels; i++){
        hist[img[i] & 0x000000FF]++;
    }
    return hist;
}


//maximixar a funcao abaixo
//sb^2 = wb * wf * (ub - uf)^2
//b de background (0) e f de foreground (255)
//sendo inclusivo para o foreground
//ex:
//  hist = [9,6,4,5,8,4]
//  nPixels = 36 (soma do hist)
//  para level = 2 (comeca em 0)
//  wb = (9 + 6) / 36
//  wf = (4 + 5 + 8 + 4) / 36
//  ub = ((9 * 0) + (6 * 1))/(9 + 6)
//  sb2 = 2.44
uint8_t otsuLevel(uint32_t* hist, uint32_t nPixels){
    double wB;
    double wF;
    double uB;
    double uF;
    double sb2Atual;
    double sb2Max = 0;
    uint32_t level = 0;

    uint32_t nPixelsB;
    uint32_t nPixelsF;

    uint32_t sumMultB;
    uint32_t sumMultF;

    uint32_t i;
    uint32_t uTop[256];

    nPixelsB = 0;
    nPixelsF = nPixels;


    sumMultB = 0;
    sumMultF = 0;
    for(i = 0; i < 256; i++){
        uTop[i] = i * hist[i];
        sumMultF += uTop[i];
    }

    //comeca em 1 para evitar divisao por 0 quando i = 0 para o uB
    for(i = 1; i < 256; i++){

        sumMultF = sumMultF - uTop[i - 1];
        sumMultB = sumMultB + uTop[i - 1];

        nPixelsB = nPixelsB + hist[i - 1];
        nPixelsF = nPixelsF - hist[i - 1];

        wF = (double)nPixelsF / (double)nPixels;
        wB = (double)nPixelsB / (double)nPixels;
        if(wF > 0 && wB > 0){
            uF = (double)sumMultF / (double)nPixelsF;
            uB = (double)sumMultB / (double)nPixelsB;
            float aux = uB - uF;
            sb2Atual = wF * wB * (aux * aux);
            if(sb2Atual > sb2Max){
                sb2Max = sb2Atual;
                level = i;
            }
        }
    }
    return level;
}

/*
//Retorna array com o nivel (0) e numero de bits 1 (1)
//
//maximixar a funcao abaixo
//sb^2 = wb * wf * (ub - uf)^2
//b de background (0) e f de foreground (255)
//sendo inclusivo para o foreground
//ex:
//  hist = [9,6,4,5,8,4]
//  nPixels = 36 (soma do hist)
//  para level = 2 (comeca em 0)
//  wb = (9 + 6) / 36
//  wf = (4 + 5 + 8 + 4) / 36
//  ub = ((9 * 0) + (6 * 1))/(9 + 6)
//  sb2 = 2.44
uint32_t *otsuLevel(uint32_t* hist, uint32_t nPixels){
    uint32_t *result;
    double wB;
    double wF;
    double uB;
    double uF;
    double sb2Atual;
    double sb2Max = 0;
    uint32_t level = 0;
    uint32_t nPixelsFlevel = 0;

    uint32_t nPixelsB;
    uint32_t nPixelsF;

    uint32_t sumMultB;
    uint32_t sumMultF;

    uint32_t i;
    uint32_t uTop[256];

    nPixelsB = 0;
    nPixelsF = nPixels;


    sumMultB = 0;
    sumMultF = 0;
    for(i = 0; i < 256; i++){
        uTop[i] = i * hist[i];
        sumMultF += uTop[i];
    }

    //comeca em 1 para evitar divisao por 0 quando i = 0 para o uB
    for(i = 1; i < 256; i++){

        sumMultF = sumMultF - uTop[i - 1];
        sumMultB = sumMultB + uTop[i - 1];

        nPixelsB = nPixelsB + hist[i - 1];
        nPixelsF = nPixelsF - hist[i - 1];

        wF = (double)nPixelsF / (double)nPixels;
        wB = (double)nPixelsB / (double)nPixels;
        if(wF > 0 && wB > 0){
            uF = (double)sumMultF / (double)nPixelsF;
            uB = (double)sumMultB / (double)nPixelsB;
            float aux = uB - uF;
            sb2Atual = wF * wB * (aux * aux);
            if(sb2Atual > sb2Max){
                sb2Max = sb2Atual;
                level = i;
                nPixelsFlevel = nPixelsF;
            }
        }
    }

    result = (uint32_t*) malloc(2 * sizeof(uint32_t));
    result[0] = level;
    result[1] = nPixelsFlevel;
    //return level;
    return result;
}
*/

extern "C" JNIEXPORT jintArray JNICALL
Java_com_example_vlclocator_ImageProcessing_imgBinarize(
        JNIEnv* env,
        jobject /* this */,
        jintArray img,
        jint width,
        jint height){
    int* originalImage = env->GetIntArrayElements(img, NULL);

    uint32_t nPixels = width * height;
    int* bwImg = (int*) malloc(nPixels * sizeof(int));

    uint32_t * hist = histogram(originalImage, nPixels);
    uint8_t level = otsuLevel(hist, nPixels);
    //uint32_t* level_n = otsuLevel(hist, nPixels);
    //uint8_t level = (uint8_t) level_n[0];
    //int* nPixelsF = (int*) malloc(sizeof(int));
    //*nPixelsF = level_n[1];
    //free(level_n);
    //level_n = NULL;



    free(hist);
    hist = NULL;

    for(uint32_t i = 0; i < nPixels; i++){
        int gray = originalImage[i] & 0x000000FF;
        bwImg[i] = originalImage[i] & 0xFF000000;
        if(gray >= level){
            bwImg[i] = bwImg[i] | 0x00FFFFFF;
        }
    }

    //cria jintArray para passar para o java
    jintArray result = env->NewIntArray(nPixels);
    //jintArray result = env->NewIntArray(nPixels + 1);

    //define os valores de jintArray como grayImage
    env->SetIntArrayRegion(result, 0, nPixels, bwImg);
    //env->SetIntArrayRegion(result, nPixels, 1, nPixelsF);

    //ReleaseIntArrayElements: Releases the native memory used by the original jintArray.
    env->ReleaseIntArrayElements(img, originalImage, 0);
    return result;

}

//guarda apenas os extremos do retângulo que engloba o blob, porque não necessito dos valores de onde
//tem
class Blob{
    private:
        //std::list<uint32_t> mPixelList;
        //melhor utilizar H e W ao inves de index, porque um H maior pode ter index menor
        int32_t frequency;
        int32_t minW;
        int32_t minH;
        int32_t maxW;
        int32_t maxH;
    public:
        Blob(){
            frequency = -1;
            minW = -1;
            minH = -1;
            maxW = -1;
            maxW = -1;
        }

        ~Blob(){

        }

        uint8_t isEmpty(){
            return minW > 0;
        }

        void addPixel(int32_t w, int32_t h){
            if(minW == -1){
                minW = w;
                minH = h;
                maxW = w;
                maxH = h;
            }else{
                if(w < minW){
                    minW = w;
                }else if(w > maxW){
                    maxW = w;
                }

                if(h < minH){
                    minH = h;
                }else if(h > maxH){
                    maxH = h;
                }
            }
        }

        void setFrequency(int32_t f){
            frequency = f;
        }

        //se estiver vazio, todas as funcoes abaixo retornam -1
        int32_t getFrequency(){
            return frequency;
        }

        int32_t getMinW(){
            return minW;
        }
        int32_t getMinH(){
            return minH;
        }
        int32_t getMaxW(){
            return maxW;
        }
        int32_t getMaxH(){
            return maxH;
        }
};

//void drawLine(int* img, int width, int height, int )

//img - imagem
//width - largura da imagem
//height - altura da imagem
//w - numero da coluna do pixel iterado
//h - numero da linha do pixel iterado
//blob - endereco do blob
void recursiveFindBlob(int* img, int32_t width, int32_t height, int32_t w, int32_t h, Blob *blob){
    if(w < 0 || w >= width || h < 0 || h >= height){
        return;
    }
    int32_t indexImg = w + h * width;

    if((img[indexImg] & 0x000000FF) == 0x000000FF){
        blob->addPixel(w,h);
        img[indexImg] = img[indexImg] & 0xFF000000;

        recursiveFindBlob(img, width, height, w - 1, h, blob);
        recursiveFindBlob(img, width, height, w + 1, h, blob);
        recursiveFindBlob(img, width, height, w, h - 1, blob);
        recursiveFindBlob(img, width, height, w, h + 1, blob);

        recursiveFindBlob(img, width, height, w - 1, h - 1, blob);
        recursiveFindBlob(img, width, height, w + 1, h - 1, blob);
        recursiveFindBlob(img, width, height, w - 1, h + 1, blob);
        recursiveFindBlob(img, width, height, w + 1, h + 1, blob);
    }
}

//retorna int* contendo as coordenadas dos blobs
extern "C" JNIEXPORT jintArray JNICALL
Java_com_example_vlclocator_ImageProcessing_findBlobs(
        JNIEnv* env,
        jobject /* this */,
        jintArray img,
        jint width,
        jint height){
    int* bwImg = env->GetIntArrayElements(img, NULL);
    //int* bwImg = copyImage(originalImage, width, height);
    uint32_t nPixels = width * height;


    std::list<Blob*> blobList;
    std::list<Blob*>::iterator it;

    for(uint32_t i = 0; i < nPixels; i++){
        if((bwImg[i] & 0x000000FF) == 0x000000FF){
            Blob* blob = new Blob();
            recursiveFindBlob(bwImg, width, height, i % width, i / width, blob);
            blobList.push_back(blob);
/*
            //para impedir crashar
            //tá crashando porque está dando array out of bounds quando não há
            //alguma fonte luminosa em foco, causando muito 1
            if(blobList.size() > 50){

                it = blobList.begin();
                while(it != blobList.end()){
                    Blob *blob = (*it);
                    delete blob;
                    blob = NULL;
                    it = blobList.erase(it);
                }
                env->ReleaseIntArrayElements(img, bwImg, 0);
                return nullptr;
            }
            */
        }
    }

    //std::list<Blob*>::iterator it;
    //remove fake blobs

    it = blobList.begin();
    while(it != blobList.end()){
        Blob *innerBlob = (*it);
        int32_t minW = innerBlob->getMinW();
        int32_t maxW = innerBlob->getMaxW();
        int32_t minH = innerBlob->getMinH();
        int32_t maxH = innerBlob->getMaxH();

        //uint8_t erased = 0;

        std::list<Blob*>::iterator it2;
        it2 = blobList.begin();
        while(it2 != blobList.end()){

            if((*it) != (*it2)){
                //checa se it esta dentro de it2
                if((*it2)->getMinW() <= minW && (*it2)->getMaxW() >= maxW &&
                   (*it2)->getMinH() <= minH && (*it2)->getMaxH() >= maxH){
                    it = blobList.erase(it);
                    delete innerBlob;
                    innerBlob = NULL;
                    break;
                }
            }
            it2++;
        }
        if(innerBlob != NULL){
            it++;
        }
    }

    /*
    uint32_t corDelta = 0x00FFFFFF / blobList.size();
    uint32_t cor = corDelta;

    for(it = blobList.begin(); it != blobList.end(); it++){
        int32_t minW = (*it)->getMinW();
        int32_t maxW = (*it)->getMaxW();
        int32_t minH = (*it)->getMinH();
        int32_t maxH = (*it)->getMaxH();
        int32_t indexImg;
        for(indexImg = minW + minH * width; indexImg <= maxW + minH * width; indexImg++){
            bwImg[indexImg] = (bwImg[indexImg] & 0xFF000000) | cor;
        }
        for(indexImg = minW + minH * width; indexImg <= minW + maxH * width; indexImg += width){
            bwImg[indexImg] = (bwImg[indexImg] & 0xFF000000) | cor;
        }
        for(indexImg = maxW + minH * width; indexImg <= maxW + maxH * width; indexImg += width){
            bwImg[indexImg] = (bwImg[indexImg] & 0xFF000000) | cor;
        }
        for(indexImg = minW + maxH * width; indexImg <= maxW + maxH * width; indexImg++){
            bwImg[indexImg] = (bwImg[indexImg] & 0xFF000000) | cor;
        }
        cor = cor + corDelta;
        delete (*it);
    }
*/
    uint32_t nBlobs = blobList.size();
    uint32_t returnSize;
    int* returnArray;
    if(nBlobs == 0){
        env->ReleaseIntArrayElements(img, bwImg, 0);
        return nullptr;
    }
    returnSize = 4 * nBlobs;
    returnArray = (int*) malloc(returnSize * sizeof(int));
    uint32_t returnArrayIndex = 0;
    for(it = blobList.begin(); it != blobList.end(); it++){
        returnArray[returnArrayIndex++] = (*it)->getMinW();
        returnArray[returnArrayIndex++] = (*it)->getMaxW();
        returnArray[returnArrayIndex++] = (*it)->getMinH();
        returnArray[returnArrayIndex++] = (*it)->getMaxH();
    }



    //free(bwImg);
    //bwImg = NULL;

    /*
    std::list<Blob*>::iterator it;
    for(it = blobList.begin(); it != blobList.end(); it++){
        int32_t minW = (*it)->getMinW();
        int32_t maxW = (*it)->getMaxW();
        int32_t minH = (*it)->getMinH();
        int32_t maxH = (*it)->getMaxH();

        //isso irá desenhar um retangulo cheio
        for(int32_t w = minW; w <= maxW; w++){
            for(int32_t h = minH; h <= maxH; h++){
                int32_t indexImg = w + h * width;
                bwImg[indexImg] = (bwImg[indexImg] & 0xFF000000) | 0x00FFFFFF;
            }
        }
        delete (*it);
    }
*/
    //cria jintArray para passar para o java
    jintArray result = env->NewIntArray(returnSize);

    //define os valores de jintArray como grayImage
    env->SetIntArrayRegion(result, 0, returnSize, returnArray);

    //ReleaseIntArrayElements: Releases the native memory used by the original jintArray.
    env->ReleaseIntArrayElements(img, bwImg, 0);
    return result;

}


/*
extern "C" JNIEXPORT jintArray JNICALL
Java_com_example_vlclocator_ImageProcessing_findBlobs(
        JNIEnv* env,
        jobject,
        jintArray img,
        jint width,
        jint height){
    int* originalImage = env->GetIntArrayElements(img, NULL);
    int* bwImg = copyImage(originalImage, width, height);
    uint32_t nPixels = width * height;


    std::list<Blob*> blobList;

    for(uint32_t i = 0; i < nPixels; i++){
        if((bwImg[i] & 0x000000FF) == 0x000000FF){
            Blob* blob = new Blob();
            recursiveFindBlob(bwImg, width, height, i % width, i / width, blob);
            blobList.push_back(blob);
        }
    }

    std::list<Blob*>::iterator it;
    //remove fake blobs

    it = blobList.begin();
    while(it != blobList.end()){
        Blob *innerBlob = (*it);
        int32_t minW = innerBlob->getMinW();
        int32_t maxW = innerBlob->getMaxW();
        int32_t minH = innerBlob->getMinH();
        int32_t maxH = innerBlob->getMaxH();

        //uint8_t erased = 0;

        std::list<Blob*>::iterator it2;
        it2 = blobList.begin();
        while(it2 != blobList.end()){

            if((*it) != (*it2)){
                //checa se it esta dentro de it2
                if((*it2)->getMinW() <= minW && (*it2)->getMaxW() >= maxW &&
                   (*it2)->getMinH() <= minH && (*it2)->getMaxH() >= maxH){
                    it = blobList.erase(it);
                    delete innerBlob;
                    innerBlob = NULL;
                    break;
                }
            }
            it2++;
        }
        if(innerBlob != NULL){
            it++;
        }
    }

    uint32_t corDelta = 0x00FFFFFF / blobList.size();
    uint32_t cor = corDelta;

    for(it = blobList.begin(); it != blobList.end(); it++){
        int32_t minW = (*it)->getMinW();
        int32_t maxW = (*it)->getMaxW();
        int32_t minH = (*it)->getMinH();
        int32_t maxH = (*it)->getMaxH();
        int32_t indexImg;
        for(indexImg = minW + minH * width; indexImg <= maxW + minH * width; indexImg++){
            bwImg[indexImg] = (bwImg[indexImg] & 0xFF000000) | cor;
        }
        for(indexImg = minW + minH * width; indexImg <= minW + maxH * width; indexImg += width){
            bwImg[indexImg] = (bwImg[indexImg] & 0xFF000000) | cor;
        }
        for(indexImg = maxW + minH * width; indexImg <= maxW + maxH * width; indexImg += width){
            bwImg[indexImg] = (bwImg[indexImg] & 0xFF000000) | cor;
        }
        for(indexImg = minW + maxH * width; indexImg <= maxW + maxH * width; indexImg++){
            bwImg[indexImg] = (bwImg[indexImg] & 0xFF000000) | cor;
        }
        cor = cor + corDelta;
        delete (*it);
    }

    //free(bwImg);
    //bwImg = NULL;

    /*
    std::list<Blob*>::iterator it;
    for(it = blobList.begin(); it != blobList.end(); it++){
        int32_t minW = (*it)->getMinW();
        int32_t maxW = (*it)->getMaxW();
        int32_t minH = (*it)->getMinH();
        int32_t maxH = (*it)->getMaxH();

        //isso irá desenhar um retangulo cheio
        for(int32_t w = minW; w <= maxW; w++){
            for(int32_t h = minH; h <= maxH; h++){
                int32_t indexImg = w + h * width;
                bwImg[indexImg] = (bwImg[indexImg] & 0xFF000000) | 0x00FFFFFF;
            }
        }
        delete (*it);
    }
//*
    //cria jintArray para passar para o java
    jintArray result = env->NewIntArray(nPixels);

    //define os valores de jintArray como grayImage
    env->SetIntArrayRegion(result, 0, nPixels, bwImg);

    //ReleaseIntArrayElements: Releases the native memory used by the original jintArray.
    env->ReleaseIntArrayElements(img, originalImage, 0);
    return result;

}
*/

float frequencyFromArray(uint32_t* array, uint32_t nElem, double secPixelExposure, double multFactor){
    if(array == NULL || nElem == 0){
        return -1;
    }
    float frequency;

    uint32_t maxSeqOf[2] = {0,0};
    uint32_t actualSeq = 1;
    uint8_t seq = array[0]; // 0 se de 0 1 se de 1

    for(uint32_t i = 1; i < nElem; i++){
        if(seq == array[i]){//continua seq
            actualSeq++;
        }else{//checa se actualSeq é maior e troca para a proxima
            if(actualSeq > maxSeqOf[seq]){
                maxSeqOf[seq] = actualSeq;
            }
            //troca seq
            seq = array[i];
            actualSeq = 1;
        }
    }

    //ultima conferencia se actualSeq é maior
    if(actualSeq > maxSeqOf[seq]){
        maxSeqOf[seq] = actualSeq;
    }

    uint32_t maxSeq;
    if(maxSeqOf[0] > maxSeqOf[1]){
        maxSeq = maxSeqOf[0];
    }else{
        maxSeq = maxSeqOf[1];
    }

    frequency = (float) ((multFactor) / ((float) ((float)maxSeq * secPixelExposure)));

    return frequency;
}

//retorna o index da constelação referida a amostra, caso nao pertença a nenhum, retorna -1
int32_t* mapToConstellation(float* samples, uint32_t sizeSamples, float* constellation, uint32_t sizeConstellation, float maxError){
    if(samples == NULL || sizeSamples == 0 || constellation == NULL || sizeConstellation == 0){
        return NULL;
    }


    //ideia: ver qual a diferença da amostra para cada ponto da constelação e assignar a que tiver menor erro
    //inicializa matriz de erro
    float** errorMatrix = (float**) malloc(sizeSamples * sizeof(float*));
    for(uint32_t i = 0; i < sizeSamples; i++){
        errorMatrix[i] = (float*) malloc(sizeConstellation * sizeof(float));
    }

    //calcula o erro em módulo
    for(uint32_t sampleIndex = 0; sampleIndex < sizeSamples; sampleIndex++){
        for(uint32_t constellationIndex = 0; constellationIndex < sizeConstellation; constellationIndex++){
            errorMatrix[sampleIndex][constellationIndex] = samples[sampleIndex] - constellation[constellationIndex];
            if(errorMatrix[sampleIndex][constellationIndex] < 0){
                errorMatrix[sampleIndex][constellationIndex] *= -1;
            }
        }
    }


    //para cada item da constelação, escolher qual tem o menor erro e verificar se o mesmo não tem
    //um item o qual o erro é menor que este, daí mesmo que tal item já esteja ocupado com outra
    //amostra, não escolher
    //talvez usar lista?
    std::list<uint32_t> listOfAvailableIndexes;
    for(uint32_t i = 0; i < sizeSamples; i++){
        listOfAvailableIndexes.push_back(i);
    }

    int32_t* map = (int32_t*) malloc(sizeSamples * sizeof(int32_t));
    for(uint32_t i = 0; i < sizeSamples; i++){
        map[i] = -1;
    }

    for(uint32_t constellationIndex = 0; constellationIndex < sizeConstellation; constellationIndex++){

        std::list<uint32_t>::iterator it = listOfAvailableIndexes.begin();

        std::list<uint32_t>::iterator lowestErrorIterator = it;

        it++;
        while(it != listOfAvailableIndexes.end()){
            if(errorMatrix[(*it)][constellationIndex] < errorMatrix[(*lowestErrorIterator)][constellationIndex]){
                lowestErrorIterator = it;
            }
            it++;
        }

        if(errorMatrix[(*lowestErrorIterator)][constellationIndex] < maxError){
            uint8_t flagNotLowestError = 0;
            //checa se este nao tem erro menor em outros pontos da constelação
            for(uint32_t constIndex2 = 0; constIndex2 < sizeConstellation; constIndex2++){
                //nao checar se index e diferente, porque vaidar erro igual e nao farei nada com isso
                if(errorMatrix[(*lowestErrorIterator)][constIndex2] < errorMatrix[(*lowestErrorIterator)][constellationIndex]){
                    flagNotLowestError = 1;
                    break;
                }
            }
            if(!flagNotLowestError){
                map[(*lowestErrorIterator)] = constellationIndex;
                listOfAvailableIndexes.erase(lowestErrorIterator);
            }
        }
    }

    //free errorMatrix
    for(uint32_t i = 0; i < sizeSamples; i++){
        free(errorMatrix[i]);
    }
    free(errorMatrix);
    errorMatrix = NULL;

    //free listOfAvailableIndexes
    listOfAvailableIndexes.clear();

    return map;
}

int32_t* mapToConstellationOrdered(float* samples, uint32_t sizeSamples, float* constellation, uint32_t sizeConstellation){
    if(samples == NULL || sizeSamples == 0 || constellation == NULL || sizeConstellation == 0 || sizeSamples < sizeConstellation){
        return NULL;
    }


    if(sizeSamples == sizeConstellation){
        //ordenar samples
        int32_t *index_samples_ordered = (int32_t*) malloc(sizeSamples * sizeof(int32_t));

        for(int32_t i = 0; i < sizeSamples; i++){
            index_samples_ordered[i] = i;
        }

        for(uint32_t i = 0; i < sizeSamples; i++){
            for(uint32_t j = i + 1; j < sizeSamples; j++){
                if(samples[index_samples_ordered[j]] < samples[index_samples_ordered[i]]){
                    int32_t aux = index_samples_ordered[i];
                    index_samples_ordered[i] = index_samples_ordered[j];
                    index_samples_ordered[j] = aux;
                }
            }
        }
        int32_t *mapp = (int32_t*) malloc(sizeSamples * sizeof(int32_t));
        for(uint32_t i = 0; i < sizeSamples; i++){
            mapp[index_samples_ordered[i]] = i;
        }
        free(index_samples_ordered);
        return mapp;
    }



    int32_t* map = (int32_t*) malloc(sizeSamples * sizeof(int32_t));
    for(uint32_t i = 0; i < sizeSamples; i++){
        map[i] = -1;
    }

    for(uint32_t constellationIndex = 0; constellationIndex < sizeConstellation; constellationIndex++){
        float menorErro = 0;
        uint32_t indexMenorErro = 0;
        uint32_t sampleIndex = 0;
        while(map[sampleIndex] != -1){
            sampleIndex++;
        }
        indexMenorErro = sampleIndex;
        menorErro = samples[sampleIndex] - constellation[constellationIndex];
        if(menorErro < 0){
            menorErro = -menorErro;
        }
        sampleIndex++;
        while(sampleIndex < sizeSamples){
            if(map[sampleIndex] == -1){
                float erroAtual = samples[sampleIndex] - constellation[constellationIndex];
                if(erroAtual < 0){
                    erroAtual = -erroAtual;
                }
                if(erroAtual < menorErro){
                    menorErro = erroAtual;
                    indexMenorErro = sampleIndex;
                }
            }
            sampleIndex++;
        }
        map[indexMenorErro] = constellationIndex;

    }

    return map;
}

float* centerOfBlobs(int32_t* bloobCoordinates, uint32_t nBlobs){
    if(bloobCoordinates == NULL || nBlobs == 0){
        return NULL;
    }
    float *center = (float* ) malloc(2 * nBlobs * sizeof(float));
    for(uint32_t i = 0; i < nBlobs; i++){
        center[2 * i] = ((float)bloobCoordinates[4 * i] + (float)bloobCoordinates[4 * i + 1]) / 2;
        center[2 * i + 1] = ((float)bloobCoordinates[4 * i + 2] + (float)bloobCoordinates[4 * i + 3]) / 2;
    }
    return center;
}

//config
// x f1 f3 x
//DCA x x DCB
// x f2 f4 x

int32_t* mapToConstellationOrderedGeometric(float* samples, uint32_t sizeSamples, float* constellation, uint32_t sizeConstellation, int32_t* bloobCoordinates){
    if(samples == NULL || sizeSamples == 0 || constellation == NULL || sizeConstellation == 0 || sizeSamples < sizeConstellation || bloobCoordinates == NULL){
        return NULL;
    }


    if(sizeSamples == sizeConstellation){
        //ordenar samples
        int32_t *index_samples_ordered = (int32_t*) malloc(sizeSamples * sizeof(int32_t));

        for(int32_t i = 0; i < sizeSamples; i++){
            index_samples_ordered[i] = i;
        }

        for(uint32_t i = 0; i < sizeSamples; i++){
            for(uint32_t j = i + 1; j < sizeSamples; j++){
                if(samples[index_samples_ordered[j]] < samples[index_samples_ordered[i]]){
                    int32_t aux = index_samples_ordered[i];
                    index_samples_ordered[i] = index_samples_ordered[j];
                    index_samples_ordered[j] = aux;
                }
            }
        }

        //////////////////////////////////////////////////////////////////////
        //sinal DC
        float *center = centerOfBlobs(bloobCoordinates, sizeSamples);
        float **distance = (float**) malloc(2 * sizeof(float*));

        //index 0 e 1 de index_samples_ordered sao do sinal DC

        for(uint8_t i = 0; i < 2; i++){
            distance[i] = (float*) malloc(4 * sizeof(float));
            for(uint8_t j = 0; j < 4; j++) {
                float x = pow(center[2 * index_samples_ordered[i]] - center[2 * index_samples_ordered[j + 2]], 2);
                float y = pow(center[2 * index_samples_ordered[i] + 1] - center[2 * index_samples_ordered[j + 2] + 1], 2);
                distance[i][j] = sqrt(x + y);
            }
        }

        float **dab = (float**) malloc(2 * sizeof(float*));
        for(uint8_t i = 0; i < 2; i++){
            dab[i] = (float*) malloc(2 * sizeof(float));
            for(uint8_t j = 0; j < 2; j++){
                dab[i][j] = distance[i][2 * j] + distance[i][2 * j + 1];
            }
        }

        //escolher o menor de cada coluna
        //uint8_t dca;
        //uint8_t dcb;

        uint8_t dc;

        //escolher a solução que trará o menor erro
        if((dab[0][0] + dab[1][1]) < (dab[0][1] + dab[1][0])){
            dc = 0;
        }else{
            dc = 1;
        }
/*
        if(dab[0][0] < dab[1][0]){
            dca = 0;
            dcb = 1;
        }else{
            dca = 1;
            dcb = 0;
        }

        if((dab[0][0] < dab[1][0] && dab[0][1] < dab[1][1]) ||
                (dab[1][0] < dab[0][0] && dab[1][1] < dab[0][1])){
            //escolher a solução que trará o menor erro
        }
*/
        //

        if(dc){
            //inverter index_samples_ordered
            int32_t aux = index_samples_ordered[0];
            index_samples_ordered[0] = index_samples_ordered[1];
            index_samples_ordered[1] = aux;
        }


        free(dab[0]);
        free(dab[1]);
        free(dab);
        free(distance[0]);
        free(distance[1]);
        free(distance);
        free(center);


        ///////////////////////////////////////////////////////////////////////////
        int32_t *mapp = (int32_t*) malloc(sizeSamples * sizeof(int32_t));
        for(uint32_t i = 0; i < sizeSamples; i++){
            mapp[index_samples_ordered[i]] = i;
        }
        free(index_samples_ordered);
        return mapp;
    }



    int32_t* map = (int32_t*) malloc(sizeSamples * sizeof(int32_t));
    for(uint32_t i = 0; i < sizeSamples; i++){
        map[i] = -1;
    }

    for(uint32_t constellationIndex = 0; constellationIndex < sizeConstellation; constellationIndex++){

        if(constellation[constellationIndex] == 0){
            continue;
        }


        float menorErro = 0;
        uint32_t indexMenorErro = 0;
        uint32_t sampleIndex = 0;
        while(map[sampleIndex] != -1){
            sampleIndex++;
        }
        indexMenorErro = sampleIndex;
        menorErro = samples[sampleIndex] - constellation[constellationIndex];
        if(menorErro < 0){
            menorErro = -menorErro;
        }
        sampleIndex++;
        while(sampleIndex < sizeSamples){
            if(map[sampleIndex] == -1){
                float erroAtual = samples[sampleIndex] - constellation[constellationIndex];
                if(erroAtual < 0){
                    erroAtual = -erroAtual;
                }
                if(erroAtual < menorErro){
                    menorErro = erroAtual;
                    indexMenorErro = sampleIndex;
                }
            }
            sampleIndex++;
        }
        map[indexMenorErro] = constellationIndex;

    }

    //definir dentre os que sobraram quais são o sinal DC correto

    //sinal DC
    uint32_t n_sinal_dc = sizeSamples - 4;
    float *center = centerOfBlobs(bloobCoordinates, sizeSamples);
    float **distance = (float**) malloc(n_sinal_dc * sizeof(float*));

    //index 0 e 1 de index_samples_ordered sao do sinal DC

    uint32_t index = 0;
    for(uint32_t i = 0; i < sizeSamples; i++){
        if(map[i] == -1) {
            distance[index] = (float *) malloc(4 * sizeof(float));
            for (uint8_t j = 0; j < sizeSamples; j++) {
                if (map[j] != -1) {
                    float x = pow(center[2 * i] - center[2 * j], 2);
                    float y = pow(center[2 * i + 1] - center[2 * j + 1], 2);
                    distance[index][map[j] - 2] = sqrt(x + y);
                }
            }
            index++;
        }
        if(index == n_sinal_dc){
            break;
        }
    }

    float **dab = (float**) malloc(n_sinal_dc * sizeof(float*));
    for(uint8_t i = 0; i < n_sinal_dc; i++){
        dab[i] = (float*) malloc(2 * sizeof(float));
        for(uint8_t j = 0; j < 2; j++){
            dab[i][j] = distance[i][2 * j] + distance[i][2 * j + 1];
        }
    }

    uint32_t index1 = 0;
    uint32_t index2 = 1;
    float menor_erro = dab[index1][0] + dab[index2][1];
    for(uint32_t i = 0; i < n_sinal_dc; i++){
        for(uint32_t j = 0; j < n_sinal_dc; j++){
            if(i == j){
                continue;
            }
            float erro_atual = dab[i][0] + dab[j][1];
            if(erro_atual < menor_erro){
                index1 = i;
                index2 = j;
            }
        }
    }

    uint32_t counter = 0;
    for(uint32_t i = 0; i < sizeSamples; i++){
        if(map[i] == -1){
            if(counter == index1){
                map[i] = 0;
            }else if(counter == index2){
                map[i] = 1;
            }
            counter++;
        }
    }

    for(uint8_t i = 0; i < n_sinal_dc; i++){
        free(dab[i]);
        free(distance[i]);
    }
    free(dab);
    free(distance);
    free(center);

    return map;
}

//retorna int* contendo as coordenadas dos blobs
extern "C" JNIEXPORT jintArray JNICALL
Java_com_example_vlclocator_ImageProcessing_CheckFrequencies(
        JNIEnv* env,
        jobject /* this */,
        jintArray originalImg,
        jintArray grayScaleImg,
        jint width,
        jint height,
        jintArray blobCoordinates,
        jint nBlobs,
        jdouble pixelExposureTime,
        jdouble freqMultFactor){
    int* originalImage = env->GetIntArrayElements(originalImg, NULL);
    int* gsImage = env->GetIntArrayElements(grayScaleImg, NULL);
    int* blobCoords = env->GetIntArrayElements(blobCoordinates, NULL);
    uint32_t nPixels = width * height;


    float* frequencies = (float*) malloc(nBlobs * sizeof(float));

    uint32_t corDelta = 0x00FFFFFF / nBlobs;
    uint32_t cor = corDelta;

    uint32_t indexBlobCoords = 0;
    for(uint32_t i = 0; i < nBlobs; i++){
        int32_t minW = blobCoords[indexBlobCoords++];
        int32_t maxW = blobCoords[indexBlobCoords++];
        int32_t minH = blobCoords[indexBlobCoords++];
        int32_t maxH = blobCoords[indexBlobCoords++];
        int32_t indexImg;

        uint32_t nElem = (maxH - minH + 1);

        //depois troca esse malloc para ser apenas o maior dos nElem e nao fazer para todo blob
        uint32_t* blobFunc = (uint32_t*) malloc(nElem * sizeof(uint32_t));
        uint32_t indexBlobFunc = 0;
        uint32_t sum = 0;

        ///////////////////////////////////////////////////////////////////////////////////
        //INSERIR CHECAGEM DE FREQUÊNCIA AQUI OU FUNÇÃO
        for(indexImg = minW + minH * width; indexImg <= minW + maxH * width; indexImg += width){
            blobFunc[indexBlobFunc] = 0;
            for(uint32_t j = indexImg; j <= indexImg + maxW; j++){
                blobFunc[indexBlobFunc] += gsImage[j] & 0x000000FF;
            }
            sum += blobFunc[indexBlobFunc];
            indexBlobFunc++;
        }

        uint32_t threshold = sum / (2 * nElem);
        for(uint32_t j = 0; j < nElem; j++){
            if(blobFunc[j] >= threshold){
                blobFunc[j] = 1;
            }else{
                blobFunc[j] = 0;
            }
        }

        frequencies[i] = frequencyFromArray(blobFunc, nElem, pixelExposureTime, freqMultFactor);

        free(blobFunc);
        blobFunc = NULL;

/*
        //////////////////////////////////////////////////////////////////////////////////
        //CORES AO REDOR DO BLOB
        for(indexImg = minW + minH * width; indexImg <= maxW + minH * width; indexImg++){
            originalImage[indexImg] = (originalImage[indexImg] & 0xFF000000) | cor;
        }
        for(indexImg = minW + minH * width; indexImg <= minW + maxH * width; indexImg += width){
            originalImage[indexImg] = (originalImage[indexImg] & 0xFF000000) | cor;
        }
        for(indexImg = maxW + minH * width; indexImg <= maxW + maxH * width; indexImg += width){
            originalImage[indexImg] = (originalImage[indexImg] & 0xFF000000) | cor;
        }
        for(indexImg = minW + maxH * width; indexImg <= maxW + maxH * width; indexImg++){
            originalImage[indexImg] = (originalImage[indexImg] & 0xFF000000) | cor;
        }
        cor = cor + corDelta;*/
    }

    //determinar quais as frequencias estao mais próximas dos setados aqui
    float constellation[] = {1000,1500,2000,2500};
    int32_t* map = mapToConstellation(frequencies, nBlobs, constellation, 4, 250);
    //int32_t* map = mapToConstellation(frequencies, nBlobs, {1000,1500,2000,2500}, 4, 250);

    //red, green, blue, pink
    uint32_t colors[] = {0x00FC0303, 0x0003FC03, 0x000B03FC, 0x00FC03E3};

    for(uint32_t i = 0; i < nBlobs; i++){
        if(map[i] != -1){
            uint32_t index = 4 * i;
            int32_t minW = blobCoords[index + 0];
            int32_t maxW = blobCoords[index + 1];
            int32_t minH = blobCoords[index + 2];
            int32_t maxH = blobCoords[index + 3];
            int32_t indexImg;


            //CORES AO REDOR DO BLOB
            for(indexImg = minW + minH * width; indexImg <= maxW + minH * width; indexImg++){
                originalImage[indexImg] = (originalImage[indexImg] & 0xFF000000) | colors[map[i]];
            }
            for(indexImg = minW + minH * width; indexImg <= minW + maxH * width; indexImg += width){
                originalImage[indexImg] = (originalImage[indexImg] & 0xFF000000) | colors[map[i]];
            }
            for(indexImg = maxW + minH * width; indexImg <= maxW + maxH * width; indexImg += width){
                originalImage[indexImg] = (originalImage[indexImg] & 0xFF000000) | colors[map[i]];
            }
            for(indexImg = minW + maxH * width; indexImg <= maxW + maxH * width; indexImg++){
                originalImage[indexImg] = (originalImage[indexImg] & 0xFF000000) | colors[map[i]];
            }
        }
    }

    //cria jintArray para passar para o java
    jintArray result = env->NewIntArray(nPixels);

    //define os valores de jintArray como grayImage
    env->SetIntArrayRegion(result, 0, nPixels, originalImage);

    //ReleaseIntArrayElements: Releases the native memory used by the original jintArray.
    env->ReleaseIntArrayElements(originalImg, originalImage, 0);
    env->ReleaseIntArrayElements(grayScaleImg, gsImage, 0);
    env->ReleaseIntArrayElements(blobCoordinates, blobCoords, 0);
    return result;

}
/*
extern "C" JNIEXPORT jintArray JNICALL
Java_com_example_vlclocator_ImageProcessing_bwImgBoards(
        JNIEnv* env,
        jobject /* this *//*,
        jintArray img,
        jint width,
        jint height){
    int* originalImg = env->GetIntArrayElements(img, NULL);
    uint32_t nPixels = width * height;

    int* resultImg = (int*)malloc(nPixels * sizeof(int));

    uint32_t indexImg;
    //uint32_t indexImgFilter;

    for(indexImg = width + 1 ; indexImg < nPixels - width - 1; indexImg = indexImg + 3){
        for(uint32_t wCounter = 0; wCounter < width - 2; wCounter++){
            uint8_t pixelValue = originalImg[indexImg] & 0x000000FF;
            uint8_t hasZeroNeighbor = 0;
            if(pixelValue){
                if((originalImg[indexImg - width] & 0x000000FF) ==  0x00000000 | (originalImg[indexImg - width - 1] & 0x000000FF) ==  0x00000000 | (originalImg[indexImg - width + 1] & 0x000000FF) ==  0x00000000 |
                        (originalImg[indexImg + width] & 0x000000FF) == 0x00000000 | (originalImg[indexImg + width - 1] & 0x000000FF) == 0x00000000 | (originalImg[indexImg + width + 1] & 0x000000FF) == 0x00000000 |
                        (originalImg[indexImg - 1] & 0x000000FF) == 0x00000000 |
                        (originalImg[indexImg + 1] & 0x000000FF) == 0x00000000){
                    hasZeroNeighbor = 0xFF;
                }
            }
            resultImg[indexImg] = originalImg[indexImg] & 0xFF000000 | hasZeroNeighbor << 16 | hasZeroNeighbor << 8 | hasZeroNeighbor;
            //indexImg = w + h * width;
            indexImg++;
        }
    }
    //topo
    /*
    for(indexImg = 0; indexImg < width; indexImg++){
        resultImg[indexImg] = originalImg[indexImg];
    }
    //indexImg == width
    //lado esquerdo e lado direito

    for(;indexImg < nPixels - width; indexImg++){
        resultImg[indexImg] = originalImg[indexImg];//lado esquerdo
        indexImg += width - 1;
        resultImg[indexImg] = originalImg[indexImg];//lado direito
    }

    //indexImg == nPixels - width
    //ultima linha
    for(; indexImg < nPixels; indexImg++){
        resultImg[indexImg] = originalImg[indexImg];
    }
    *//*

    //BORDAS DA IMAGEM
    indexImg = 0;
    //topo
    do{
        resultImg[indexImg] = originalImg[indexImg];
        indexImg++;
    }while(indexImg < width);

    do{
        resultImg[indexImg] = originalImg[indexImg];
        indexImg += width;
        resultImg[indexImg -1] = originalImg[indexImg - 1];
    }while(indexImg < nPixels);

    do{
        indexImg--;
        resultImg[indexImg] = originalImg[indexImg];
    }while(indexImg > (nPixels - width));


    //cria jintArray para passar para o java
    jintArray result = env->NewIntArray(nPixels);

    //define os valores de jintArray como grayImage
    env->SetIntArrayRegion(result, 0, nPixels, resultImg);

    //ReleaseIntArrayElements: Releases the native memory used by the original jintArray.
    env->ReleaseIntArrayElements(img, originalImg, 0);
    return result;

}
*/

extern "C" JNIEXPORT jintArray JNICALL
Java_com_example_vlclocator_ImageProcessing_bwImgBoards(
        JNIEnv* env,
        jobject /* this */,
        jintArray img,
        jint width,
        jint height){
    int* originalImg = env->GetIntArrayElements(img, NULL);
    uint32_t nPixels = width * height;

    int* resultImg = (int*)malloc(nPixels * sizeof(int));

    for(uint32_t linha = 0; linha < height; linha++){
        for(uint32_t coluna = 0; coluna < width; coluna++){
            uint32_t indexImg = (linha * width) + coluna;
            if(linha == 0 || coluna == 0 || linha == height - 1 || coluna == width - 1){
                resultImg[indexImg] = originalImg[indexImg];
            }else{
                uint8_t hasZeroNeighbor = 0;
                if((originalImg[indexImg] & 0x00FFFFFF) == 0x00FFFFFF) {
                    for (uint32_t linha2 = linha - 1; linha2 <= linha + 1; linha2++) {
                        for (uint32_t coluna2 = coluna - 1; coluna2 <= coluna + 1; coluna2++) {
                            uint32_t indexImg2 = (linha2 * width) + coluna2;
                            if ((originalImg[indexImg2] & 0x00FFFFFF) == 0x00000000) {//estava 0x00FFFFFF
                                hasZeroNeighbor = 0xFF;
                                goto end_loop;
                            }
                        }
                    }
                }
                end_loop:
                resultImg[indexImg] = originalImg[indexImg] & 0xFF000000 | hasZeroNeighbor << 16 | hasZeroNeighbor << 8 | hasZeroNeighbor;
            }
        }
    }

    //cria jintArray para passar para o java
    jintArray result = env->NewIntArray(nPixels);

    //define os valores de jintArray como grayImage
    env->SetIntArrayRegion(result, 0, nPixels, resultImg);

    //ReleaseIntArrayElements: Releases the native memory used by the original jintArray.
    env->ReleaseIntArrayElements(img, originalImg, 0);
    return result;

}


//todas as etapas em uma só função e retorna imagem com frequencia desenhada
/*
extern "C" JNIEXPORT jintArray JNICALL
Java_com_example_vlclocator_ImageProcessing_mainImageProcessing(
        JNIEnv* env,
        jobject /* this *,
        jintArray img,
        jint width,
        jint height){
    int* originalImg = env->GetIntArrayElements(img, NULL);
    uint32_t nPixels = width * height;

    uint32_t i;

    int* grayScaleImage = (int*) malloc(nPixels * sizeof(int));

    uint32_t* imgHistogram = (uint32_t *) malloc(256 * sizeof(uint32_t));
    for(i = 0; i < 256; i++){
        imgHistogram[i] = 0;
    }

    for(; i < nPixels; i++){
        //opacidade
        uint32_t a = (originalImg[i] & 0xFF000000);

        //cores
        uint32_t r = (originalImg[i] & 0x00FF0000) >> 16;
        uint32_t g = (originalImg[i] & 0x0000FF00) >> 8;
        uint32_t b = (originalImg[i] & 0x000000FF);

        //mesmo método do matlab
        uint32_t grayValue = 0.299 * r + 0.587 * g + 0.114 * b;

        //grayImage[i] = (grayValue << 16) | (grayValue << 8) | (grayValue);
        //necessário incluir o alpha
        grayScaleImage[i] = a | (grayValue << 16) | (grayValue << 8) | (grayValue);

    }

    //blurImg


    //cria jintArray para passar para o java
    jintArray result = env->NewIntArray(nPixels);

    //define os valores de jintArray como grayImage
    env->SetIntArrayRegion(result, 0, nPixels, resultImg);

    //ReleaseIntArrayElements: Releases the native memory used by the original jintArray.
    env->ReleaseIntArrayElements(img, originalImg, 0);
    return result;

}*/

////DILATAÇÃO

extern "C" JNIEXPORT jintArray JNICALL
Java_com_example_vlclocator_ImageProcessing_bwDilatation(
        JNIEnv* env,
        jobject /* this */,
        jintArray img,
        jint width,
        jint height,
        jint filterOrder,
        jint widthOrder){
    int* originalImg = env->GetIntArrayElements(img, NULL);
    uint32_t nPixels = width * height;

    int* resultImg = (int*)malloc(nPixels * sizeof(int));

    //dFS + pixel + dFE = fO
    uint32_t deltaFilterStart = filterOrder / 2;
    uint32_t deltaFilterEnd = deltaFilterStart;
    if(deltaFilterStart + deltaFilterEnd == filterOrder){
        deltaFilterStart--;
    }

    uint32_t widthFilterStart = widthOrder / 2;
    uint32_t widthFilterEnd = widthFilterStart;
    if(widthFilterStart + widthFilterEnd == widthOrder){
        widthFilterStart--;
    }



    uint32_t indexImg;
    uint32_t filterIndex;
    //uint32_t indexImgFilter;

    for(indexImg = 0; indexImg < nPixels; indexImg++){
        resultImg[indexImg] = originalImg[indexImg];
    }

    indexImg = 0;
    for(uint32_t h = 0; h < height; h++){
        for(uint32_t w = 0; w < width; w++){
            if(originalImg[indexImg] & 0x00FFFFFF == 0x00FFFFFF){
                for(int32_t fH = h - deltaFilterStart; fH < h + deltaFilterEnd; fH++){
                    for(int32_t fW = w - widthFilterStart; fW < w + widthFilterEnd; fW++){
                        if(fH > 0 && fH < height && fW > 0 && fW < width){
                            filterIndex = fW + fH * width;
                            resultImg[filterIndex] = originalImg[indexImg];
                        }
                    }
                }
            }
            indexImg++;
        }
    }
    //abaixo está sem widthOrder
/*
    for(indexImg = deltaFilterStart * width ; indexImg < nPixels - (deltaFilterEnd * width); indexImg++){

        //indexImg = w + h * width;
        if(originalImg[indexImg] & 0x00FFFFFF == 0x00FFFFFF){
            for(filterIndex = indexImg - (deltaFilterStart * width); filterIndex < indexImg + deltaFilterEnd * width; filterIndex += width){
                resultImg[filterIndex] = originalImg[indexImg];
            }
        }

    }

    uint32_t fH, fW;
    //topo
    indexImg = 0;
    for(fH = 0; fH <= deltaFilterStart; fH++){
        for(fW = 0; fW < width; fW++){
            if(originalImg[indexImg] & 0x00FFFFFF == 0x00FFFFFF){
                for(filterIndex = indexImg - (fH * width); filterIndex < indexImg + deltaFilterEnd * width; filterIndex += width){
                    resultImg[filterIndex] = originalImg[indexImg];
                }
            }
            indexImg++;
        }
    }

    //bottom
    indexImg = nPixels - (deltaFilterEnd * width);
    for(fH = 0; fH <= deltaFilterEnd; fH++){
        for(fW = 0; fW < width; fW++){
            if(originalImg[indexImg] & 0x00FFFFFF == 0x00FFFFFF){
                for(filterIndex = indexImg - (deltaFilterStart * width); filterIndex < indexImg + (deltaFilterEnd - fH) * width; filterIndex += width){
                    resultImg[filterIndex] = originalImg[indexImg];
                }
            }
            indexImg++;
        }
    }
*/
    //cria jintArray para passar para o java
    jintArray result = env->NewIntArray(nPixels);

    //define os valores de jintArray como grayImage
    env->SetIntArrayRegion(result, 0, nPixels, resultImg);

    //ReleaseIntArrayElements: Releases the native memory used by the original jintArray.
    env->ReleaseIntArrayElements(img, originalImg, 0);
    return result;

}



float frequencyFromArrayV2(uint8_t* array, uint32_t nElem, double secPixelExposure, double multFactor){
    if(array == NULL || nElem == 0){
        return -1;
    }
    float frequency;

    uint32_t maxSeq;
    uint32_t actualSeq;
    uint8_t seq; // 0 se de 0 1 se de 1

    uint32_t index = 0;
    uint32_t maxIndex = nElem - 1;
    //elimina 0 do inicio
    do{
        if(array[index] == 0){
            index++;
        }else{
            break;
        }
    }while(index < nElem);

    if(index == nElem){
        return 0;
    }
    //elimina 0 do final
    do{
        if(array[maxIndex] == 0){
            maxIndex--;
        }else{
            break;
        }
    }while(maxIndex > index);


    seq = array[index];
    actualSeq = 1;
    maxSeq = actualSeq;
    index++;

    while(index <= maxIndex){
        if(seq == array[index]){
            actualSeq++;
        }else{
            if(actualSeq > maxSeq){
                maxSeq = actualSeq;
            }
            seq = array[index];
            actualSeq = 1;
        }
        index++;
    }
    if(actualSeq > maxSeq){
        maxSeq = actualSeq;
    }

    frequency = (float) ((multFactor) / ((float) ((float)maxSeq * secPixelExposure)));

    return frequency;
}

//retorna int* contendo as coordenadas dos blobs
extern "C" JNIEXPORT jintArray JNICALL
Java_com_example_vlclocator_ImageProcessing_CheckFrequenciesv2(
        JNIEnv* env,
        jobject /* this */,
        jintArray originalImg,
        jintArray bwImg,
        jint width,
        jint height,
        jintArray blobCoordinates,
        jint nBlobs,
        jdouble pixelExposureTime,
        jdouble freqMultFactor){
    int* originalImage = env->GetIntArrayElements(originalImg, NULL);
    int* bwImage = env->GetIntArrayElements(bwImg, NULL);
    int* blobCoords = env->GetIntArrayElements(blobCoordinates, NULL);
    uint32_t nPixels = width * height;


    float* frequencies = (float*) malloc(nBlobs * sizeof(float));

    uint32_t corDelta = 0x00FFFFFF / nBlobs;
    //uint32_t cor = corDelta;

    uint32_t indexBlobCoords = 0;
    for(uint32_t i = 0; i < nBlobs; i++){
        int32_t minW = blobCoords[indexBlobCoords++];
        int32_t maxW = blobCoords[indexBlobCoords++];
        int32_t minH = blobCoords[indexBlobCoords++];
        int32_t maxH = blobCoords[indexBlobCoords++];
        int32_t indexImg;

        uint32_t nElem = (maxH - minH + 1);

        //depois troca esse malloc para ser apenas o maior dos nElem e nao fazer para todo blob
        uint8_t* blobFunc = (uint8_t*) malloc(nElem * sizeof(uint8_t));
        uint32_t indexBlobFunc = 0;
        uint32_t sum = 0;
/*
        ///////////////////////////////////////////////////////////////////////////////////
        //INSERIR CHECAGEM DE FREQUÊNCIA AQUI OU FUNÇÃO
        for(indexImg = minW + minH * width; indexImg <= minW + maxH * width; indexImg += width){
            blobFunc[indexBlobFunc] = 0;
            for(uint32_t j = indexImg; j <= indexImg + (maxW - minW); j++){
                //if(bwImage[indexImg] & 0x00FFFFFF == 0x00FFFFFF){
                if(bwImage[j] & 0x00FFFFFF == 0x00FFFFFF){
                    blobFunc[indexBlobFunc] = 1;
                    break;
                }
            }
            indexBlobFunc++;
        }
*/
        for(uint32_t i = minH; i <= maxH; i++){
            blobFunc[indexBlobFunc] = 0;
            for(uint32_t j = minW; j <= maxW; j++){
                if(bwImage[i * width + j] & 0x00FFFFFF == 0x00FFFFFF){
                    blobFunc[indexBlobFunc] = 1;
                    break;
                }
            }
            indexBlobFunc++;
        }




        frequencies[i] = frequencyFromArrayV2(blobFunc, nElem, pixelExposureTime, freqMultFactor);


        free(blobFunc);
        blobFunc = NULL;

/*
        //////////////////////////////////////////////////////////////////////////////////
        //CORES AO REDOR DO BLOB
        for(indexImg = minW + minH * width; indexImg <= maxW + minH * width; indexImg++){
            originalImage[indexImg] = (originalImage[indexImg] & 0xFF000000) | cor;
        }
        for(indexImg = minW + minH * width; indexImg <= minW + maxH * width; indexImg += width){
            originalImage[indexImg] = (originalImage[indexImg] & 0xFF000000) | cor;
        }
        for(indexImg = maxW + minH * width; indexImg <= maxW + maxH * width; indexImg += width){
            originalImage[indexImg] = (originalImage[indexImg] & 0xFF000000) | cor;
        }
        for(indexImg = minW + maxH * width; indexImg <= maxW + maxH * width; indexImg++){
            originalImage[indexImg] = (originalImage[indexImg] & 0xFF000000) | cor;
        }
        cor = cor + corDelta;*/
    }

    //determinar quais as frequencias estao mais próximas dos setados aqui
    float constellation[] = {1000,1500,2000,2500};
    //int32_t* map = mapToConstellation(frequencies, nBlobs, constellation, 4, 250);
    //int32_t* map = mapToConstellation(frequencies, nBlobs, {1000,1500,2000,2500}, 4, 250);

    int32_t* map = mapToConstellationOrdered(frequencies, nBlobs, constellation, 4);


    //red, green, blue, pink
    uint32_t colors[] = {0x00FC0303, 0x0003FC03, 0x000B03FC, 0x00FC03E3};

    for(uint32_t i = 0; i < nBlobs; i++){
        if(map[i] != -1){
            uint32_t index = 4 * i;
            int32_t minW = blobCoords[index + 0];
            int32_t maxW = blobCoords[index + 1];
            int32_t minH = blobCoords[index + 2];
            int32_t maxH = blobCoords[index + 3];
            int32_t indexImg;
            int32_t mapa = map[i];


            //CORES AO REDOR DO BLOB
            for(indexImg = minW + minH * width; indexImg <= maxW + minH * width; indexImg++){
                originalImage[indexImg] = (originalImage[indexImg] & 0xFF000000) | colors[map[i]];
            }
            for(indexImg = minW + minH * width; indexImg <= minW + maxH * width; indexImg += width){
                originalImage[indexImg] = (originalImage[indexImg] & 0xFF000000) | colors[map[i]];
            }
            for(indexImg = maxW + minH * width; indexImg <= maxW + maxH * width; indexImg += width){
                originalImage[indexImg] = (originalImage[indexImg] & 0xFF000000) | colors[map[i]];
            }
            for(indexImg = minW + maxH * width; indexImg <= maxW + maxH * width; indexImg++){
                originalImage[indexImg] = (originalImage[indexImg] & 0xFF000000) | colors[map[i]];
            }
        }
    }

    //cria jintArray para passar para o java
    jintArray result = env->NewIntArray(nPixels + nBlobs);

    //define os valores de jintArray como grayImage
    env->SetIntArrayRegion(result, 0, nPixels, originalImage);

    //mapeamento
    env->SetIntArrayRegion(result, nPixels, nBlobs, map);

    //ReleaseIntArrayElements: Releases the native memory used by the original jintArray.
    env->ReleaseIntArrayElements(originalImg, originalImage, 0);
    env->ReleaseIntArrayElements(bwImg, bwImage, 0);
    env->ReleaseIntArrayElements(blobCoordinates, blobCoords, 0);
    return result;

}



//retorna int* contendo as coordenadas dos blobs
extern "C" JNIEXPORT jintArray JNICALL
Java_com_example_vlclocator_ImageProcessing_CheckFrequenciesv3(
        JNIEnv* env,
        jobject /* this */,
        jintArray originalImg,
        jintArray bwImg,
        jint width,
        jint height,
        jintArray blobCoordinates,
        jint nBlobs,
        jdouble pixelExposureTime,
        jdouble freqMultFactor){
    int* originalImage = env->GetIntArrayElements(originalImg, NULL);
    int* bwImage = env->GetIntArrayElements(bwImg, NULL);
    int* blobCoords = env->GetIntArrayElements(blobCoordinates, NULL);
    uint32_t nPixels = width * height;


    float* frequencies = (float*) malloc(nBlobs * sizeof(float));

    uint32_t corDelta = 0x00FFFFFF / nBlobs;
    //uint32_t cor = corDelta;

    uint32_t indexBlobCoords = 0;
    for(uint32_t i = 0; i < nBlobs; i++){
        int32_t minW = blobCoords[indexBlobCoords++];
        int32_t maxW = blobCoords[indexBlobCoords++];
        int32_t minH = blobCoords[indexBlobCoords++];
        int32_t maxH = blobCoords[indexBlobCoords++];
        int32_t indexImg;

        uint32_t nElem = (maxH - minH + 1);

        //depois troca esse malloc para ser apenas o maior dos nElem e nao fazer para todo blob
        uint8_t* blobFunc = (uint8_t*) malloc(nElem * sizeof(uint8_t));
        uint32_t indexBlobFunc = 0;
        uint32_t sum = 0;
/*
        ///////////////////////////////////////////////////////////////////////////////////
        //INSERIR CHECAGEM DE FREQUÊNCIA AQUI OU FUNÇÃO
        for(indexImg = minW + minH * width; indexImg <= minW + maxH * width; indexImg += width){
            blobFunc[indexBlobFunc] = 0;
            for(uint32_t j = indexImg; j <= indexImg + (maxW - minW); j++){
                //if(bwImage[indexImg] & 0x00FFFFFF == 0x00FFFFFF){
                if(bwImage[j] & 0x00FFFFFF == 0x00FFFFFF){
                    blobFunc[indexBlobFunc] = 1;
                    break;
                }
            }
            indexBlobFunc++;
        }
*/
        for(uint32_t i = minH; i <= maxH; i++){
            blobFunc[indexBlobFunc] = 0;
            for(uint32_t j = minW; j <= maxW; j++){
                if(bwImage[i * width + j] & 0x00FFFFFF == 0x00FFFFFF){
                    blobFunc[indexBlobFunc] = 1;
                    break;
                }
            }
            indexBlobFunc++;
        }




        frequencies[i] = frequencyFromArrayV2(blobFunc, nElem, pixelExposureTime, freqMultFactor);


        free(blobFunc);
        blobFunc = NULL;

/*
        //////////////////////////////////////////////////////////////////////////////////
        //CORES AO REDOR DO BLOB
        for(indexImg = minW + minH * width; indexImg <= maxW + minH * width; indexImg++){
            originalImage[indexImg] = (originalImage[indexImg] & 0xFF000000) | cor;
        }
        for(indexImg = minW + minH * width; indexImg <= minW + maxH * width; indexImg += width){
            originalImage[indexImg] = (originalImage[indexImg] & 0xFF000000) | cor;
        }
        for(indexImg = maxW + minH * width; indexImg <= maxW + maxH * width; indexImg += width){
            originalImage[indexImg] = (originalImage[indexImg] & 0xFF000000) | cor;
        }
        for(indexImg = minW + maxH * width; indexImg <= maxW + maxH * width; indexImg++){
            originalImage[indexImg] = (originalImage[indexImg] & 0xFF000000) | cor;
        }
        cor = cor + corDelta;*/
    }

    //determinar quais as frequencias estao mais próximas dos setados aqui
    float constellation[] = {0, 0,1000,1500,2000,2500};
    //int32_t* map = mapToConstellation(frequencies, nBlobs, constellation, 4, 250);
    //int32_t* map = mapToConstellation(frequencies, nBlobs, {1000,1500,2000,2500}, 4, 250);

    //int32_t* map = mapToConstellationOrdered(frequencies, nBlobs, constellation, 4);
    int32_t* map = mapToConstellationOrderedGeometric(frequencies, nBlobs, constellation, 6, blobCoords);


    //white, yellow, gray, red, green, blue, pink
    uint32_t colors[] = {0x00FFFFFF, 0x00FFFF00, 0x00FC0303, 0x0003FC03, 0x000B03FC, 0x00FC03E3};

    for(uint32_t i = 0; i < nBlobs; i++){
        if(map[i] != -1){
            uint32_t index = 4 * i;
            int32_t minW = blobCoords[index + 0];
            int32_t maxW = blobCoords[index + 1];
            int32_t minH = blobCoords[index + 2];
            int32_t maxH = blobCoords[index + 3];
            int32_t indexImg;
            int32_t mapa = map[i];


            //CORES AO REDOR DO BLOB
            for(indexImg = minW + minH * width; indexImg <= maxW + minH * width; indexImg++){
                originalImage[indexImg] = (originalImage[indexImg] & 0xFF000000) | colors[map[i]];
            }
            for(indexImg = minW + minH * width; indexImg <= minW + maxH * width; indexImg += width){
                originalImage[indexImg] = (originalImage[indexImg] & 0xFF000000) | colors[map[i]];
            }
            for(indexImg = maxW + minH * width; indexImg <= maxW + maxH * width; indexImg += width){
                originalImage[indexImg] = (originalImage[indexImg] & 0xFF000000) | colors[map[i]];
            }
            for(indexImg = minW + maxH * width; indexImg <= maxW + maxH * width; indexImg++){
                originalImage[indexImg] = (originalImage[indexImg] & 0xFF000000) | colors[map[i]];
            }
        }
    }

    //cria jintArray para passar para o java
    jintArray result = env->NewIntArray(nPixels + nBlobs);

    //define os valores de jintArray como grayImage
    env->SetIntArrayRegion(result, 0, nPixels, originalImage);

    //mapeamento
    env->SetIntArrayRegion(result, nPixels, nBlobs, map);

    //ReleaseIntArrayElements: Releases the native memory used by the original jintArray.
    env->ReleaseIntArrayElements(originalImg, originalImage, 0);
    env->ReleaseIntArrayElements(bwImg, bwImage, 0);
    env->ReleaseIntArrayElements(blobCoordinates, blobCoords, 0);
    return result;

}




////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////PNP/////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/*
extern "C" JNIEXPORT jdoubleArray JNICALL
Java_com_example_vlclocator_ImageProcessing_p4pJNI(
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



extern "C" JNIEXPORT jdoubleArray JNICALL
Java_com_example_vlclocator_ImageProcessing_p4pJNI(
        JNIEnv* env,
        jobject /* this */,
        jdoubleArray K_array,
        jdoubleArray rx_array,
        jintArray sx_array) {

    //adquire os vetores do java
    jdouble *rx_jdouble = env->GetDoubleArrayElements(rx_array, NULL);
    jdouble *K_jdouble = env->GetDoubleArrayElements(K_array, NULL);

    jint *sx_jint = env->GetIntArrayElements(sx_array, NULL);

    double **rx = (double**) malloc(4 * sizeof(double*));
    double **K = (double**) malloc(3 * sizeof(double*));
    uint32_t **sx = (uint32_t**) malloc(3 * sizeof(uint32_t*));
    for(uint8_t i = 0; i < 4; i++){
        rx[i] = (double*) malloc(4 * sizeof(double));
        if(i < 3){
            K[i] = (double*) malloc(3 * sizeof(double));
            sx[i] = (uint32_t*) malloc(4 * sizeof(uint32_t));
        }
        //inicializar os elementos
        for(uint8_t j = 0; j < 4; j++){
            rx[i][j] = rx_jdouble[4 * i + j];
            if(i < 3){
                sx[i][j] = sx_jint[4 * i + j];
                if(j < 3){
                    K[i][j] = K_jdouble[3 * i + j];
                }
            }
        }

    }

    double ***Xo_R = p4p_grunert_gauss_newton(K, rx, sx);

    double *Xo = NULL;
    if(Xo_R != NULL){
        if(Xo_R[0] != NULL){
            Xo = (double*) malloc(3 * sizeof(double));
            for(uint8_t i = 0; i < 3; i++){
                Xo[i] = Xo_R[0][i][0];
            }
        }
        matrix_free(Xo_R[0], 3);
        matrix_free(Xo_R[1], 3);
        free(Xo_R);
    }



    matrix_free(rx, 4);
    matrix_free(K, 3);
    for(uint8_t i = 0; i < 3; i++){
        free(sx[i]);
    }
    free(sx);


    if(Xo == NULL){
        return NULL;
    }
    //cria jintArray para passar para o java
    jdoubleArray result = env->NewDoubleArray(3);

    //define os valores de jintArray como grayImage
    env->SetDoubleArrayRegion(result, 0, 3, Xo);

    //ReleaseIntArrayElements: Releases the native memory used by the original jintArray.
    env->ReleaseIntArrayElements(sx_array, sx_jint, 0);

    env->ReleaseDoubleArrayElements(K_array, K_jdouble, 0);
    env->ReleaseDoubleArrayElements(rx_array, rx_jdouble, 0);


    return result;
}

extern "C" JNIEXPORT jdoubleArray JNICALL
Java_com_example_vlclocator_ImageProcessing_p4pJNIXoR(
        JNIEnv* env,
        jobject /* this */,
        jdoubleArray K_array,
        jdoubleArray rx_array,
        jintArray sx_array) {

    //adquire os vetores do java
    jdouble *rx_jdouble = env->GetDoubleArrayElements(rx_array, NULL);
    jdouble *K_jdouble = env->GetDoubleArrayElements(K_array, NULL);

    jint *sx_jint = env->GetIntArrayElements(sx_array, NULL);

    double **rx = (double**) malloc(4 * sizeof(double*));
    double **K = (double**) malloc(3 * sizeof(double*));
    uint32_t **sx = (uint32_t**) malloc(3 * sizeof(uint32_t*));
    for(uint8_t i = 0; i < 4; i++){
        rx[i] = (double*) malloc(4 * sizeof(double));
        if(i < 3){
            K[i] = (double*) malloc(3 * sizeof(double));
            sx[i] = (uint32_t*) malloc(4 * sizeof(uint32_t));
        }
        //inicializar os elementos
        for(uint8_t j = 0; j < 4; j++){
            rx[i][j] = rx_jdouble[4 * i + j];
            if(i < 3){
                sx[i][j] = sx_jint[4 * i + j];
                if(j < 3){
                    K[i][j] = K_jdouble[3 * i + j];
                }
            }
        }

    }

    double ***Xo_R = p4p_grunert_gauss_newton(K, rx, sx);

    double *XoR = NULL;
    if(Xo_R != NULL){
        if(Xo_R[0] != NULL){
            XoR = (double*) malloc(12 * sizeof(double));
            for(uint8_t i = 0; i < 3; i++){
                XoR[i] = Xo_R[0][i][0];
                for(uint8_t j = 0; j < 3; j++){
                    XoR[3 + 3 * i + j] = -Xo_R[1][i][j];//ele da R com sinal errado
                }
            }
        }
        matrix_free(Xo_R[0], 3);
        matrix_free(Xo_R[1], 3);
        free(Xo_R);
    }



    matrix_free(rx, 4);
    matrix_free(K, 3);
    for(uint8_t i = 0; i < 3; i++){
        free(sx[i]);
    }
    free(sx);


    if(XoR == NULL){
        return NULL;
    }
    //cria jintArray para passar para o java
    jdoubleArray result = env->NewDoubleArray(12);

    //define os valores de jintArray como grayImage
    env->SetDoubleArrayRegion(result, 0, 12, XoR);

    //ReleaseIntArrayElements: Releases the native memory used by the original jintArray.
    env->ReleaseIntArrayElements(sx_array, sx_jint, 0);

    env->ReleaseDoubleArrayElements(K_array, K_jdouble, 0);
    env->ReleaseDoubleArrayElements(rx_array, rx_jdouble, 0);


    return result;
}

#include <string.h>
//para converter os dados para o formato correto
//vlc	dddddmmm maaaaaaa aaaaaaah hhhhmmmm mmssssss
//24b + 40b
//64b - x
//64b - y
//64b - z
//total - 256b = 32bytes
extern "C" JNIEXPORT jbyteArray JNICALL
Java_com_example_vlclocator_ImageProcessing_formatString(
        JNIEnv* env,
        jobject /* this */,
        jdoubleArray Xo_array,
        jint dia,
        jint mes,
        jint ano,
        jint hora,
        jint minuto,
        jint segundo) {

    //adquire os vetores do java
    jdouble *Xo_jdouble = env->GetDoubleArrayElements(Xo_array, NULL);



    uint8_t index = 0;

    int8_t *data = (int8_t*) malloc(32 * sizeof(int8_t));

    //uint8_t b = dia << 3 + mes >> 1;
    //data[index++] = 'v' << 24 + 'l' << 16 + 'c' << 8 + ((dia << 3) & 0xF8 + (mes >> 1) & 0x07);
    //data[0] = (0x76 << 24) + (0x6C << 16) + (0x63 << 8) + (((dia << 3) & 0xF8) + ((mes >> 1) & 0x07));
    //data[0] = 0x766C6300;
    //uint8_t aux =
    //data[1] = ((((mes << 7) & (0x80)) + ((ano >> 7) & 0x7F)) << 24) + ((((ano << 1) & 0xFE) + ((hora >> 4) & 0x01)) << 16) +
    //        (((hora << 4) & 0xF0) + ((minuto >> 2) & 0x0F) << 8) + (((minuto << 6) & 0xC0) + (segundo & 0x3F));

    data[0] = 0x76;
    data[1] = 0x6C;
    data[2] = 0x63;
    data[3] = (((dia << 3) & 0xF8) + ((mes >> 1) & 0x07));
    data[4] = (((mes << 7) & (0x80)) + ((ano >> 7) & 0x7F));
    data[5] = (((ano << 1) & 0xFE) + ((hora >> 4) & 0x01));
    data[6] = ((hora << 4) & 0xF0) + ((minuto >> 2) & 0x0F);
    data[7] = (((minuto << 6) & 0xC0) + (segundo & 0x3F));

    index = 8;
    for(uint8_t i = 0; i < 3; i++){
        uint64_t ui64helper;

        if(Xo_jdouble != NULL) {
            memcpy(&ui64helper, &Xo_jdouble[i], sizeof(double));
        }else{
            ui64helper = 0;
        }
        for(uint8_t j = 0; j < 8; j++){
            data[index++] = (int8_t) ((ui64helper >> ((7 - j) * 8)) & 0xFF);
        }
            //data[index++] = (int32_t) ui64helper >> 32;
            //data[index++] = (int32_t) ui64helper & 0xFFFF;
        /*}else{
            data[index++] = 0;
            data[index++] = 0;
        }*/
    }


    //cria jintArray para passar para o java
    jbyteArray result = env->NewByteArray(32);
    //define os valores de jintArray como grayImage
    //env->SetIntArrayRegion(result, 0, 8, data);
    env->SetByteArrayRegion(result, 0, 32, data);

    //ReleaseIntArrayElements: Releases the native memory used by the original jintArray.
    env->ReleaseDoubleArrayElements(Xo_array, Xo_jdouble, 0);


    return result;
}



extern "C" JNIEXPORT jdoubleArray JNICALL
Java_com_example_vlclocator_ImageProcessing_p6pDLTJNI(
        JNIEnv* env,
        jobject /* this */,
        jdoubleArray rx_array,
        jintArray sx_array) {

    //adquire os vetores do java
    jdouble *rx_jdouble = env->GetDoubleArrayElements(rx_array, NULL);

    jint *sx_jint = env->GetIntArrayElements(sx_array, NULL);

    double **rx = (double**) malloc(6 * sizeof(double*));
    uint32_t **sx = (uint32_t**) malloc(6 * sizeof(uint32_t*));
    for(uint8_t i = 0; i < 6; i++){
        rx[i] = (double*) malloc(4 * sizeof(double));
        sx[i] = (uint32_t*) malloc(3 * sizeof(uint32_t));
        //inicializar os elementos
        for(uint8_t j = 0; j < 3; j++){
            rx[i][j] = rx_jdouble[i + 6 * j];
            sx[i][j] = sx_jint[i + 6 * j];
        }
        rx[i][3] = rx_jdouble[i + 6 * 3];

    }


    double ***KRZ = p6p_dlt(sx, rx);

    double *Xo = NULL;
    if(KRZ != NULL){
        if(KRZ[2] != NULL){
            Xo = (double*) malloc(3 * sizeof(double));
            for(uint8_t i = 0; i < 3; i++){
                Xo[i] = KRZ[2][i][0];
            }
        }
        matrix_free(KRZ[0], 3);
        matrix_free(KRZ[1], 3);
        matrix_free(KRZ[2], 3);
        free(KRZ);
    }



    for(uint8_t i = 0; i < 6; i++){
        free(sx[i]);
        free(rx[i]);
    }
    free(rx);
    free(sx);


    if(Xo == NULL){
        return NULL;
    }
    //cria jintArray para passar para o java
    jdoubleArray result = env->NewDoubleArray(3);

    //define os valores de jintArray como grayImage
    env->SetDoubleArrayRegion(result, 0, 3, Xo);

    //ReleaseIntArrayElements: Releases the native memory used by the original jintArray.
    env->ReleaseIntArrayElements(sx_array, sx_jint, 0);

    env->ReleaseDoubleArrayElements(rx_array, rx_jdouble, 0);


    return result;
}


extern "C" JNIEXPORT jdoubleArray JNICALL
Java_com_example_vlclocator_ImageProcessing_p6pDLTJNIXoRK(
        JNIEnv* env,
        jobject /* this */,
        jdoubleArray rx_array,
        jintArray sx_array) {

    //adquire os vetores do java
    jdouble *rx_jdouble = env->GetDoubleArrayElements(rx_array, NULL);

    jint *sx_jint = env->GetIntArrayElements(sx_array, NULL);

    double **rx = (double**) malloc(6 * sizeof(double*));
    uint32_t **sx = (uint32_t**) malloc(6 * sizeof(uint32_t*));
    for(uint8_t i = 0; i < 6; i++){
        rx[i] = (double*) malloc(4 * sizeof(double));
        sx[i] = (uint32_t*) malloc(3 * sizeof(uint32_t));
        //inicializar os elementos
        for(uint8_t j = 0; j < 3; j++){
            rx[i][j] = rx_jdouble[i + 6 * j];
            sx[i][j] = sx_jint[i + 6 * j];
        }
        rx[i][3] = rx_jdouble[i + 6 * 3];

    }


    double ***KRZ = p6p_dlt(sx, rx);

    double *XoRK = NULL;
    if(KRZ != NULL){
        if(KRZ[2] != NULL){
            XoRK = (double*) malloc(21 * sizeof(double));
            //uint8_t index = 0;
            //for(uint8_t i = 0; i < 3; i++){
            //    XoRK[index++] = KRZ[2][i][0];
            //}
            for(uint8_t i = 0; i < 3; i++){
                XoRK[i] = KRZ[2][i][0];
                for(uint8_t j = 0; j < 3; j++){
                    XoRK[3 + 3 * i + j] = KRZ[1][i][j];
                    XoRK[12 + 3 * i + j] = KRZ[0][i][j];
                }
            }
        }
        matrix_free(KRZ[0], 3);
        matrix_free(KRZ[1], 3);
        matrix_free(KRZ[2], 3);
        free(KRZ);
    }



    for(uint8_t i = 0; i < 6; i++){
        free(sx[i]);
        free(rx[i]);
    }
    free(rx);
    free(sx);


    if(XoRK == NULL){
        return NULL;
    }
    //cria jintArray para passar para o java
    jdoubleArray result = env->NewDoubleArray(21);

    //define os valores de jintArray como grayImage
    env->SetDoubleArrayRegion(result, 0, 21, XoRK);

    //ReleaseIntArrayElements: Releases the native memory used by the original jintArray.
    env->ReleaseIntArrayElements(sx_array, sx_jint, 0);

    env->ReleaseDoubleArrayElements(rx_array, rx_jdouble, 0);


    return result;
}
