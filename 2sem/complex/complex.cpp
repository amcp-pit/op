#include <iostream>
#include <cmath>

class Complex {
private:
	double real;
	double imag;
public:

	Complex(double re = 0.0, double im = 0.0) : real(re), imag(im) {
		std::cout << "I was born (" <<real << ", " << imag <<")\n";
	}

	Complex(const Complex& other) : real(other.real), imag(other.imag){
		std::cout<< "I was born like a copy (" << real <<", " << imag <<")\n";
	}

	double re() const {return real;}
	double im() const {return imag;}
	double abs() const {return sqrt(real * real + imag * imag);}

	Complex conj() const {
		return Complex(real, -imag);
	}


	Complex operator-(const Complex& right){
		return Complex(real - right.real, imag - right.imag);
	}

	Complex& operator*=(const Complex& y){
		double r = real*y.real - imag*y.imag;
		double i = real*y.imag + imag*y.real;
		real = r;
		imag = i;
		return *this;
	}

	~Complex() {
		std::cout << "Somebody kill me (" << real << ", " << imag <<")\n";
	}
};

std::ostream& operator << (std::ostream &out, const Complex& X){
	out << X.re();
	if (X.im() >= 0){
		out << "+";
	}
	out << X.im() << "*i";
	return out;
}

Complex operator+ (const Complex &left, const Complex &right){
	return Complex( left.re() + right.re(), left.im() + right.im());
}

Complex operator* (const Complex &left, const Complex &right){
	Complex tmp(left);
	tmp *= right;
	return tmp;
}


int main(){

	Complex x; // (0, 0)
	// x.real = 1.0; // Нет доступа, real private
	// x.imag = 0.0; // Нет доступа, imag private

	Complex y(1.0, -1.0);
	const Complex i(0, 1);
	Complex z(3);
	Complex j(i);


	x = z + y + i;
	//std::cout << "z = " << z << std::endl;

	// std::cout << "x = "<< x.re() <<"+i*"<< x.im() << std::endl;
	std::cout<<"x = " << x <<std::endl;
	std::cout << "y = " << y << std::endl;
	std::cout << "z = " << z << std::endl;
	std::cout << "i = " <<i << std::endl;
	std::cout << "|x| = " << x.abs() << std::endl;
	std::cout << "|y| = " << y.abs() << std::endl;
	std::cout << "|i| = " << i.abs() << std::endl;
	z = x + 2;
	std::cout <<"x + 2 = " << z << std::endl;
	z = 2 + x;
	std::cout <<"2 + x = " << z << std::endl;

	z = x - y;
	std::cout << "x - y = " << z << std::endl;
	z = x - 2;
	std::cout << "x - 2 = " << z << std::endl;
	z = Complex(2) - x;
	std::cout << "2 - x = " << z << std::endl;

	z = x * y;
	std::cout << "x * y = " << z << std::endl;
	z = 2 * x;
	std::cout << "2 * x = "<< z << std::endl;
	
	z = x * x.conj();
	std::cout << "z = " << z << std::endl;
	return 0;
}
