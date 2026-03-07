#ifndef _STROKA_26_
#define _STROKA_26_
#include <iostream>
#include <cstring>

class stroka{
	size_t size_;
	char * data_;
	void swap(stroka& other) noexcept {
		std::swap(data_, other.data_);
		std::swap(size_, other.size_);
	}
public:
	stroka(const char * str="") : size_(std::strlen(str) + 1), data_(new char[size_]) {
	    std::memcpy(data_, str, size_);
	}

	stroka(char ch) : size_(4), data_(new char[size_]) {
	    data_[0] = ch;
	    data_[1] = '\0';
	}

	stroka(const stroka& other) : size_(other.size_), data_(new char[size_]) {
	    std::memcpy(data_, other.data_, size_);
	}

	stroka& operator=(const stroka& other) {
		if (this != &other){
			stroka tmp(other);
			swap(tmp);
		}
		return *this;
	}

#ifndef NOMOVESEMANTICS
	stroka(stroka&& other) noexcept : size_(0), data_(nullptr) {
		swap(other);
	}

	stroka& operator=(stroka&& other) noexcept {
		if (this != &other) {
			swap(other);
		}
		return *this;
	}
#endif

	~stroka() {
		delete[] data_;
	}

	size_t length() const { return std::strlen(data_); }
	size_t size() const { return size_; }
	const char* str() const { return data_; }

	char operator[] (size_t index) const {
		if (index >= size_){
			throw std::out_of_range("Out of string limits");
		}
		return  data_[index];
	}

	stroka& operator+=(const stroka&);
};

stroka operator+(const stroka&, const stroka&);

bool operator==(const stroka&, const stroka&);
bool operator!=(const stroka&, const stroka&);
bool operator<(const stroka&, const stroka&);
bool operator<=(const stroka&, const stroka&);
bool operator>(const stroka&, const stroka&);
bool operator>=(const stroka&, const stroka&);

std::ostream& operator<< (std::ostream&, const stroka&);

#endif
