#ifndef SAFEARRAY_H
#define SAFEARRAY_H


#include <cstddef>
#include <iostream>

template <class T>
class SafeArray{
private:
	int size;
	T *array;

public:
	SafeArray();
	SafeArray(int size);
	SafeArray(const SafeArray<T> &other);
	~SafeArray();

	SafeArray<T> &operator=(const SafeArray<T> &other);

	int length() const;

	void setEntry(int index, const T& entry);
	const T& getEntry(int index) const;
	bool deleteEntry(const T& entry);

	T& operator[](int index);

};


template <class T>
std::ostream& operator<<(std::ostream &out, const SafeArray<T> &array)
{
	for(int i = 0;i<array.length();i++)
	{
		out << array.getEntry(i) << " ";
	}
	return out;
}


template <class T>
SafeArray<T>::SafeArray() : size(0), array(NULL)
{

}

template <class T>
SafeArray<T>::SafeArray(const SafeArray<T> &other) : size(other.size)
{
	array = new T[size];
	for(int i = 0;i<size;i++)
	{
		array[i] = other.array[i];
	}
}


template <class T>
SafeArray<T>::SafeArray(int size) : size(size), array(new T[size])
{
	//array initialized, everything is empty.
}


template <class T>
SafeArray<T>::~SafeArray()
{
	if(array != NULL)
	{
		delete [] array;
	}
}

template <class T>
SafeArray<T> &SafeArray<T>::operator=(const SafeArray<T> &other)
{
	if(array != NULL)
	{
		delete [] array;
	}

	size = other.size;
	array = new T[size];

	for(int i = 0;i<size;i++)
	{
		array[i] = other.array[i];
	}

	return *this;
}

template <class T>
int SafeArray<T>::length() const
{
	return size;
}

template <class T>
void SafeArray<T>::setEntry(int index, const T& entry)
{
	if(index > 0 && index < size)
	{
		array[index] = entry;
	}
}

template <class T>
const T& SafeArray<T>::getEntry(int index) const
{
	if(index < 0 || index >= size)
	{
		std::exit(1);
	}

	return array[index];
}

template <class T>
bool SafeArray<T>::deleteEntry(const T& entry)
{
	int index = -1;
	for(int i = 0; i < size; i++)
	{
		if(array[i] == entry)
		{
			index = i;
			break;
		}
	}

	if(index == -1)
	{
		return false;
	}

	if(size == 1)
	{
		delete [] array;
		array = NULL;
		size--;
	}
	else
	{
		T *temp = new T[size - 1];
		int j = 0;
		for(int i = 0;i<size;i++)
		{
			if(i != index)
			{
				temp[j++] = array[i];
			}
		}
		delete [] array;
		array = temp;
		size--;
	}

	return true;
}

template <class T>
T& SafeArray<T>::operator[](int index)
{
	if(index < 0 || index >= size)
	{
		std::cout << "Index out of bounds" << std::endl;
		std::exit(0);
	}
	return array[index];
}


#endif
