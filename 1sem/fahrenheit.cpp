/*
Перевод температуры в градусах по Фаренгейту в градусы по Цельсию.
Формула: С = 5/9*(F-32)
Градусы по Фаренгейту меняются в диапазоне от -20 до 100 с шагом 10.
*/

#include <iostream>

int main(){

	for(double F = -20.0; F <= 100.0; F += 10.0){
		double C = 5.0/9.0*(F-32.0); // Попробуйте заменить на 5/9*(F-32). Почему всегда получается C=0?
		std::cout << "F=" << F << "\tC= " << C;
		if (C > 35.0) {
			std::cout << " hot";
		} else {
			if (C > 10){
				std::cout << " Comfortable";
			} else if (C > 0) {
				std::cout << " Chilly";
			} else if (C > -20.0) {
				std::cout << " Winter is coming";
			} else {
				std::cout << " Very cold";
			}
		}
		std::cout<< std::endl;
	}
	
	return 0;
}
