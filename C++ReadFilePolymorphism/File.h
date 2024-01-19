#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <string>
#include "SafeMatrix.h"
#include "SafeArray.h"

using std::string;

class File{
private:
	string name;
	string type;
public:
	File();
	File(string name_, string type_);
	virtual ~File(){};
	virtual int getSize() const = 0;
	virtual void setSize(int size_) = 0;

	string& getName();
	string& getType();
};

#endif

