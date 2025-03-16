#ifndef _STROKA_25_
#define _STROKA_25_
#include <iostream>
#include <string.h>

class stroka{
	char * data_;
	size_t size_;
	void swap(stroka& other) {
		std::swap(data_, other.data_);
		std::swap(size_, other.size_);
	}
public:
	stroka(const char * str="");
	stroka(char);
	stroka(const stroka&);
	stroka(stroka&&);
	~stroka() { delete[] data_; }
	stroka& operator=(const stroka&);
	stroka& operator=(stroka&&);

	size_t length() const { return strlen(data_); }
	size_t size() const { return size_; }
	const char* str() const {return data_;}
	char operator[] (size_t)const;
	stroka& operator+=(const stroka&);
};

stroka operator+(const stroka&, const stroka&);
std::ostream& operator<< (std::ostream&, const stroka&);

bool operator==(const stroka&, const stroka&);
bool operator!=(const stroka&, const stroka&);
bool operator<(const stroka&, const stroka&);
bool operator<=(const stroka&, const stroka&);
bool operator>(const stroka&, const stroka&);
bool operator>=(const stroka&, const stroka&);

#endif