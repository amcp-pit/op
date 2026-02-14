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
	Complex(double re=0.0, double im=0.0) : real(re), imag(im) {
		std::cout << "I was born (" << re << ", " << im << ")\n";
	}

	Complex(const Complex & other): real(other.real), imag(other.imag) {
		std::cout << "I was born like a copy (" << real << ", " << imag << ")\n";
	}

    ~Complex() {
        std::cout<< "Somebody kill me :'( " << real << ", " << imag << std::endl;
    }

	Complex conj() const {
		return Complex(real, -imag);
	}

	double re() const {return real;}
	double im() const {return imag;}
	double abs() const {
		return std::sqrt(real*real+imag*imag);
	}
/*	Complex operator+(const Complex& y) const {
		return Complex(real + y.real, imag + y.imag);
	}
*/

	Complex& operator+=(const Complex& other){
		real += other.real;
		imag += other.imag;
		return *this;
	}

    Complex& operator-=(const Complex& other){
        real -= other.real;
        imag -= other.imag;
        return *this;
    }

    Complex& operator*=(const Complex& other){
        double tmp = real*other.real - imag*other.imag;
        imag = real*other.imag + imag*other.real;
		real = tmp;
        return *this;
    }

    Complex& operator/=(const Complex& other){
        double num = real*other.real + imag*other.imag;
        double denum = other.real*other.real + other.imag*other.imag;
        real = num / denum;
		imag = (imag*other.real - real*other.imag) / denum;
        return *this;
    }
/*
	bool operator==(const Complex& other){
		return (real==other.real) && (imag == other.imag);
	}
*/
	friend bool operator==(const Complex& , const Complex& );

};

std::ostream& operator<<(std::ostream& out, const Complex & x){
	out << x.re();
	if (x.im() >= 0){
		out << " + ";
	}
	out << x.im() << " * i";
	return out;
}

double abs(const Complex& x){
	//return std::sqrt(x.re()*x.re() + x.im()*x.im());
	return x.abs();
}

/*
Complex operator+(const Complex &x, const Complex &y){
	return Complex(x.re() + y.re(), x.im() + y.im());
}
*/

Complex operator+(Complex x, const Complex &y){
    return x+=y;
}

Complex operator-(Complex x, const Complex &y){
    return x-=y;
}

Complex operator*(Complex x, const Complex &y){
    return x*=y;
}

Complex operator/(Complex x, const Complex &y){
    return x/=y;
}
/*
bool operator==(const Complex& left, const Complex& right){
    return (left.re()==right.re()) && (left.im() == right.im());
}
*/

bool operator==(const Complex& left, const Complex& right){
    return (left.real==right.real) && (left.imag == right.imag);
}


int main(){
	Complex a;
//	a.real = 2.5;
//	a.imag = -1.3;
	std::cout << "a = " << a << std::endl;


	const Complex i(0.0, 1.0);
	Complex x(1.0, 1.0);
	std::cout << "x = " << x << std::endl;
    std::cout << "i = " << i << std::endl;

	const Complex j = i;
    std::cout << "j = " << j << std::endl;


	Complex y = x.conj();
	std::cout << "y = " << y << std::endl;


	y = 2 + x * x - i + a * x;
    std::cout << "y = " << y << std::endl;


	Complex z = x * x.conj();
	std::cout << "z = " << z << std::endl;

    std::cout << "|i| = " << i.abs() << std::endl;
	std::cout << "|x| = " << x.abs() << std::endl;
	std::cout << "|y| = " << y.abs() << std::endl;
    std::cout << "|z| = " << z.abs() << std::endl;
    std::cout << "|i| = " << abs(i) << std::endl;
    std::cout << "|x| = " << abs(x) << std::endl;
    std::cout << "|y| = " << abs(y) << std::endl;

	z = x / 2;
	std::cout << "z = " << z << std::endl;

	return 0;
}
