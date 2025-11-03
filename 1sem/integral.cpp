#include <iostream>
#include <cmath>

//typedef unsigned long long ull;
typedef double (*pfun)(double);

//double integral( double (*f)(double), double a, double b, int N=1000)
double integral(pfun f, double a, double b, int N=1000)
{
	double sign = 1.0;
	if (b<a){
		std::swap(a, b);
		sign = -1.0;
	}
	double dx = (b-a) / N; // dx >= 0
	double S = 0.0;
	double xk = a;
	while(xk < b){
		S += f(xk + dx/2.0) * dx;
		xk += dx;
	}
	return sign * S;
}

double myfun1(double x){
	return x;
}

double myfun2(double x){
	return x*x - 3.0 * x + 2.0 ;
}

int menu(){
	int key = 0;
	do{
		std::cout <<"1. sin\n" ;
		std::cout <<"2. cos\n" ;
		std::cout <<"3. x\n" ;
		std::cout <<"4. x^2-3x+2\n" ;
		std::cout <<"5. sqrt(x)\n" ;
		std::cin >> key;
	} while(key<1 || key>5);
	return key;
}

int foo(int x, double y){
	return (int)(x * y);
}

int main(){
	int (*g)(int, double);
	g = foo;
	std::cout << g(4, 5.5) << std::endl;

	pfun f;
	f = std::sin;
	std::cout << "sin(1) =" << sin(1.0) <<std::endl;
	std::cout << "f(1) =" << f(1.0) <<std::endl;
	std::cout << "(*f)(1) = " << (*f)(1.0) <<std::endl;
	std::cout << "f = " << f <<std::endl;

	std::cout << integral(std::sin, 0.0, 3.1415) << std::endl;
	std::cout << integral(std::sin, 0.0, 2*3.1415) << std::endl;
	std::cout << integral(myfun1, 0.0, 3.0) << std::endl;
	f = myfun2;
	std::cout << integral(f, -1, 3.0) << std::endl;

	pfun funcArray[] = {std::sin, std::cos, myfun1, myfun2, std::sqrt};
	int key = menu();
	double s = integral(funcArray[key-1], 0.0, 1.0);
	std::cout << "integral from 0 to 1 is " << s <<std::endl;
	return 0;
}

