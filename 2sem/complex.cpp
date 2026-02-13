#include <iostream>
#include <cmath>

class Complex{
	double real, imag;
public:
//	Complex(double re, double im) {real = re; imag =im;}
/*
	Complex(double re, double im) : real(re), imag(im) {}
	Complex(double re) : real(re), imag(0.0) {}
	Complex() : real(0.0), imag(0.0) {}
*/
	Complex(double re=0.0, double im=0.0) : real(re), imag(im) {}

	double re() const {return real;}
	double im() const {return imag;}
};

std::ostream& operator<<(std::ostream& out, const Complex & x){
	out << x.re();
	if (x.im() >= 0){
		out << "+";
	}
	out << x.im() << "*i";
	return out;
}


int main(){
	Complex a(2.5, -1.3);
//	a.real = 2.5;
//	a.imag = -1.3;
	std::cout << "a = " << a << std::endl;


	const Complex i(0.0, 1.0);
	Complex x(1.0, 1.0);
	std::cout << "x = " << x << std::endl;
/*
	const Complex j = i;
	Complex y = x * x - i + (x + i) * i;
    std::cout << "y = " << y << std::endl;

	Complex z = x * x.conj();
	std::cout << "z = " << x << std::endl;

    std::cout << "|i| = " << i.abs() << std::endl;
	std::cout << "|x| = " << x.abs() << std::endl;
	std::cout << "|y| = " << y.abs() << std::endl;
    std::cout << "|z| = " << z.abs() << std::endl;
*/
	return 0;
}