#include <iostream>
#include <string>
#include "SafeMatrix.h"
#include "SafeArray.h"
#include "File.h"
#include "Image.h"
#include "Text.h"

#include <vector>
#include <fstream>
using std::cin;
using std::cout;

void outputProperties(const std::vector<File*>& list, int index = 0);
std::vector<File*> filterByType(const std::vector<File*>& list, const std::string& ext);


int main(){
	std::vector<File*> files;
	string deli;
    string name;
    int row, column;
    int size;

    char mode;
	std::fstream myfile;
	string type;

	while(true){
		do{
			cout << "\t1. Read from a File " << std::endl
					<<"\t2. Create an Image File." << std::endl
					<< "\t3. Create a Text File. " << std::endl
					<< "\t4. Print All Files. " << std::endl
					<< "\t5. Print Image Files." << std::endl
					<< "\t6. Print Text Files. " << std::endl
					<< "\t7. Quit. " << std::endl;
			cin >> mode;
		}while(!std::isdigit(mode));

		switch(mode){
				case '1':{
					myfile.open("/Users/fangfang/eclipse-workspace/hw8/src/file.txt", std::ifstream::in);
					while(!myfile.eof()){
						myfile >> type;
						if(type == "gif"){
							myfile >> name;
							myfile >> row;
							myfile >> deli;
							myfile >> column;
							files.push_back(new Image(name, row,  column));
							myfile >> size;
							files[files.size()-1]->setSize(size);
						}else if(type == "txt"){
							myfile >> name;
							files.push_back(new Text(name, ""));
							myfile >> size;
							files[files.size()-1]->setSize(size);
						}
					}

					myfile.close();
					break;
				}
				case '2':{

					cout << "Enter name of the image:" << std::endl;
					cin >> name;
					cout << "Enter the dimension row and column (separete by space): " ;
					cin >> row;
					cin >> column;
					files.push_back(new Image(name, row,  column));
					break;
				}
				case '3':{
					cout << "Enter name of the Text:" << std::endl;
					cin >> name;
					files.push_back(new Text(name, ""));
					break;
				}
				case '4':{
					outputProperties(files);
					break;
				}
				case '5':{
					outputProperties(filterByType(files,"gif"));
					break;
				}
				case '6':{
					outputProperties(filterByType(files,"txt"));
					break;
				}
				case '7':{
					for(int i = 0; i<files.size();i++){
						delete files[i];
					}
					exit(1);
					std::cout << "Program ended" << std::endl;
					break;
				}
				default:{
					for(int i = 0; i<files.size();i++){
						delete files[i];
					}
					exit(1);
				}
		}
	}


}


void outputProperties(const std::vector<File*>& list, int index){
	if(index >= list.size()){
		return;
	}

    File* currentFile = list[index];
	std::cout << "Text name: " << (currentFile->getName()) << std::endl;
	std::cout << "Text type: " << (currentFile->getType()) <<std::endl;
	std::cout << currentFile->getSize() << " Bytes" << std::endl;

	outputProperties(list, index+1);

}

std::vector<File*> filterByType(const std::vector<File*>& list, const std::string& ext){
	std::vector<File*> filtered;
	std::vector<File*> localCopy = list;

	if(localCopy.size()==0){
		return filtered;
	}

	if(localCopy.back()->getType() == ext){
		filtered.push_back(localCopy.back());
	}
	localCopy.pop_back(); // delete the filtered element

	std::vector<File*> recursiveFilter = filterByType(localCopy, ext);
	//combine the two, from the last case, til it combined all recursive calls.

    filtered.insert(filtered.end(), recursiveFilter.begin(), recursiveFilter.end());
    //insert after the theoretical next position

    return filtered;

}

