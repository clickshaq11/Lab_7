#include "Class.h"
#include "String.h"
#include <cmath>
#include <iomanip>

AviaRequest::AviaRequest() 
{
	this->flightNum_ = String();
	this->destination_ = String();
	this->name_ = String();
	this->date_ = String();
}

AviaRequest::AviaRequest(String num, String dest, String name, String date) 
{
	if (translateNum(num) == 0) {
		this->flightNum_ = String();
		this->destination_ = String();
		this->name_ = String();
		this->date_ = String();
	}
	else {
		this->flightNum_ = num;
		this->destination_ = dest;
		this->name_ = name;
		this->date_ = date;
	}
}

AviaRequest::AviaRequest(const AviaRequest& other) 
{
	if (translateNum(other.flightNum_) == 0) {
		this->flightNum_ = String();
		this->destination_ = String();
		this->name_ = String();
		this->date_ = String();
	}
	else {
		this->flightNum_ = other.flightNum_;
		this->destination_ = other.destination_;
		this->name_ = other.name_;
		this->date_ = other.date_;
	}
}

AviaRequest::~AviaRequest() 
{
	
}

String& AviaRequest::getFlightNum()
{
	return this->flightNum_;
}

String& AviaRequest::getDestination()
{
	return this->destination_;
}

String& AviaRequest::getName()
{
	return this->name_;
}

String& AviaRequest::getDate()
{
	return this->date_;
}

void AviaRequest::setFlightNum(const String& num) {
	this->flightNum_ = num;
}

void AviaRequest::setDestination(const String& dest) {
	this->destination_ = dest;
}

void AviaRequest::setName(const String& name) {
	this->name_ = name;
}

void AviaRequest::setDate(const String& date) {
	this->date_ = date;
}

bool AviaRequest::operator<(int num)
{
	if (translateNum(this->getFlightNum()) < num) return true;
	return false;
}

bool AviaRequest::operator>(AviaRequest& other)
{
	if (this->date_.getData() == "###" || other.date_.getData() == "###") {
		std::cout << "Одна или более введенных дат не прошли проверку." << "\n";
		return false;
	}
	char *date1 = this->date_.getData();
	char* date2 = other.date_.getData();
	char* day1 = new char[3];
	char* day2 = new char[3];
	day1[0] = date1[0];
	day1[1] = date1[1];
	day1[2] = '\0';
	day2[0] = date2[0];
	day2[1] = date2[1];
	day2[2] = '\0';
	int iday1 = translateNum(String(day1));
	int iday2 = translateNum(String(day2));
	char* month1 = new char[3];
	char* month2 = new char[3];
	month1[0] = date1[3];
	month1[1] = date1[4];
	month1[2] = '\0';
	month2[0] = date2[3];
	month2[1] = date2[4];
	month2[2] = '\0';
	int imonth1 = translateNum(String(month1));
	int imonth2 = translateNum(String(month2));
	char* year1 = new char[5];
	char* year2 = new char[5];
	for (int i = 0; i < 4; i++) {
		year1[i] = date1[i + 6];
		year2[i] = date2[i + 6];
	}
	year1[4] = '\0';
	year2[4] = '\0';
	int iyear1 = translateNum(String(year1));
	int iyear2 = translateNum(String(year2));
	if (iyear1 > iyear2) {
		return true;
	}
	else if (iyear1 == iyear2){
		if (imonth1 > imonth2) {
			return true;
		}
		else if (imonth1 == imonth2) {
			if (iday1 > iday2) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool AviaRequest::operator==(const AviaRequest& other)
{
	if (this->flightNum_ == other.flightNum_
		&& this->date_ == other.date_
		&& this->name_ == other.name_
		&& this->destination_ == other.destination_) {
		return true;
	}
	return false;
}

bool AviaRequest::operator!=(const AviaRequest& other) 
{
	return !(*this == other);
}

AviaRequest& AviaRequest::operator+=(int num)
{
	this->flightNum_ = alterateNum(translateNum(this->flightNum_) + num);
	return *this;
}

AviaRequest& AviaRequest::operator=(const AviaRequest& other)
{
	this->flightNum_ = other.flightNum_;
	this->date_ = other.date_;
	this->destination_ = other.destination_;
	this->name_ = other.name_;
	return *this;
}

AviaRequest& AviaRequest::operator++() 
{
	this->flightNum_ = alterateNum(translateNum(this->flightNum_) + 1);
	return *this;
}	

AviaRequest& operator-=(AviaRequest& cur, int num)
{
	cur.setFlightNum(cur.getFlightNum() + num);
	return cur;
}

AviaRequest operator++(AviaRequest& cur, int) 
{
	AviaRequest temp(cur);
	cur.setFlightNum(translateNum(cur.getFlightNum()) + 1);
	return temp;
}

std::ostream& operator<<(std::ostream& stream, const AviaRequest& curRequest)
{
	stream << curRequest.flightNum_ << curRequest.destination_ << curRequest.name_ << curRequest.date_ << "\n";
	return stream;
}

std::istream& operator>>(std::istream& stream, AviaRequest& curString)
{
	AviaRequest temp;
	stream >> temp.flightNum_ >> temp.destination_ >> temp.name_ >> temp.date_;
	String tempFlightNum = validateFlightNum(temp);
	String tempDestination = validateDestination(temp);
	String tempName = validateName(temp);
	String tempDate = validateDate(temp);
	std::cout << tempFlightNum << "|" << tempDestination << "|" << tempName << "|" << tempDate << "\n";
	if (tempDate.getLen() == 0) {
		tempDate = String("###");
	}
	if (tempFlightNum.getLen() == 0) {
		tempFlightNum = String("###");
	}
	if (tempDestination.getLen() == 0) {
		tempDestination = String("###");
	}
	if (tempName.getLen() == 0) {
		tempName = String("###");
	}
	curString = AviaRequest(tempFlightNum, tempDestination, tempName, tempDate);
	return stream;
}

bool AviaRequest::operator>(int num)
{
	if (translateNum(this->getFlightNum()) > num) return true;
	return false;
}

bool operator<=(AviaRequest& cur, AviaRequest& other)
{
	int num1 = translateNum(cur.getFlightNum());
	int num2 = translateNum(other.getFlightNum());
	if (num1 <= num2) return true;
	return false;
}

bool operator>=(AviaRequest& cur, AviaRequest& other)
{
	int num1 = translateNum(cur.getFlightNum());
	int num2 = translateNum(other.getFlightNum());
	if (num1 >= num2) return true;
	return false;
}

String validateDate(AviaRequest& cur)
{
	char* date = cur.getDate().getData();
	if (cur.getDate().getLen() == 10) {
		for (int i = 0; i < 2; i++) {
			if (static_cast<int>(date[i]) < 48 || static_cast<int>(date[i]) > 57) {
				return String("###");
			}
		}
		if (date[2] != '.' && date[2] != '-') return String("###");
		for (int i = 3; i < 5; i++) {
			if (static_cast<int>(date[i]) < 48 || static_cast<int>(date[i]) > 57) {
				return String("###");
			}
		}
		if (date[5] != '.' && date[5] != '-') return String("###");
		for (int i = 6; i < 10; i++) {
			if (static_cast<int>(date[i]) < 48 || static_cast<int>(date[i]) > 57) {
				return String("###");
			}
		}
		if (date[10] != '\0') return String("###");
		bool isValid = isDataValid(cur.getDate());
		if (!isValid) return String("###");
		return cur.getDate();
	}
	return String("###");
}

String validateName(AviaRequest& cur)
{
	char* name = cur.getName().getData();
	if (name == "###") return String("###");
	int len = cur.getName().getLen();
	int spaces = 0;
	if (static_cast<int>(name[0]) < 65 || static_cast<int>(name[0]) > 90) return String("1st char is not cap letter");
	int i = 1;
	while (name[i] != ' ') {
		if (static_cast<int>(name[i]) < 97 || static_cast<int>(name[i]) > 122) return String("name is not written in lowercase");
		i++;
	}
	i++;
	if (static_cast<int>(name[i]) < 65 || static_cast<int>(name[i]) > 90) return String("1st char of surname is not cap");
	i++;
	for (i; i < len; i++) {
		if (static_cast<int>(name[i]) < 97 || static_cast<int>(name[i]) > 122) return String("surname is not written in lowercase");
	}
	if (name[len] != '\0') return String("String isn\'t closed");
	return cur.getName();
}

String validateFlightNum(AviaRequest& cur)
{
	char* num = cur.getFlightNum().getData();
	int len = cur.getFlightNum().getLen();
	for (int i = 0; i < len; i++) {
		if (static_cast<int>(num[i]) < 48 || static_cast<int>(num[i]) > 57) return String("invalid num");
	}
	if (num[len] != '\0') return String("String isn\'t closed");
	return cur.getFlightNum();
}

String validateDestination(AviaRequest& cur)
{
	char* dest = cur.getDestination().getData();
	int len = cur.getDestination().getLen();
	if (static_cast<int>(dest[0]) < 65 || static_cast<int>(dest[0]) > 90) return String("1st char is not cap letter");
	for (int i = 1; i < len; i++) {
		if (static_cast<int>(dest[i]) < 97 || static_cast<int>(dest[i]) > 122) return String("1st char is not cap letter");
	}
	if (dest[len] != '\0') return String("String isn\'t closed");
	return cur.getDestination();
}

int translateNum(String num) 
{
	int len = num.getLen();
	long long number = 0;
	for (int i = 0; i < len; i++) {
		if (num[i] >= 48 && num[i] <= 57) {
			number += (static_cast<short int>(num.getData()[i])-48) * pow(10, len - i - 1);
		}
		else {
			return 0;
		}
	}
	return number;
}

String alterateNum(int num)
{
	String temp;
	int tempnum = num;
	int tempnum2 = num;
	int count = 0;
	while (tempnum) {
		count++;
		tempnum /= 10;
	}
	int k = 0;
	for (int i = 0; i < count; i++) {
		k = tempnum2 / (pow(10, count - i - 1));
		tempnum2 = tempnum2 % static_cast<int>(pow(10, count - i - 1));
		temp.push_back(static_cast<char>(k + 48));
	}
	return temp;
}

bool isDataValid(String date)
{
	char* day = new char[3];
	char* month = new char[3];
	char* year = new char[5];
	day[0] = date.getData()[0];
	day[1] = date.getData()[1];
	day[2] = '\0';
	String sday(day);
	month[0] = date.getData()[3];
	month[1] = date.getData()[4];
	month[2] = '\0';
	String smonth(month);
	for (int i = 0; i < 4; i++) {
		year[0] = date.getData()[i + 6];
	}
	year[4] = '\0';
	String syear(year);
	int iday = translateNum(sday);
	int imonth = translateNum(smonth);
	int iyear = translateNum(syear);
	if (iday < 1 || iday > 31) return false;
	if (imonth < 1 || imonth > 12) return false;
	bool isLeap = false;
	if (iyear % 4 == 0 && iyear % 400 == 0) {
		isLeap = true;
	} else {
		if (iyear % 4 == 0 && iyear % 100 == 0) {
			isLeap = false;
		}
	}
	if (imonth == 2 && iday > 29 && isLeap == true) {
		return false;
	}
	if (imonth == 2 && iday > 28 && isLeap == false) {
		return false;
	}
	if (imonth == 4 || imonth == 6 || imonth == 9 || imonth == 11) {
		if (iday > 30) {
			return false;
		}
	}
	return true;
}
