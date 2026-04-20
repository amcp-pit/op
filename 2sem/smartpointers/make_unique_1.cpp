#include <iostream>
#include <memory> // для std::unique_ptr и std::make_unique

class Fraction {
private:
	int m_numerator = 0;
	int m_denominator = 1;
public:
	Fraction(int numerator = 0, int denominator = 1) :
		m_numerator(numerator), m_denominator(denominator) { }

	friend std::ostream& operator<<(std::ostream& out, const Fraction &f) {
		out << f.m_numerator << "/" << f.m_denominator;
		return out;
	}
};

int main() {
	// Создаем объект с динамически выделенным Fraction с numerator = 7 и denominator = 9
	std::unique_ptr<Fraction> fraction = std::make_unique<Fraction>(7, 9);
	std::cout << *fraction << '\n';

	// Создаем объект с динамически выделенным массивом Fraction длиной 5.
	// Используем автоматическое определение типа данных с помощью ключевого слова auto
	auto fractions = std::make_unique<Fraction[]>(5);
	std::cout << fractions[0] << '\n';

	return 0;
}