#include "Blob.h"


Blob::Pixel::Pixel() {
	row = 0;
	col = 0;
}
Blob::Pixel::Pixel(int row, int col) {
	this->row = row;
	this->col = col;
}
Blob::Pixel::~Pixel() {
	//desnecessário zerar os elementos
	//row = 0;
	//col = 0;
}
/*
void Blob::Pixel::copy(Pixel pixel) {
	row = pixel.row;
	col = pixel.col;
}
*/

Blob::Blob() {
	pixelCounter = 0;
}

Blob::~Blob() {
	while (!pixelList.empty()) {
		delete pixelList.front(), pixelList.pop_front();
	}
}

#include<iostream>
void Blob::addPixel(int row, int col) {
	Pixel* pixel;

	pixel = new Pixel(row, col);
	attCornerPixels(pixel);
	//pixelList.push_back(pixel);
	pixelCounter++;
	delete pixel;
	
	
}

void Blob::attCornerPixels(Pixel *pixel) {
	if (pixelCounter == 0) {
		topLeftPixel.row = pixel->row;
		topLeftPixel.col = pixel->col;
		bottomRightPixel.row = pixel->row;
		bottomRightPixel.col = pixel->col;
	}
	else {
		if (pixel->row < topLeftPixel.row) {
			topLeftPixel.row = pixel->row;
		}
		else if (pixel->row > bottomRightPixel.row) {
			bottomRightPixel.row = pixel->row;
		}

		if (pixel->col < topLeftPixel.col) {
			topLeftPixel.col = pixel->col;
		}
		else if (pixel->col > bottomRightPixel.col) {
			bottomRightPixel.col = pixel->col;
		}
	}
}

std::list<Blob::Pixel*> Blob::getPixelList() {
	return pixelList;
}
int Blob::getPixelCounter() {
	return pixelCounter;
}

Blob::Pixel Blob::getTopLeftPixel() {
	return topLeftPixel;
}
Blob::Pixel Blob::getBottomRightPixel() {
	return bottomRightPixel;
}