#pragma once
#ifndef BLOB_H
#define BLOB_H

#include<cstdio>
#include<list>

//----cols------
//|
//|
//rows
//|
//|
class Blob
{
public:

	class Pixel {
	public:
		int row, col;

		Pixel();
		Pixel(int row, int col);

		~Pixel();

		//void copy(Pixel pixel);
	};

	//overkill n compensa
	//ao invés de ser uma lista, poderia ser uma árvore quaternária

private:
	//Pixel* pixelRoot;
	std::list<Pixel*> pixelList;

	Pixel topLeftPixel;
	Pixel bottomRightPixel;

	int pixelCounter;


public:
	Blob();

	~Blob();

	
	void addPixel(int row, int col);
	std::list<Pixel*> getPixelList();
	int getPixelCounter();
	
	Pixel getTopLeftPixel();
	Pixel getBottomRightPixel();

private:
	void attCornerPixels(Pixel *pixel);

};

#endif BLOB_H