#include <iostream>
#include <cstring>
#include "formulae.hpp"

int main() {
	char str[1024];
	try {
		while(true){
			std::cout << "> ";
			std::cin.getline(str, 1024);
			if (strlen(str) == 0) continue;
			if (strcmp(str, "quit") == 0) break;
			try {
				Formula F(str);
				std::cout << "calculate: " << F.str() << std::endl;
				double result = F.calc();
				std::cout << "result = " << result << std::endl;
				std::cout << "TeX: " << F.tex() << std::endl;
			} catch (...) {
				std::cout << "Error " << std::endl;
			}
		}
	} catch(...){
		std::cout << "Unknown error " << std::endl;
	}
	return 0;
}
