#include "mycomplex.h"

void Complex::print() const {
	std::cout << real_;
	if (imag_ >= 0) {
		std::cout << "+";
	}
	std::cout << imag_ << "i" << std::endl;
}

inline double Complex::im() const {
	return imag_;
}

Complex operator+(const Complex& left, const Complex& right) {
	Complex result(left);
	result += right;
	return result;
}

std::ostream& operator<< (std::ostream& out, const Complex& x) {
	out << x.re();
	if (x.im() >= 0) {
		out << "+";
	}
	out << x.im() << "i";
	return out;
}

