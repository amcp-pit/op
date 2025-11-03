#include <iostream>
#include <stdarg.h>

int summa0(int n, int x, ...){
	int answer = 0;
	int *p = &x;
	for(int i=0; i<n; ++i){
		answer += *p;
		++p;
	}
	return answer;
}

int summa(int n, int x, ...){
	va_list args;
	va_start(args, x);
	int answer = x;
	for(int i=1; i<n; ++i){
		answer += va_arg(args, int);
	}
	va_end(args);
	return answer;
}

double prod(double x, ...){
	va_list args;
	va_start(args, x);
	double a = x;
	double ans = a;
	while( (a = va_arg(args, double)) != 0.0){
		ans *= a;
	}
	va_end(args);
	return ans;
}

int main(){

	std::cout << summa(1, 2) <<std::endl;
	std::cout << summa(2, 1, 2) <<std::endl;
	std::cout << summa(3, 1, 2, 3) <<std::endl;
	std::cout << summa(5, 1, 2, 3, 4, 5) <<std::endl;
	std::cout << summa(10, 1, 2, 3, 4, 5, -5, -4, -3, -2, -1) <<std::endl;

	double f=1.3, e=2.71, p=3.14, h=1.0, k=-2.7;
	std::cout<< prod(f, 0.0) <<std::endl;
	std::cout<< prod(f, e, 0.0) <<std::endl;
	std::cout<< prod(f, e, p, 0.0) <<std::endl;
	std::cout<< prod(f, e, p, h, 0.0) <<std::endl;
	std::cout<< prod(f, e, p, h, k, 0.0) <<std::endl;
	return 0;
}

