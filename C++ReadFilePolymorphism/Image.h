#ifndef IMAGE_H
#define IMAGE_H
#include <iostream>
#include <string>
#include "SafeMatrix.h"
#include "SafeArray.h"
#include "File.h"

class Image : public File{
private:
	SafeMatrix<int> pMatrix; //bits
	int size;
public:
	Image();
	Image(string name, int row, int column);
	SafeMatrix<int>& getpMatrix();
	int getColorD(int row, int column);
	int calcSize();
	int getSize() const override;
	void setSize(int size_) override;

};

#endif
