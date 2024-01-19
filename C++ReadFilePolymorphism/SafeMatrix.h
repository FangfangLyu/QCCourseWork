#ifndef SAFEMATRIX_H
#define SAFEMATRIX_H

#include <cstddef>
#include <iostream>
#include "SafeArray.h"

template <class T>
class SafeMatrix{
private:
	int rowNo;
	int colNo;
	SafeArray<T>* matrix;

public:
	int length() const;
	SafeMatrix();
	SafeMatrix(int rowNo, int columnNo);
	SafeMatrix(const SafeMatrix<T> &other);


	~SafeMatrix();

	SafeMatrix<T> &operator=(const SafeMatrix<T> &other);


	void setRow(int index, const SafeArray<T>& entry);
	const SafeArray<T>& getRow(int rowIndex) const;

	SafeArray<T>& operator[](int index) const;

};

template <class T>
std::ostream& operator<<(std::ostream& out, const SafeMatrix<T> &matrix){
	for(int i = 0;i<matrix.length();i++)
		{
			out << matrix.getRow(i) << std::endl;
		}
	return out;
}

template <class T>
SafeMatrix<T>::SafeMatrix() : rowNo(0), colNo(0), matrix(NULL){

}

template <class T>
SafeMatrix<T>::SafeMatrix(int rowNo, int columnNo):rowNo(rowNo), colNo(columnNo){
	//initialize the matrix here
	//ROW
	matrix = new SafeArray<T>[rowNo];
	for(int i = 0; i<rowNo; ++i){
		SafeArray<T> temp(colNo);
		matrix[i] = temp;
	}
}

template <class T>
SafeMatrix<T>::~SafeMatrix(){
	if(matrix != NULL)
	{
		delete [] matrix;
	}
}



template <class T>
SafeMatrix<T>::SafeMatrix(const SafeMatrix<T> &other) : rowNo(other.rowNo), colNo(other.colNo)
{
	matrix = new SafeArray<T>[rowNo];
	for(int i = 0;i<rowNo;i++)
	{
		matrix[i] = other.matrix[i];
	}
}



template <class T>
SafeMatrix<T> &SafeMatrix<T>::operator=(const SafeMatrix<T> &other)
{
	if(matrix != NULL)
	{
		delete [] matrix;
	}

	rowNo = other.rowNo;
	colNo = other.colNo;
	matrix = SafeMatrix(rowNo, colNo);

	for(int i = 0;i<rowNo;i++)
	{
		matrix[i] = other.matrix[i];
	}

	return *this;
}

template <class T>
int SafeMatrix<T>::length() const{
	return rowNo;
}

template <class T>
void SafeMatrix<T>::setRow(int index, const SafeArray<T>& entry){
	if(index>=0 && index <rowNo){
		matrix[index] = entry;
	}

}

template <class T>
const SafeArray<T>& SafeMatrix<T>::getRow(int rowIndex) const{
	if(rowIndex < 0 || rowIndex >= rowNo)
		{
			std::exit(1);
	}
	return matrix[rowIndex];
}

template <class T>
SafeArray<T>& SafeMatrix<T>::operator[](int index) const{
	if(index < 0 || index >= rowNo)
			{
				std::exit(1);
		}
	return matrix[index];
}
#endif
