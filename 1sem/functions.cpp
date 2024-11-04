#include <iostream>

void foo(int a, int b);
void bar(int *pa, int *pb);
void baz(int &a, int &b);

template <typename T>
void myswap(T& a, T& b) {
	T tmp = a;
	a = b;
	b = tmp;
}

int main() {
	int x = 1, y = 2;
	std::cout<<"before foo x="<< x <<", y="<< y <<std::endl;
	foo(x, y);
	std::cout<<"after  foo x="<< x <<", y="<< y <<std::endl;

	std::cout<<"before bar x="<< x <<", y="<< y <<std::endl;
	bar(&x, &y);
	std::cout<<"after  bar x="<< x <<", y="<< y <<std::endl;
	
	std::cout<<"before baz x="<< x <<", y="<< y <<std::endl;
	baz(&x, &y);
	std::cout<<"after  baz x="<< x <<", y="<< y <<std::endl;

	std::cout<<"before myswap x="<< x <<", y="<< y <<std::endl;
	myswap(x, y);
	std::cout<<"after  myswap x="<< x <<", y="<< y <<std::endl;

	double a = 1.0, b = 2.0;
	std::cout<<"before myswap a="<< a <<", b="<< b <<std::endl;
	myswap(a, b);
	std::cout<<"after  myswap a="<< a <<", b="<< b <<std::endl;
	return 0;
}

void foo(int a, int b) {
	std::cout<<"before a="<<a<<", b="<<b<<std::endl;
	int tmp=a;
	a=b;
	b=tmp;
	std::cout<<"after a="<<a<<", b="<<b<<std::endl;
}

void bar(int *pa, int *pb){
	std::cout<<"before *pa="<<*pa<<", *pb="<<*pb<<std::endl;
	int tmp = *pa;
	*pa = *pb;
	*pb = tmp;
	std::cout<<"after *pa="<<*pa<<", *pb="<<*pb<<std::endl;
}

void baz(int &a, int &b){
	std::cout<<"before a="<<a<<", b="<<b<<std::endl;
	int tmp=a;
	a=b;
	b=tmp;
	std::cout<<"after a="<<a<<", b="<<b<<std::endl;
}
