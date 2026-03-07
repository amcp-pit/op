#include "stroka.hpp"

stroka& stroka::operator+=(const stroka& other) {
	size_t len1 = length();
	size_t len2 = other.length();
	if (len1 + len2 + 1 > size_){
		size_ = len1 + len2 + 1;
		char * tmp = new char [size_];
		std::memcpy(tmp, data_, len1);
		delete[] data_;
		data_ = tmp;
	}
	std::memcpy(data_+len1, other.data_, len2 + 1);
	return *this;
}

stroka operator+(const stroka& left, const stroka& right) {
	stroka result(left);
	result += right;
	return result;
}

std::ostream& operator<< (std::ostream& out, const stroka& X) {
	out << X.str();
	return out;
}

bool operator==(const stroka& left, const stroka& right) {
	return std::strcmp(left.str(), right.str()) == 0;
}

bool operator!=(const stroka& left, const stroka& right) {
    return std::strcmp(left.str(), right.str()) != 0;
}

bool operator<(const stroka& left, const stroka& right) {
    return std::strcmp(left.str(), right.str()) < 0;
}

bool operator<=(const stroka& left, const stroka& right) {
    return std::strcmp(left.str(), right.str()) <= 0;
}

bool operator>(const stroka& left, const stroka& right) {
    return std::strcmp(left.str(), right.str()) > 0;
}

bool operator>=(const stroka& left, const stroka& right) {
    return std::strcmp(left.str(), right.str()) >= 0;
}
