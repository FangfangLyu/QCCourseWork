#include <iostream>
#include <string>
#include <cmath>

#include "SafeMatrix.h"
#include "SafeArray.h"
#include "File.h"
#include "Image.h"

Image::Image() : File("","gif"), pMatrix(){
}

Image::Image(string name, int row, int column): File(name, "gif"), pMatrix(SafeMatrix<int>(row, column)){

	int sum = 0;
	for(int i=0; i<pMatrix.length(); i++){
		for(int j=0; j < pMatrix[0].length() ; j++){
			sum += pMatrix[i][j];
		}
	}
	size = ceil(sum/8);
}

SafeMatrix<int>& Image::getpMatrix(){
	return pMatrix;
}
int Image::getColorD(int row, int column){
	return pMatrix[row][column];
}

int Image::getSize() const{
	return size;
}
void Image::setSize(int size_){
	size =size_;
}
int Image::calcSize(){
	int sum = 0;
	for(int i=0; i<pMatrix.length(); i++){
		for(int j=0; j < pMatrix[0].length() ; j++){
			sum += pMatrix[i][j];
		}
	}
	return ceil(sum/8);
}
