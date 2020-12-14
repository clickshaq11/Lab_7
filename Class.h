#pragma once
#include "String.h"
#include "Array.h"
#include <iostream>

class AviaRequest 
{
public:
	AviaRequest();
	AviaRequest(String num, String dest, String name, String date);
	AviaRequest(const AviaRequest& other);
	~AviaRequest();

	String& getFlightNum();
	String& getDestination();
	String& getName();
	String& getDate();

	void setFlightNum(const String& num);
	void setDestination(const String& dest);
	void setName(const String& name);
	void setDate(const String& date);

	AviaRequest& operator = (const AviaRequest& other);

	bool operator > (int num);
	bool operator < (int num);
	bool operator > (AviaRequest& other);
	bool operator < (AviaRequest& other);
	friend bool operator >= (AviaRequest& cur, AviaRequest& other);
	friend bool operator <= (AviaRequest& cur, AviaRequest& other);
	bool operator == (const AviaRequest& other);
	bool operator != (const AviaRequest& other);

	AviaRequest& operator += (int num);
	friend AviaRequest& operator -=(AviaRequest& cur, int num);
	AviaRequest& operator ++();
	friend AviaRequest operator ++(AviaRequest& cur, int);

	friend std::ostream& operator <<(std::ostream& stream, const AviaRequest& curString);
	friend std::istream& operator >>(std::istream& stream, AviaRequest& curString);

private:
	String flightNum_;
	String destination_;
	String name_;
	String date_;
};

String validateDate(AviaRequest& cur);
String validateName(AviaRequest& cur);
String validateFlightNum(AviaRequest& cur);
String validateDestination(AviaRequest& cur);
int translateNum(String num);
String alterateNum(int num);
bool isDataValid(String date);