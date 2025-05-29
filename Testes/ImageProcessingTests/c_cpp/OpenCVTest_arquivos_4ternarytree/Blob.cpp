#include "Blob.h"


Blob::Pixel::Pixel() {
	row = 0;
	col = 0;
	initializePointers();
}
Blob::Pixel::Pixel(int row, int col) {
	this->row = row;
	this->col = col;
	initializePointers();
}

void Blob::Pixel::initializePointers() {
	topLeft = NULL;
	topRight = NULL;
	bottomLeft = NULL;
	bottomRight = NULL;
}

Blob::Blob() {
	pixelRoot = NULL;
}

Blob::~Blob() {
	freeTree(&pixelRoot);
}


void Blob::addPixel(int row, int col) {
	addPixel(&pixelRoot, row, col);
}

void Blob::addPixel(Pixel** pixel, int row, int col) {
	if (*pixel == NULL) {
		*pixel = new Pixel(row, col);
		return;
	}
	if (row > (*pixel)->row) {
		if (col > (*pixel)->col) {
			//bottom right
			addPixel(&(*pixel)->bottomRight, row, col);
		}
		else {
			//bottom left
			addPixel(&(*pixel)->bottomLeft, row, col);
		}
	}
	else {
		if (col > (*pixel)->col) {
			//bottom right
			addPixel(&(*pixel)->topRight, row, col);
		}
		else {
			//bottom left
			addPixel(&(*pixel)->topLeft, row, col);
		}
	}

}

void Blob::freeTree() {
	freeTree(&pixelRoot);
}

void Blob::freeTree(Pixel** pixel) {
	if (*pixel == NULL)	return;
	freeTree(&(*pixel)->topLeft);
	freeTree(&(*pixel)->topRight);
	freeTree(&(*pixel)->bottomLeft);
	freeTree(&(*pixel)->bottomRight);
	
	delete (*pixel);
	(*pixel) = NULL;
}

Blob::Pixel* Blob::getPixelTree() {
	return pixelRoot;
}

void Blob::diplayPixelTree() {
	displayPixelTree(&pixelRoot);
}

#include<iostream>
void Blob::displayPixelTree(Pixel** pixel) {
	if (*pixel == NULL)	return;
	displayPixelTree(&(*pixel)->topLeft);
	displayPixelTree(&(*pixel)->topRight);

	std::cout << "[" << (*pixel)->row << "," << (*pixel)->col << "]" << std::endl;

	displayPixelTree(&(*pixel)->bottomLeft);
	displayPixelTree(&(*pixel)->bottomRight);
}