#include "String.h"
#include "Class.h"

// пункт назначения, номер рейса, фамилия и имя пассажира, желаемая дата вылета.
// перегруженный оператор отношения для номера рейса
// сортировка методом простого выбора для желаемой даты вылета
// перегруженный оператор отношения для даты 

String::String() 
{
	this->length_ = 0;
	this->str_ = nullptr;
}

String::String(const char* string) 
{
	this->length_ = strlen(string);
	this->str_ = new char[length_+1];
	for (int i = 0; i < length_; i++) {
		this->str_[i] = string[i];
	}
	this->str_[this->length_] = '\0';
}

String::String(const String& other)
{
	if (this->length_ != 0) {
		this->str_ = nullptr;
		this->length_ = 0;
	}
	this->length_ = other.length_;
	this->str_ = new char[this->length_+1];
	for (int i = 0; i < length_; i++) {
		this->str_[i] = other.str_[i];
	}
	this->str_[this->length_] = '\0';
}

String::String(int len) 
{
	this->length_ = len;
	this->str_ = new char[this->length_];
}

String::~String() 
{
	delete[] this->str_;
}

int String::getLen() 
{
	return this->length_;
}

char* String::getData()
{
	return this->str_;
}

void String::push_back(const char elem) 
{
	String temp(*this);
	this->length_++;
	delete[] this->str_;
	this->str_ = new char[length_ + 1];
	for (int i = 0; i < length_ - 1; i++) {
		this->str_[i] = temp[i];
	}
	this->str_[length_ - 1] = elem;
	this->str_[length_] = '\0';
}

String& String::operator =(const String& other)
{	
	if (&other == this) {
		return *this;
	}
	if (this->length_ != 0) {
		delete[] this->str_;
	}
	this->length_ = other.length_;
	this->str_ = new char[this->length_+1];
	for (int i = 0; i < this->length_; i++) {
		this->str_[i] = other.str_[i];
	}

	this->str_[this->length_] = '\0';

	return *this;
}

String String::operator+(const String& other) 
{
	String temp;
	temp.length_ = this->length_ + other.length_;
	temp.str_ = new char[temp.length_+1];
	int i = 0;
	for (; i < this->length_; i++) {
		temp.str_[i] = this->str_[i];
	}
	for (int j = 0; j < other.length_; j++, i++) {
		temp.str_[i] = other.str_[j];
	}
	temp.str_[temp.length_] = '\0';
	return temp;
}

char& String::operator[](int index) 
{
	if (this->str_ == nullptr) {
		throw "Error";
	}
	if (index < 0 || index > this->length_) throw "Error";
	return this->str_[index];
}

bool String::operator==(const String& other) 
{
	if (this->length_ != other.length_) return false;
	for (int i = 0; i < this->length_; i++) {
		if (this->str_[i] != other.str_[i]) return false;
	}
	return true;
}

bool String::operator!=(const String& other) 
{
	if (this->length_ != other.length_) return true;
	int count = 0;
	for (int i = 0; i < this->length_; i++) {
		if (this->str_[i] == other.str_[i]) count++;
	}
	if (count == this->length_) {
		return false;
	}
	return true;
}

std::istream& operator >> (std::istream& stream, String& string) 
{
	String temp;
	char c;
	while (stream.peek() != EOF) {
		c = stream.get();
		if (c == '\n' || c == '\t' || c == '\0') {
			break;
		}
		temp.push_back(c);
	}
	string = temp;
	if (string.length_ != 0) string.str_[string.length_] = '\0';
	return stream;
}

std::ostream& operator << (std::ostream& stream, const String& string) 
{
	for (int i = 0; i < string.length_; i++) {
		stream << string.str_[i];
	}
	return stream;
}