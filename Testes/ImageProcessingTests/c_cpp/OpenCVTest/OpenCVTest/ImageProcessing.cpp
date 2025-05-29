#include "ImageProcessing.h"

ImageProcessing::ImageProcessing() {
	matImage = NULL;
}

ImageProcessing::ImageProcessing(std::string imagePath) {
    loadImage(imagePath);
}

ImageProcessing::~ImageProcessing() {
    matImage.release();
    /*
    if (matImage != NULL) {
        delete matImage;
        matImage = NULL;
    }
    */
}

void ImageProcessing::loadImage(std::string imagePath) {
    matImage.release();
    matImage = cv::imread(imagePath);
    /*
	if (imagePath.empty()) {
		matImage = NULL;
	}
	else {
        matImage = new cv::Mat(cv::imread(imagePath));
		//*matImage = cv::imread(imagePath);
	}
    */
}

void ImageProcessing::setImage(cv::Mat image) {
    matImage = image.clone();
}

cv::Mat ImageProcessing::getImage() {
    return matImage.clone();
}

void ImageProcessing::resizeImage(unsigned int value, bool valueIsWidth) {

    if (value == 0) return;

    int w = matImage.cols;
    int h = matImage.rows;
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


    cv::resize(matImage, matImage, cv::Size(newWidth, newHeight), cv::INTER_LINEAR);

}

void ImageProcessing::rgb2gray() {
    cv::cvtColor(matImage, matImage, cv::COLOR_BGR2GRAY);
}

void ImageProcessing::blur(int filterOrder) {
    cv::blur(matImage, matImage, cv::Size(filterOrder, filterOrder));
}

void ImageProcessing::gray2bw() {
    cv::threshold(matImage, matImage, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
}

void ImageProcessing::rgbWBlur2bw(int filterOrder) {
    rgb2gray();
    blur(filterOrder);
    gray2bw();
}

void ImageProcessing::displayImg(int delay) {
    cv::imshow("", matImage);
    cv::waitKey(delay);
}

//image must be binary
std::list<Blob*> ImageProcessing::findBlobs() {
    std::list<Blob*> blobs;
    if (!matImage.empty()) {
        cv::Mat img = matImage.clone();
        
        int nPixels = img.cols * img.rows;

        int row, col;

        //poderia iterar entre uma fila que tem todos os nPixels, mas sla
        for (int i = 0; i < nPixels; i++) {
            //std::cout << "row = " << i / img.cols << ",  col = " << i % img.rows << std::endl;
            

            //i daqui tá dando diferente do i da recursiveBlobConnnector
            if (matImage.data[i] == 255) {
                Blob *blob;
                //row = i / img.cols;
                //col = i % img.cols;

                blob = new Blob();

                //cv::imshow("o", img);
                //cv::waitKey();

                //recursiveBlobConnnector(blob, img.data, row, col, img.rows, img.cols);
                recursiveBlobConnnector(blob, i, nPixels);
                //std::cout << "row = " << row << ",  col = " << col << std::endl;
                //cv::imshow("o",img);
                //cv::waitKey();


                if (!blob->getPixelList().empty()) {
                    blobs.push_back(blob);
                }
                else {
                    delete blob;
                }
                
            }
        }
        matImage.release();
        matImage = img.clone();
        img.release();
    }
    return blobs;
}

void ImageProcessing::recursiveBlobConnnector(Blob* blob, int i, int nPixels) {
    if (i < 0 || i >= nPixels){
        return;
    }
    if (matImage.data[i] == 255) {
        matImage.data[i] = 0;
        int row = i / matImage.cols;
        int col = i % matImage.cols;
        blob->addPixel(row, col);

        std::cout << blob->getPixelCounter() << std::endl;

        int j = i - matImage.cols - 1;
        int k;
        do {
            k = 0;
            do {
                recursiveBlobConnnector(blob, j + k, nPixels);
                k++;
            } while (k < 3);
            j += matImage.cols;
        } while (j < i + 3 * matImage.cols);
    }
}

/*
void ImageProcessing::recursiveBlobConnnector(Blob *blob, uint8_t* pixelPointer, int row, int col, int imgRows, int imgCols) {
    if (row < 0 || row >= imgRows ||
        col < 0 || col >= imgCols) {
        return;
    }
    int i = row * imgCols + col;
    if (pixelPointer[i] == 255) {
        pixelPointer[i] = 0;
        blob->addPixel(row, col);
        std::cout << blob->getPixelCounter() << std::endl;
        for (int rowAdd = -1; rowAdd <= 1; rowAdd++) {
            for (int colAdd = -1; colAdd <= 1; colAdd++) {
                recursiveBlobConnnector(blob, pixelPointer,
                    row + rowAdd, col + colAdd, imgRows, imgCols);
            }
        }
    }
}
*/

void ImageProcessing::HighLightBlobs() {
    std::list<Blob*> blobs = findBlobs();

    //cv::Mat img = matImage.clone();

    while (!blobs.empty()) {
        Blob* blob = blobs.front();

        drawBlobSquare(blob);

        blobs.pop_front();
        delete blob;
    }
    //return img;
}

void ImageProcessing::drawBlobSquare(Blob* blob) {
    Blob::Pixel topLeftPixel = blob->getTopLeftPixel();
    Blob::Pixel bottomRightPixel = blob->getBottomRightPixel();

    Blob::Pixel auxPixel;
    auxPixel.row = topLeftPixel.row;
    auxPixel.col = bottomRightPixel.col;

    drawSolidSquare(&matImage, topLeftPixel, auxPixel, 255);
    drawSolidSquare(&matImage, auxPixel, bottomRightPixel, 255);

    auxPixel.row = bottomRightPixel.row;
    auxPixel.col = topLeftPixel.col;

    drawSolidSquare(&matImage, topLeftPixel, auxPixel, 255);
    drawSolidSquare(&matImage, auxPixel, bottomRightPixel, 255);
}

void ImageProcessing::drawSolidSquare(cv::Mat* img, Blob::Pixel p1, Blob::Pixel p2, uint8_t grayShade) {

    int row1, row2;
    int col1, col2;

    if (p1.row < p2.row) {
        row1 = p1.row;
        row2 = p2.row;
    }
    else {
        row2 = p1.row;
        row1 = p2.row;
    }

    if (p1.col < p2.col) {
        col1 = p1.col;
        col2 = p2.col;
    }
    else {
        col2 = p1.col;
        col1 = p2.col;
    }

    if (row1 < 0 || row2 >= img->rows ||
        col1 < 0 || col2 >= img->cols) {
        return;
    }

    int pj;

    int pjStart = row1 * img->cols + col1;
    int pjLimit = row2 * img->cols + col2;
    int colDiff = col2 - col1;
    int pjColLimit;

    pj = pjStart;
    do {

        pjColLimit = pj + colDiff;
        do {
            img->data[pj] = grayShade;
            pj++;
        } while (pj <= pjColLimit);
        pj--;
        pj += img->cols;
    } while (pj <= pjLimit);
    /*
    int pointerJumperLimit = 

    for (int row = row1; row <= row2; row++) {
        pointerJumper = row * img->cols + col1;
        for(;pointerJumper )
        for (int col = col1; col <= col2; col++) {
            pointerJumper = 
        }
    }
    */
}

/*
uint8_t** ImageProcessing::cvMat2Byte(cv::Mat image) {
    uint8_t** ui8Img = NULL;
    if (!image.empty()) {
        int w = image.cols;
        int h = image.rows;

        int i, j, aux;

        ui8Img = (uint8_t**)malloc(h * sizeof(uint8_t*));
        for (i = 0; i < h; i++) {
            ui8Img[i] = (uint8_t*)malloc(w * sizeof(uint8_t));
        }

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
*/