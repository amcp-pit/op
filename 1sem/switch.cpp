/*
 Пример вывода названия дня по номеру дня недели.
*/

#include <iostream>

int main()
{
	int day;

	do {
		std::cout << "Number of day: ";
		std::cin >> day;  // Да, здесь никак не обрабатывается ввод. Поэтому при тестировании вводим только числа.
		switch (day % 7) {
		case 1: std::cout << "Mon "; // Попробуйте поставить break;
		case 2: std::cout << "Thu "; // Попробуйте поставить break;
		case 3: std::cout << "Wen "; // Попробуйте поставить break;
		case 4: std::cout << "Thr "; // Попробуйте поставить break;
		case 5: std::cout << "Fry "; break;
		case 6: std::cout << "Sat ";
		default: std::cout << "Sun ";
		}
		std::cout << std::endl;
	} while (day != 0);
	return 0;
}

