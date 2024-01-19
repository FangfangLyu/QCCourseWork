#ifndef TEXT_H
#define TEXT_H
#include <iostream>
#include <string>
#include "SafeMatrix.h"
#include "SafeArray.h"
#include "File.h"

class Text: public File{
private:
	string chars;
	int size;

public:
	Text();
	Text(string name_, string message);
	int getSize() const override;
	int calcSize();
	int count();
	void setSize(int size_) override;

};

#endif
