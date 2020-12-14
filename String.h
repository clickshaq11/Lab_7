#pragma once
#include <iostream>
class String 
{
public:
	String();
	String(int len);
	String(const char* const);
	String(const String& other);
	int getLen();
	char* getData();
	void push_back(const char elem);
	String& operator =(const String& other);
	String operator +(const String& other);
	char& operator [](int index);
	bool operator ==(const String& other);
	bool operator !=(const String& other);
	friend std::istream& operator >> (std::istream& stream, String& string);
	friend std::ostream& operator << (std::ostream& stream, const String& string);
	~String();
private: 
	int length_;
	char* str_;
};

