#include "dyn_array.h"

void dyn_array::copy(const datatype * from, datatype * to, int size)
{
	for (int i = 0; i < size; ++i) to[i] = from[i];
}

void dyn_array::swap(dyn_array &a)
{
	std::swap(size, a.size);
	std::swap(data, a.data);
}

dyn_array::dyn_array()
{
	size = 1;
	data = new datatype[size];
	data[0] = 0;
}

dyn_array::dyn_array(int size): size(size)
{
	try
	{	if (size <= 0) throw std::invalid_argument("Отрицательный размер!!!" );

		data = new datatype[size];
		for (int i = 0; i < size; ++i) data[i] = 0;
	}
	catch (std::invalid_argument a)
	{
		std::cout << a.what();
	}
}

dyn_array::~dyn_array()
{
	
	if (data!=nullptr)
	delete[] data;

}

/*dyn_array::dyn_array( dyn_array && d)
{
	swap(d);
}
*/
dyn_array::dyn_array(const dyn_array & d)
{
	size = d.size;
	data = new datatype[size];
	for (int i = 0; i < size; ++i)
		data[i] = d.data[i];

}


dyn_array & dyn_array::operator=( dyn_array  d)
{
	swap(d);
	return *this;
}

void dyn_array::sort(bool a)
{
	for (int i = 0; i < size - 1; ++i)
		for (int j = 0; j < size - 1; ++j)
			if ((data[j] < data[j + 1]) == a)
				std::swap(data[j], data[j + 1]);
}

void dyn_array::unique()
{
	this->sort();
	for (int i = 0; i < size - 1; )
		if (data[i] == data[i + 1]) this->remove(i);
		else
			++i;

}

void dyn_array::append(dyn_array & a)
{
	for (int i = 0; i < a.size; ++i)
		this->append(a[i]);
}

dyn_array & dyn_array::operator=( dyn_array && d)
{
	swap(d);
	return *this;
}

void dyn_array::resize(int new_size)
{
	try
	{
		if (size <= 0) throw std::invalid_argument("Отрицательный размер!!!");
		if (new_size == size) return;
		datatype *data_new;
		data_new = new datatype[new_size];
		if (new_size > size)
			copy(data, data_new, size);
		else
			copy(data, data_new, new_size);
		if (data) delete[] data;
		data = data_new;
		size = new_size;
	}
	catch (std::invalid_argument a)
	{
		std::cout << a.what();
	}
}

void dyn_array::append(const datatype & x)
{

		this->resize(size + 1);
		data[size - 1] = x;
}

void dyn_array::insert(int index, const datatype & x)
{ 
	try {
		if (index > size) throw std::out_of_range("Вставка за пределы массива!!! ");
		this->resize(size + 1);
		for (int i = size - 1; index < i; --i)
			std::swap(data[i], data[i - 1]);
		data[index] = x;
	}
	catch (std::out_of_range a)
	{
		std::cout << a.what();
	}
}

void dyn_array::remove(int index)
{
	try {
		if (index > size) throw std::out_of_range("Удаление за пределами массива!!! ");

	for (int i = index; i < size - 2; ++i)
		std::swap(data[i], data[i + 1]);
	this->resize(size - 1);
	}
	
	catch (std::out_of_range a)
	{
		std::cout << a.what();
	}
}

int dyn_array::find(const datatype & x) const
{
	for (int i = 0; i < size; ++i)
		if (data[i] == x) return i;
	return -1;
}

std::istream & operator>>(std::istream & is, dyn_array & p)
{
	int a;
	is >> a;

	p.resize(a); 
	for (int i = 0; i < p.size; ++i)
	{
		is >> p.data[i];
	}
	p.size = a;
	return is;
}

std::ostream & operator<<(std::ostream & os, const dyn_array & p)
{
	os << p.size;
	for (int i = 0; i < p.size; ++i)
	{
		os <<" "<< p.data[i];
	}
	return os;
}

bool operator==(dyn_array a, dyn_array b)
{
	if (a.size == b.size)
		for (int i = 0; i < a.size && a[i] == b[i]; ++i)
			if (i == a.size - 1) return true;
	return false;
}

