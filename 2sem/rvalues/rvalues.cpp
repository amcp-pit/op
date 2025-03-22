#include <iostream>

void foo(int& x) // try: const int&
{
	std::cout << "lvalue ref: " << x << "\n";
}

void foo(int&& x) // try: const int&&
{
	std::cout << "rvalue ref: " << x << "\n";
	x = 1;
}

int getValue()
{
	int temp_ii = 44;
	return temp_ii;
}


class Fraction
{
private:
	int numerator_;
	int denominator_;
	int ID;
	static int autoinc;
public:
	Fraction(int numerator = 0, int denominator = 1) :
		numerator_(numerator), denominator_(denominator) 
	{
		ID = ++autoinc;
        std::cout << "create (" << numerator_ << ", " << denominator_ << ")"<<" id: " << ID <<"\n";
	}

	Fraction& operator=(const Fraction& other) {
		numerator_ = other.numerator_;
		denominator_ = other.denominator_;
		return *this;
	}

   Fraction& operator=(Fraction&& other) {
        numerator_ = other.numerator_;
        denominator_ = other.denominator_;
        return *this;
    }

	friend std::ostream& operator<<(std::ostream& out, const Fraction &f1)
	{
		out << f1.numerator_ << "/" << f1.denominator_;
		return out;
	}
	~Fraction()
	{
		std::cout << "fraction(" << numerator_ << ", " << denominator_ << ") die id: "<< ID << "\n";
	}
};

int Fraction::autoinc = 0;

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

	{
		Fraction &&rref = Fraction(4, 7); // ссылка r-value на анонимный объект класса Fraction
		std::cout << rref << '\n'; // используем ссылку r-value для вывода значения анонимного объекта класса Fraction
	} // rref (и анонимный объект класса Fraction) выходит из области видимости здесь
/*
	Создаваемый анонимный объект Fraction(4, 7) обычно вышел бы из области видимости в конце выражения, в котором он определен. 
	Однако, так как мы инициализируем ссылку r-value этим анонимным объектом, 
	то его продолжительность жизни увеличивается до продолжительности жизни самой ссылки r-value, 
	т. е. до конца блока {}, в коотором задана rref. 
*/

	std::cout << "--------------------------- \n";
	{
		Fraction &&rref = Fraction(2, 3); // ссылка r-value на анонимный объект класса Fraction
		std::cout << rref << '\n'; 

		rref = Fraction(5, 6);
		std::cout << rref << '\n'; 
		std::cout << "inside the block with rref\n";
	} // rref (и анонимный объект класса Fraction) выходит из области видимости здесь

	std::cout << "outside the block with rref\n";

	int &&rref = 7; // поскольку инициализируем ссылку r-value литералом 7, 
					// то создается временный объект со значением 7, 
					// на который указывает ссылка r-value
    rref = 13;
    std::cout << rref << std::endl;

	return 0;
}
