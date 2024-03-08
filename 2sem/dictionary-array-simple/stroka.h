#pragma once
#include <string.h>
#include <utility>

class stroka{
	char * data_;
	size_t size_;
	void swap(stroka& other){
		std::swap(data_, other.data_);
		std::swap(size_, other.size_);
	}
public:
	stroka(const char * str="");
	stroka(size_t N);
	stroka(const stroka&);
	~stroka();
	stroka& operator=(const stroka&);

	size_t length() const {return strlen(data_);}
	size_t size() const {return size_;}
	const char* str() const {return data_;}
	stroka& operator+=(const stroka&);
	char operator[](size_t index) const;
};

bool operator==(const stroka& left, const stroka& right);
bool operator!=(const stroka& left, const stroka& right);
bool operator<(const stroka& left, const stroka& right);

stroka operator+(const stroka&, const stroka&);

#include <iostream>
std::ostream& operator<<(std::ostream& out, const stroka& X);
