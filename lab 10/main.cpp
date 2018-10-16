//
// Лабораторная работа №10. Классы. Целые числа с длинной арифметикой
// main.cpp
//
#include <iostream>
#include "bignum.h"
#include <string>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	string a = "1071";
	bignum c(a);
	//cout << string(c);
	c = c - bignum(a) - bignum(461);
	cout<<string(c);
    system("pause");

	return 0;
}
