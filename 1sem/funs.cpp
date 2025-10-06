#include <iostream>
#include <cmath>

int power(int, unsigned int);
// double power(int, int);
double power(double, int);
double power(double, double);

int main(){
	//int power(int, int);
	std::cout << "2^4 = " << power(2, 4u) << std::endl;
	std::cout << "-3^7 = " << power(-3, 7u) << std::endl;
	std::cout << "5^0 = " << power(5, 0u) << std::endl;
    std::cout << "1^1 = " << power(1, 1u) << std::endl;
    std::cout << "-1^1 = " << power(-1, 1u) << std::endl;
    std::cout << "1^-1 = " << power(1, -1) << std::endl;
    std::cout << "-1^-1 = " << power(-1, -1) << std::endl;
    std::cout << "5^1 = " << power(5, 1u) << std::endl;
    std::cout << "5^-1 = " << power(5, -1) << std::endl;
    std::cout << "-5^1 = " << power(-5, 1u) << std::endl;
    std::cout << "-5^-1 = " << power(-5, -1) << std::endl;
    std::cout << "5^-3 = " << power(5, -3) << std::endl;
    std::cout << "-5^-3 = " << power(-5, -3) << std::endl;

	double power(double, int);
	std::cout << "2.5^4 = " << power(2.5, 4) << std::endl;
	double x = 1.5;
	double y = 2.6;
	std::cout << " x^y = " << power(x,y) << std::endl;

	return 0;
}

int power(int x, unsigned int n){ // power_int_uint
    int answer = 1;
    for(int i=0; i<n; ++i){
        answer *= x;
    }
    return answer;
}

double power(double x, int n){ // power_double_int
    double answer = 1.0;
    if (n<0){
        n = -n;
        for(int i=0; i<n; ++i){
            answer /= x;
        }
    } else {
        for(int i=0; i<n; ++i){
            answer *= x;
        }
    }
    return answer;
}

double power(double x, double n){
	return std::exp(n * std::log(std::fabs(x)));
}
