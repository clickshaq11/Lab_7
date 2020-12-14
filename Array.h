#pragma once
#include <iostream>
#include "Class.h"

template <class T>
class Array 
{
public:
	Array();
	Array(int size);
	Array(const Array& arr);
	~Array();
	T& operator[] (int i) const;
	Array& operator=(const Array& arr);
	int getSize();
	void push_back(T& element);
	friend bool operator==(const Array& arr, const Array& other);
	friend bool operator!=(const Array& arr, const Array& other);
private:
	T* request_;
	int size_;
};

template <class T>
Array<T>::Array() 
{
	this->request_ = nullptr;
	this->size_ = 0;
}

template <class T>
Array<T>::Array(int size) 
{
	if (size == 0) {
		this->request_ = nullptr;
		this->size_ = 0;
	}
	else {
		this->size_ = size;
		this->request_ = new T[size];
	}
}

template <class T>
Array<T>::Array(const Array& other) 
{
	if (other.size_ == 0) {
		this->request_ = nullptr;
		this->size_ = 0;
	}
	else {
		this->size_ = other.size_;
		this->request_ = new T[this->size_];
		for (int i = 0; i < this->size_; i++) {
			this->request_[i] = other.request_[i];
		}
	}
}

template <class T>
T& Array<T>::operator[] (int i) const 
{
	if (i < 0 || i > this->size_) {
		throw "Error";
	}
	return request_[i];
}

template <class T>
bool operator==(const Array<T>& arr, const Array<T>& other) 
{
	if (arr.size_ == other.size_) {
		for (int i = 0; i < arr.size_; i++) {
			if (arr.request_[i] != other.request_[i]) {
				return false;
			}
			return true;
		}
	}
	return false;
}

template <class T>
bool operator!=(const Array<T>& arr, const Array<T>& other) 
{
	return !(arr == other);
}

template <class T>
Array<T>& Array<T>::operator=(const Array<T>& other) 
{
	if (this->request_ != nullptr) {
		delete[] this->request_;
	}
	this->size_ = other.size_;
	this->request_ = new T & [this->size_];
	for (int i = 0; i < this->size_; i++) {
		this->request_[i] = other.request_[i];
	}
}

template <class T>
void Array<T>::push_back(T& element)
{
	if (this->size_ == 0 || this->request_ == nullptr) {
		this->request = new T[1];
		this->request[0] = element;
	}
	else {
		Array<T> Temp(this);
		this->size_++;
		delete[] this->request_;
		this->request_ = new T[size_];
		for (int i = 0; i < this->size_-1; i++) {
			this->request_[i] = Temp[i];
		}
		delete[] Temp;
		this->request_[size_] = element;
	}
}

template <class T>
std::istream& operator>>(std::istream& stream, Array<T>& arr) 
{
	for (int i = 0; i < arr.size_; i++) {
		stream >> arr >> " ";
	}
	return stream;
}

template <class T>
std::ostream& operator<<(std::ostream& stream, const Array<T>& arr) 
{
	for (int i = 0; i < arr.size_; i++) {
		stream << arr << " ";
	}
	return stream;
}

template <class T>
int Array<T>::getSize() 
{
	return this->size_;
}

template <class T>
Array<T>::~Array() 
{
	delete[] request_;
}