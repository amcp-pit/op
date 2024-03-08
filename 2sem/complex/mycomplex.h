#pragma once
#include <cmath>
#include <iostream>

class Complex {
	double real_;
	double imag_;
public:
	Complex(double real = 0.0, double imag = 0.0) : real_(real), imag_(imag) {}

	double re() const {
		return real_;
	}

	double im() const;

	double abs() const {
		return sqrt(real_ * real_ + imag_ * imag_);
	}

	Complex conj() const {
		return Complex(real_, -imag_);
	}

	Complex& operator+=(const Complex& right) {
		real_ += right.real_;
		imag_ += right.imag_;
		return *this;
	}

	Complex& operator-=(const Complex& right) {
		real_ -= right.real_;
		imag_ -= right.imag_;
		return *this;
	}

	Complex operator-(const Complex& right) const {
		// Как лучше реализовать арифметический оператор:
		// как для этого оператора или как сделано для оператора +?
		return Complex(real_ - right.real_, imag_ - right.imag_);
	}

	Complex operator*(const Complex& right) const {
		return Complex(real_ * right.real_ - imag_ * right.imag_,
			imag_ * right.real_ + real_ * right.imag_);
	}

	Complex& operator*=(const Complex& right) {
		// Подумать: лучше реализовывать оператор *= через оператор * или наоборот?
		*this = (*this) * right;
		return *this;
	}

	Complex& operator/=(const Complex& right) {
		*this = (*this) / right;
		return *this;
	}

	Complex operator/(const Complex& right) const {
		Complex tmp = right * right.conj();
		if (tmp.real_ == 0) throw "Divide by zero";
		Complex z = (*this) * right.conj();
		z.real_ /= tmp.real_;
		z.imag_ /= tmp.real_;
		return z;
	}

	void print() const;
};

Complex operator+(const Complex& left, const Complex& right);
std::ostream& operator<< (std::ostream& out, const Complex& x);
