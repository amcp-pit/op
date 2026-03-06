#include <iostream>

void foo(int& x) // try: const int&
{
	std::cout << "lvalue ref: " << x << "\n";
}

void foo(int&& x) // try: const int&&
{
	std::cout << "rvalue ref: " << x << "\n";
	x = 1;
	std::cout << "rvalue ref after x = 1:" << x << "\n";
}

int getValue()
{
	int temp_ii = 44;
	return temp_ii;
}

int main()
{
	int i = 77;

	std::cout << "foo(i) => ";
	foo(i);    // lvalue ref called

	std::cout << "foo(99) => ";
	foo(99);   // rvalue ref called


	std::cout << "foo(std::move(i)) => ";
	foo(std::move(i));  // rvalue ref called
	std::cout << "i=" << i << std::endl;


	std::cout << "foo(getValue()) => ";
	foo(getValue());  // rvalue ref called


	int &&rref = 7; // поскольку инициализируем ссылку r-value литералом 7,
					// то создается временный объект со значением 7,
					// на который указывает ссылка r-value
    rref = 13;
    std::cout << rref << std::endl;

	return 0;
}

