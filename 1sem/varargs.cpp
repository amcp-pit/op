#include <iostream>
#include <stdarg.h>

int summa0(int N, int x, ... ){
	int sum = 0;
	int *p = &x;
	for (int i=0; i<N; ++i){
		sum += *p;
		++p;
	}
	return sum;
}


int summa(int N, int x, ... ){
	va_list args;
	va_start(args, x);

	int sum = x;
	for (int i=1; i<N; ++i){
		sum += va_arg(args, int);
	}
	va_end(args);
	return sum;
}

double prod(double x, ...){
	va_list args;
	va_start(args, x);
	double a=x;
	double total=a;
	while( (a=va_arg(args, double)) != 0.0 ){
		total *= a;
	}
	va_end(args);
	return total;
}


int main(){
	std::cout << summa(1, 2) <<std::endl;
	std::cout << summa(2, 2, 2) <<std::endl;
	std::cout << summa(3, 1, 2, 3) <<std::endl;
	std::cout << summa(5, 1, -1, 1, -1, 1) <<std::endl;
	std::cout << summa(10,1,2,3,4,5,6,7,8,9,0) <<std::endl;

	double f=1.5, e=2.71, g=9.8, h=1.0, s=-1.1;
	std::cout<< prod(f, 0.0) <<std::endl;
	std::cout<< prod(f,e, 0.0) <<std::endl;
	std::cout<< prod(f,e,g, 0.0) <<std::endl;
	std::cout<< prod(f,e,g,h, 0.0) <<std::endl;
	std::cout<< prod(f,e,g,h,s, 0.0) <<std::endl;
	return 0;
}