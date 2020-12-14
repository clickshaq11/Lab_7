#include <iostream>
#include <fstream>
#include "Array.h"
#include "Class.h"
#include "String.h"

int maxFNumSize(Array<AviaRequest>& arr);
int maxNameSize(Array<AviaRequest>& arr);
int maxDateSize(Array<AviaRequest>& arr);
int maxDestSize(Array<AviaRequest>& arr);

int fileSize(String str);

void printSpaces(const int size1, std::ofstream& stream);

int findMaxFlightnum(Array<AviaRequest> arr);

void printArray(Array<AviaRequest>& arr);

template <class T>
void sort(Array <T>& array);

int translateNumber(String num);

Array<AviaRequest> readFile();
void writeMaxNumber(int max);

int main() 
{
	setlocale(LC_ALL, "Rus");
	Array <AviaRequest> array = readFile();
	int max = findMaxFlightnum(array);
	writeMaxNumber(max);
	std::cout << "Результаты работы программы в файлах output.txt и max_flight_num.txt.";
	return 0;
}

Array<AviaRequest> readFile() 
{
	String path;
	std::cout << "Введите файл, их которого будет происходить ввод\n";
	std::ifstream stream;
	while (!(std::cin >> path)) {
		std::cout << "Файл не открыт. Пожалуйста, введите другое название файла.";
		std::cin.clear();
		std::cin.get();
	}
	stream.open(path.getData());
	int size = fileSize(path);
	int arrsize = size / 4;
	if (size % 4 != 0) {
		std::cout << "В файле отсутствует необходимое количество строк (кратное 4).\n Это может привести к неполной таблице.\n";
	}
	Array<AviaRequest> arr(arrsize);
	for (int i = 0; i < arrsize; i++) {
		stream >> arr[i];
	}
	stream.close();
	sort(arr);
	printArray(arr);
	return arr;
}

void writeMaxNumber(int max)
{
	std::ofstream stream;
	stream.open("max_flight_num.txt");
	stream << "Максимальное значение номера полета равно: \n";
	stream << max;
	stream.close();
}

int maxFNumSize(Array<AviaRequest>& arr)
{
	int max = 12;
	for (int i = 0; i < arr.getSize(); i++) {
		if (arr[i].getFlightNum().getLen() > max) {
			max = arr[i].getFlightNum().getLen();
		}
	}
	return max;
}

int maxNameSize(Array<AviaRequest>& arr)
{
	int max = 14;
	for (int i = 0; i < arr.getSize(); i++) {
		if (arr[i].getName().getLen() > max) {
			max = arr[i].getName().getLen();
		}
	}
	return max;
}

int maxDateSize(Array<AviaRequest>& arr)
{
	int max = 12;
	for (int i = 0; i < arr.getSize(); i++) {
		if (arr[i].getDate().getLen() > max) {
			max = arr[i].getDate().getLen();
		}
	}
	return max;
}

int maxDestSize(Array<AviaRequest>& arr)
{
	int max = 17;
	for (int i = 0; i < arr.getSize(); i++) {
		if (arr[i].getDate().getLen() > max) {
			max = arr[i].getDate().getLen();
		}
	}
	return max;
}

int fileSize(String str)
{
	std::ifstream stream;
	stream.open(str.getData());
	int count = 0;
	while (stream.ignore(32265, '\n')) count++;
	stream.close();
	return count;
}

int findMaxFlightnum(Array<AviaRequest> arr)
{
	int max = 0;
	for (int i = 0; i < arr.getSize(); i++) {
		if (arr[i] > max) {
			max = translateNumber(arr[i].getFlightNum());
		}
	}
	return max;
}

void printArray(Array<AviaRequest>& arr)
{
	int mfnumsize = maxFNumSize(arr);
	int mnamesize = maxNameSize(arr);
	int mdatesize = maxDateSize(arr);
	int mdestsize = maxDestSize(arr);
	std::ofstream stream;
	stream.open("output.txt");
	stream << "Номер рейса ";
	printSpaces(mfnumsize - 12, stream);
	stream << "Пункт назначения ";
	printSpaces(mdestsize - 17, stream);
	stream << "Имя пассажира ";
	printSpaces(mnamesize - 14, stream);
	stream << "Дата вылета";
	stream << "\n";
	for (int i = 0; i < arr.getSize(); i++) {
		stream << arr[i].getFlightNum();
		for (int j = 0; j < mfnumsize - arr[i].getFlightNum().getLen(); j++) {
			stream << " ";
		}
		stream << arr[i].getDestination();
		for (int j = 0; j < mdestsize - arr[i].getDestination().getLen(); j++) {
			stream << " ";
		}
		stream << arr[i].getName();
		for (int j = 0; j < mnamesize - arr[i].getName().getLen(); j++) {
			stream << " ";
		}
		stream << arr[i].getDate();
		for (int j = 0; j < mdatesize - arr[i].getDate().getLen(); j++) {
			stream << " ";
		}
		stream << '\n';
	}
}

void printSpaces(const int size1, std::ofstream& stream) {
	for (int i = 0; i < size1; i++) {
		stream << " ";
	}
}

int translateNumber(String num)
{
	int len = num.getLen();
	long long number = 0;
	for (int i = 0; i < len; i++) {
		if (num[i] >= 48 && num[i] <= 57) {
			number += static_cast<long long>((static_cast<int>(num.getData()[i]) - 48) * (pow(10, len - i - 1)));
		}
		else {
			return 0;
		}
	}
	return number;
}

template <class T>
void sort(Array <T>& array)
{
	T temp;
	for (int i = 1; i < array.getSize(); i++)
	{
		temp = array[i];
		int j = i - 1;
		for (; j >= 0 && array[j] > temp; j--)
		{
			array[j + 1] = array[j];
		}
		array[j + 1] = temp;
	}
}

