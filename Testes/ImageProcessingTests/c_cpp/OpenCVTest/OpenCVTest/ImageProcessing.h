#pragma once
#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <iostream>
#include <cstdlib>
#include<string>
#include<list>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "Blob.h"

class ImageProcessing
{
	//variables
private:
	cv::Mat matImage;
	
	//methods
public:

	ImageProcessing();
	ImageProcessing(std::string imagePath);

	~ImageProcessing();

	void loadImage(std::string imagePath);

	void setImage(cv::Mat image);

	cv::Mat getImage();

	void resizeImage(unsigned int value, bool valueIsWidth);

	void rgb2gray();

	void blur(int filterOrder);

	void gray2bw();

	void rgbWBlur2bw(int filterOrder);

	void displayImg(int delay);

	std::list<Blob*> findBlobs();

	void HighLightBlobs();
private:
//	void recursiveBlobConnnector(Blob* blob, uint8_t* pixelPointer,int row, int col, int imgRows, int imgCols );
	void recursiveBlobConnnector(Blob* blob, int i, int nPixels);

	void drawBlobSquare(Blob* blob);

	void drawSolidSquare(cv::Mat* img, Blob::Pixel p1, Blob::Pixel p2, uint8_t grayShade);

};

#endif IMAGEPROCESSING_H
