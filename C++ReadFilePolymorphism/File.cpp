#include <iostream>
#include <string>
#include "SafeMatrix.h"
#include "SafeArray.h"
#include "File.h"

using std::string;

File::File(){
	name = "";
	type = "";
}
File::File(string name_, string type_){
	name = name_;
	type = type_;
}

string& File::getName(){
	return name;
}
string& File::getType(){
	return type;
}
