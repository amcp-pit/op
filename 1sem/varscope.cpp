#include <iostream>

int a = 1;
static int c = 2; // Зачем такой вариант обсудим немного позже

void foo();
void bar();
void baz();

int main(){
    std::cout << "a = " << a << " (global)" << std::endl;

	int a = 2;
	std::cout << "a = " << a << " (local before {)" << std::endl;
	std::cout << "a = " << ::a << " (global)" << std::endl;
	{
		int b = 1;
		int a = 3;
		std::cout << "a = " << a << " (local in {})" << std::endl;
		std::cout << "b = " << b << std::endl;
	}
    std::cout << "a = " << a << "(local after })" << std::endl;
    // std::cout << "b = " << b << std::endl;

	a = 0; // Меняем локальную переменную
	::a = 11; // Меняем глобальную переменную
	std::cout << "One more time\n";
    std::cout << "main: a = " << a << std::endl;
    std::cout << "global a = " << ::a << std::endl;
	foo();
	bar();
	for(int i=0; i<10; ++i)
		baz();
	return 0;
}

void foo(){
	std::cout << "foo: a = " << a << std::endl;
}

void bar(){
	int a = 4;
	std::cout << "bar: a = " << a << std::endl;
	std::cout << "bar ::a= " << ::a << std::endl;
}

void baz(){
	int cnt1 = 0;
	static int cnt2 = 0;
	++cnt1;
	++cnt2;
	std::cout << "Counts: "<< cnt1 <<", " << cnt2 << std::endl;
}
