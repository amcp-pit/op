/*
  Пример для работы с указателем на функцию.
  Вычисление интеграла методом прямоугольников.
*/
#include <iostream>
#include <cmath>

typedef double (*pfun)(double);

double integral( pfun f, double a, double b, int N=1000) {
	double sign = 1.0;
	if (b < a) {
		std::swap(a,b);
		sign = -1.0;
	}
	double dx = (b - a) / N;
	double S = 0.0, xi = a;
	while( xi < b) {
		S += f(xi+dx/2.0) * dx;
		xi+= dx;
	}
	return sign * S;
}

double myfun(double x) {
	return x * x - 3.0 * x + 2.0;
}

int menu(){
	int key;
	do{
		std::cout<< "1. sin" <<std::endl;
		std::cout<< "2. cos" <<std::endl;
		std::cout<< "3. myfun" <<std::endl;
		std::cin >> key;
	}while(key<1 || key >3);
	return key-1; 
}


int main(){
	pfun f;
	f = sin;
	std::cout<<"f(1) = " << f(1) <<std::endl;
	std::cout<<"(*f)(1) = " << (*f)(1) <<std::endl;
	std::cout<<"f = " << f <<std::endl;

	f = myfun;
	std::cout<<"f(1) = " << f(1) <<std::endl;
	std::cout<<"(*f)(1) = " << (*f)(1) <<std::endl;
	std::cout<<"f = " << f <<std::endl;

	pfun funcArray[]={sin, cos, myfun};
	int key=menu();
	double S= integral(funcArray[key], 0, 1.0);
	std::cout << "integral from 0 to 1: " << S <<std::endl;

	return 0;
}