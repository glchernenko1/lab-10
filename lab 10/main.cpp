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
	bignum d(8);
	//cout << string(c);
	cout << c.gcd(462)<<endl;
	//cout << bignum(1071) % bignum(462) << endl;
	cout << d.is_prime()<<endl;
    system("pause");

	return 0;
}
