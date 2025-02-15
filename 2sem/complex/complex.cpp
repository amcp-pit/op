#include <iostream>

class Complex {
private:
	double real;
	double imag;
public:

	Complex(double re = 0.0, double im = 0.0) : real(re), imag(im){
		std::cout << "I was born (" <<real << ", " << imag <<")\n";
	}

	double re() const {return real;}
	double im() const {return imag;}

};

std::ostream& operator << (std::ostream &out, const Complex& X){
	out << X.re();
	if (X.im() >= 0){
		out << "+";
	}
	out << X.im() << "*i";
	return out;
}


int main(){

	Complex x; // (0, 0)
	// x.real = 1.0; // Нет доступа, real private
	// x.imag = 0.0; // Нет доступа, imag private

	Complex y(1.0, -1.0);
	const Complex i(0, 1);
	Complex z(3);
	// Complex z = x + y;
	//std::cout << "z = " << z << std::endl;

	// std::cout << "x = "<< x.re() <<"+i*"<< x.im() << std::endl;
	std::cout<<"x = " << x <<std::endl;
	std::cout << "y = " << y << std::endl;
	std::cout << "z = " << z << std::endl;
	std::cout << "i = " <<i << std::endl;
	return 0;
}
