//
// Лабораторная работа №10. Классы. Целые числа с длинной арифметикой
// bignum.cpp
//
#include "bignum.h"
#include <exception>
#include <climits>
#include <cmath>
#include <cctype>
#include <string>

bignum::bignum() : digits(), negative(false)
{}

bignum::bignum(int64_t number) : digits()
{
	bool a = true;
    if (number < 0) {
        number = -number;
        negative = true;
    }
    else
        negative = false;
    while (number > 0) {
		if (a)
		{
			digits[0] = number % 10;
			number = number / 10;
			a = false;
		}
		else
		{
			digits.append(number % 10);
			number = number / 10;
		}
    }
}

bignum::bignum(int number) : digits()
{
	bool a = true;
	if (number < 0) {
		number = -number;
		negative = true;
	}
	else
		negative = false;
	while (number > 0) {
		if (a)
		{
			digits[0] = number % 10;
			number = number / 10;
			a = false;
		}
		else
		{
			digits.append(number % 10);
			number = number / 10;
		}
	}
}


bignum::bignum(const std::string a)
{
	try {
		if (a[0] == '-')
		{
			negative = true;
			digits.resize(a.size() - 1);
		}
		else
		{
			negative = false;
			digits.resize(a.size());
		}
		int j = 0;
			for (int i = a.size()-1;i>=0 && i >= a.size()-digits.count(); --i)
			{
				if (!(a[i] >= '0' && a[i] <='9')) throw std::invalid_argument("Строка не число!!!");
				digits[j] = a[i] - '0';
				j++;
			}
		
	
	}
	catch (std::invalid_argument a)
	{
		std::cout << a.what();
	}
}

bignum::operator int64_t() const
{
    if (digits.count() > (int)ceil(log10(INT64_MAX)))
        throw std::length_error("Bignum is too big for int64!");
    
    int64_t result = 0;
    if (digits.count() == 0)
        return result;
    
    int64_t mul = (int64_t)::pow(10, digits.count()-1);
    for (int i = digits.count() - 1; i >= 0; --i)
    {
        result = result + mul * digits[i];
        mul /= 10;
    }
    
    if (negative)
        result *= -1;
        
    return result;
}

bignum::operator int() const
{
	if (digits.count() > (int)ceil(log10(INT_MAX)))
		throw std::length_error("Bignum is too big for int!");

	int result = 0;
	if (digits.count() == 0)
		return result;

	int mul = (int)::pow(10, digits.count() - 1);
	for (int i = digits.count() - 1; i >= 0; --i)
	{
		result = result + mul * digits[i];
		mul /= 10;
	}

	if (negative)
		result *= -1;

	return result;
}

bignum::operator std::string() const
{
	std::string s;
	if (negative) s += '-';
	for (int i = digits.count()-1; i >= 0; --i)
		s += digits[i]+'0';
	return s;
}

bool bignum::operator==(const bignum &other) const
{
    if (negative != other.negative ||
        digits.count() != other.digits.count())
        return false;
    
    return digits == other.digits;
}

bool bignum::operator!=(const bignum &other) const
{
    return !(*this == other);
}

bool bignum::operator>(const bignum & other) const //где то тут надл что то исправиться 
{
	if (other.negative && !negative) return true;
	if (!other.negative && negative) return false;
	if (!other.negative && !negative)
		if (this->size() > other.size()) return true;
		else
			if (this->size() < other.size()) return false;
			else
				for (int i = other.size() - 1; i >= 0; --i)
					if (digits[i] > other.digits[i]) return true;
	if (other.negative && negative)
		if (this->size() < other.size()) return true;
		else
			if (this->size() > other.size()) return false;
			else
				for (int i = other.size() - 1; i >= 0; --i)
					if (digits[i] < other.digits[i]) return true;
	return false;
}

bool bignum::operator<=(const bignum & other) const
{

	if (!other.negative && negative) return true;
	if (other.negative && !negative) return false;
	if (!other.negative && !negative)
		if (this->size() <= other.size()) return true;
		else
			if (this->size() > other.size()) return false;
			else
				for (int i = other.size() - 1; i >= 0; --i)
					if (digits[i] <= other.digits[i]) return true;
	if (other.negative && negative)
		if (this->size() >= other.size()) return true;
		else
			if (this->size() < other.size()) return false;
			else
				for (int i = other.size() - 1; i >= 0; --i)
					if (digits[i] >= other.digits[i]) return true;
	return false;
}


bool bignum::operator<(const bignum & other) const
{
	if (!other.negative && negative) return true;
	if (other.negative && !negative) return false;
	if (!other.negative && !negative)
		if (this->size() < other.size()) return true;
		else
			if (this->size() > other.size()) return false;
			else
				for (int i = other.size() - 1; i >= 0; --i)
					if (digits[i] < other.digits[i]) return true;
	if (other.negative && negative)
		if (this->size() > other.size()) return true;
		else
			if (this->size() < other.size()) return false;
			else
				for (int i = other.size() - 1; i >= 0; --i)
					if (digits[i] > other.digits[i]) return true;
	return false;
}

bool bignum::operator>=(const bignum & other) const
{
	if (other.negative && !negative) return true;
	if (!other.negative && negative) return false;
	if (!other.negative && !negative)
		if (this->size() >= other.size()) return true;
		else
			if (this->size() < other.size()) return false;
			else
				for (int i = other.size() - 1; i >= 0; --i)
					if (digits[i] >= other.digits[i]) return true;
	if (other.negative && negative)
		if (this->size() <= other.size()) return true;
		else
			if (this->size() > other.size()) return false;
			else
				for (int i = other.size() - 1; i >= 0; --i)
					if (digits[i] <= other.digits[i]) return true;
	return false;
}

bignum bignum::operator-() const
{
	bool a = true;
	if (negative) a = false;
	
	return bignum(a, digits);
}

bignum bignum::operator+(const bignum & other) const
{
	bignum rez;
	int  sum;
	int ost = 0;
	int min_size, max_size;
	if (this->size() > other.size())
	{
		max_size = this->size();
		min_size = other.size();
	}
	else
	{
		max_size = other.size();  min_size = this->size();
	}
	if (this->is_negative() && other.is_negative() || !this->is_negative() && !other.is_negative())
	{
		rez.negative = this->is_negative();
		for (int i = 0; i < min_size; ++i)
		{
			sum = digits[i] + other.digits[i] + ost;
			ost = sum / 10;
			if (i == 0) rez.digits[i] = (sum % 10);
			else
				rez.digits.append(sum % 10);
		}
		if (this->size() < max_size)
		{
			for (int i = min_size; i < max_size; ++i)
			{
				sum = other.digits[i] + ost;
				ost = sum / 10;
				rez.digits.append(sum % 10);
			}
		}
		if (other.size() < max_size)
			for (int i = min_size; i < max_size; ++i)
			{
				sum = this->digits[i] + ost;
				ost = sum / 10;
				rez.digits.append(sum % 10);
			}

		if (ost!=0) rez.digits.append(ost);
		
	}
	if (this->is_negative() && !other.is_negative() || !this->is_negative() && other.is_negative())
	{
		
		if ((abs(other)<abs(*this) && this->is_negative()) || (!(abs(other)<abs(*this)) && other.is_negative())) rez.negative = true;
		else
			rez.negative = false;

		for (int i = 0; i < min_size; ++i)
		{
			sum = digits[i] - other.digits[i] - ost;
			if (sum < 0)
			{
				ost = 1;
				sum += 10;
			}
			if (i == 0) rez.digits[i] = (sum);
			else
				rez.digits.append(sum);
		}
		if (this->size() < max_size)
		{
			for (int i = min_size; i < max_size; ++i)
			{
				sum = other.digits[i] - ost;
				if (sum < 0)
				{
					ost = 1;
					sum += 10;
				}
				else
					ost = 0;
				rez.digits.append(sum);
			}
		}
		if (other.size() < max_size)
			for (int i = min_size; i < max_size; ++i)
			{	
				sum = this->digits[i] - ost;
				if (sum < 0)
				{
					ost = 1;
					sum += 10;
				}
				else
					ost = 0;
				rez.digits.append(sum);
			}

		//if (sum != 0) rez.digits.append(sum);
	}
	while (rez.size() != 1 && rez.digits[rez.size() - 1] == 0) rez.digits.remove(rez.size() - 1);
	
	 return rez;
}

bignum & bignum::operator+=(const bignum & other)
{
	*this = *this + other;
	return *this;
}

bignum bignum::operator-(const bignum & other) const
{
	
	return  *this+(-other);
}

bignum & bignum::operator-=(const bignum & other)
{
	*this = *this - other;
	return  *this;
}

bignum bignum::operator*(const bignum & other) const
{
	bignum rez=*this;
	for (int64_t i = 1; i < abs(int64_t(other)); ++i)
		rez += *this;
	if (this->is_negative() == other.is_negative()) rez.negative = false;
	else
		if(other.is_negative()) rez.negative = true;
	return rez;
}

bignum & bignum::operator*=(const bignum & other)
{
	*this = *this * other;
	return  *this;
}

bignum bignum::pow(const bignum & exp) const
{
	bignum rez = *this;
	for (int i = 1; i < exp; ++i)
		rez *= *this;
	return rez;
}

bignum bignum::operator/(const bignum & other) const
{
	bignum rez = *this;
	bignum i = -1;
	for (; rez > bignum(0); i += 1)
	{
		rez -= other;
	}
	return i;
}

bignum & bignum::operator/=(const bignum & other)
{
	*this = *this / other;
	return *this;
}

bignum bignum::operator%(const bignum & other) const
{
	bignum rez = *this / other;
	return bignum(*this-rez*other);
}

bignum & bignum::operator%=(const bignum & other)
{
	*this = *this % other;
	return *this;
}

bignum bignum::gcd(const bignum & other) const
{
	bignum rez = *this;
	bignum rez1 = *this;
	bignum other1 = other;
	while ((rez % other1) > bignum(0))
	{
		rez %= other1;
		other1 = rez - rez1 / other1 * rez1%other1;
		rez1 = rez;
		std::cout << std::string(rez) << std::endl;
		std::cout << std::string(other1) << std::endl;
		return rez;
	}
}




//std::istream &operator>>(std::istream &is, bignum &b)
//{
//    std::string str;
//    while (is.peek() == '-' || isdigit(is.peek()))
//    {
//        str += is.get();
//    }
//    b = bignum(str.c_str());
//    return is;
//}

//std::ostream &operator<<(std::ostream &os, const bignum &b)
//{
//    os << (string)b;
//    return os;
//}
