#include <iostream>
#include <cstring>

//#include "formulanodes.h"
#include "formulae.h"
#include "errors.h"

int main(){
	char str[1024];

	try{
		while(true){
			std::cout << "> ";
			std::cin.getline(str, 1024);
			if (strlen(str) == 0) continue;
			if (strcmp(str,"quit") == 0)
				break;
			try {
				Formula f(str);
				//  std::cout << "calculate: " << f.str() << std::endl;
				double result = f.calc();
				std::cout << "result = " << result << std::endl;
				std::cout << "TeX: " << f.tex() << std::endl;
			} catch(const Error & error){
				std::cout << "Error. " << error.what() << std::endl;
			}
		} // end of while
	} catch(...){
		std::cout << "Unknown error" << std::endl;
	}
	return 0;
}
