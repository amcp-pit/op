#include <iostream>
#include <cmath>

int main(){

	const Complex i(0.0, 1.0);
	const Complex j = i;
	Complex x(1.0, 1.0);
	std::cout << "x = " << x << std::endl;

	Complex y = x * x - i + (x + i) * i;
    std::cout << "y = " << y << std::endl;

	Complex z = x * x.conj();
	std::cout << "z = " << x << std::endl;

    std::cout << "|i| = " << i.abs() << std::endl;
	std::cout << "|x| = " << x.abs() << std::endl;
	std::cout << "|y| = " << y.abs() << std::endl;
    std::cout << "|z| = " << z.abs() << std::endl;

	return 0;
}
