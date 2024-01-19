#include <iostream>
#include <string>
#include "SafeMatrix.h"
#include "SafeArray.h"
#include "File.h"
#include "Text.h"


Text::Text():File("", "txt"){

}
Text::Text(string name_, string message) : File(name_,"txt"),chars(message){


	int num = chars.length(); //each char is 8 bits = 1 byte
	size = num;
}
int Text::getSize() const{
	return size;
}
int Text::calcSize(){
	int num = chars.length(); //each char is 8 bits = 1 byte
	return num;
}
int Text::count(){
	return chars.length();
}
void Text::setSize(int size_){
	size = size_;
}
