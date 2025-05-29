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
		
		Pixel* topLeft;
		Pixel* topRight;
		Pixel* bottomLeft;
		Pixel* bottomRight;

		Pixel();
		Pixel(int row, int col);

	private:
		void initializePointers();
	};

	//ao invés de ser uma lista, poderia ser uma árvore quaternária
	//std::list<Pixel> coordinates;
	//Pixel* extremitiesPixels[4];
private:
	Pixel* pixelRoot;

public:
	Blob();

	~Blob();

	//eu devia colocar um row e um col e deixar os outros privados, para que 
	//eu deixe pixelroot como root, caso contrario pode dar merda

	
	void addPixel(int row, int col);

	Pixel* getPixelTree();

	void freeTree();

	void diplayPixelTree();

	Pixel** getBlobExtremeties();

	//void calculateExtremitiesPixels();

private:
	void addPixel(Pixel** pixel, int row, int col);
	void freeTree(Pixel** pixel);
	void displayPixelTree(Pixel** pixel);

};

#endif BLOB_H