#include <iostream>

unsigned long long factorial(unsigned long long n){
	if (n<2)
		return 1;
	return n * factorial(n-1);
}

void factorial2(unsigned long long * result,
				unsigned long long n)
{
	if (n<2) return;
	*result *= n;
	return factorial2(result, n-1);
}

unsigned long long fib(unsigned int n){
	static unsigned long long counter = 0;
	static unsigned long long memcounter[20] = {0};
	++counter;
	if (n<20) ++memcounter[n];
	std::cout << "fib step: " << counter <<", n = " << n << std::endl;
	for(int i=0; i<20; ++i){
		std::cout << memcounter[i] << " ";
	}
	std::cout << std::endl;
	if (n==0) return 0;
	if (n==1) return 1;
	return fib(n-1) + fib(n-2);
}

int main(){
	unsigned long long n;
	std::cin >> n;
	unsigned long long result = factorial(n);
	std::cout << n << "! = " << result << std::endl;
	result = 1;
	factorial2(&result, n);
	std::cout << n << "! = " << result << std::endl;
	result = fib(n);
	std::cout << "fib(" << n << ") = " << result << std::endl;
	return 0;
}
