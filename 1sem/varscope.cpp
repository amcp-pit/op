#include <iostream>

int a = 1;
void foo();
void bar();
void baz();

int main(){
	std::cout<< "Global: a = " << a <<std::endl;
	int a = 2;
	std::cout<< "main: a = " << a <<std::endl;
	std::cout<< "::a = " << ::a <<std::endl;
	foo();
	bar();
	
	a = 0; // меняем локальную переменную
	::a=0; // меняем глобальную a
	std::cout <<"One more time"<<std::endl;
	std::cout<< "main: a = " << a <<std::endl;
	foo();
	bar();

	for(int i=0; i<10; ++i)
		baz();

	return 0;
}

void foo(){
	std::cout<< "foo: a = " << a <<std::endl;
}

void bar(){
	{
		int a = 3;
		std::cout<< "bar: a = " << a <<std::endl;
		{
			int a = 4;
			std::cout<< "bar: a = " << a <<std::endl;
			std::cout<< "bar: ::a = " << ::a <<std::endl;
		}
		std::cout<< "bar: a = " << a <<std::endl;
	}
	std::cout<< "bar: a = " << a <<std::endl;
}

void baz(){
	int cnt1 = 0;
	static int cnt2 = 0;
	++cnt1;
	++cnt2;
	std::cout<<"Counts: "<< cnt1<<", "<<cnt2<<std::endl;
}
