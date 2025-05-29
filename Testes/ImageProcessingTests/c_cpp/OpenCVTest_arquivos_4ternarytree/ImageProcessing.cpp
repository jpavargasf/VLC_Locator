#include "ImageProcessing.h"

ImageProcessing::ImageProcessing() {
	matImage = NULL;
}

ImageProcessing::ImageProcessing(std::string imagePath) {
    loadImage(imagePath);
}

ImageProcessing::~ImageProcessing() {
    if (matImage != NULL) {
        delete matImage;
        matImage = NULL;
    }
}

void ImageProcessing::loadImage(std::string imagePath) {
	if (imagePath.empty()) {
		matImage = NULL;
	}
	else {
		*matImage = cv::imread(imagePath);
	}
}

void ImageProcessing::setImage(cv::Mat *image) {
    matImage = image;
}

cv::Mat* ImageProcessing::getImage() {
    return matImage;
}

void ImageProcessing::resizeImage(unsigned int value, bool valueIsWidth) {

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

    cv::Mat r;
    cv::resize(*matImage, *matImage, cv::Size(newWidth, newHeight), cv::INTER_LINEAR);
}

//image must be binary
std::list<Blob*> ImageProcessing::findBlobs() {
    std::list<Blob*> blobs;
    if (matImage != NULL) {
        cv::Mat img = matImage->clone();
        
        int nPixels = img.cols * img.rows;

        int row, col;

        for (int i = 0; i < nPixels; i++) {
            std::cout << "row = " << i / img.cols << ",  col = " << i % img.rows << std::endl;
            
            if (img.data[i] == 255) {
                Blob *blob;
                row = i / img.cols;
                col = i % img.rows;

                blob = new Blob();

                recursiveBlobConnnector(blob, img.data, row, col, img.rows, img.cols);
                //std::cout << "row = " << row << ",  col = " << col << std::endl;
                cv::imshow("o",img);
                cv::waitKey();

                blobs.push_back(blob);
            }
        }



    }
    return blobs;
}

void ImageProcessing::recursiveBlobConnnector(Blob *blob, uint8_t* pixelPointer, int row, int col, int imgRows, int imgCols) {
    if (row < 0 || row >= imgRows ||
        col < 0 || col >= imgCols) {
        return;
    }
    int i = row * imgCols + col;
    if (pixelPointer[i] == 255) {
        pixelPointer[i] = 0;
        blob->addPixel(row, col);
        for (int rowAdd = -1; rowAdd <= 1; rowAdd++) {
            for (int colAdd = -1; colAdd <= 1; colAdd++) {
                recursiveBlobConnnector(blob, pixelPointer,
                    row + rowAdd, col + colAdd, imgRows, imgCols);
            }
        }
    }
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