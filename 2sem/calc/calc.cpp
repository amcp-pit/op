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
/*
	FormulaNode *a, *b, *c;
	a = new ParamNode('y');
	b = new ParamNode('z');
	c = new MultNode(a, b);

	a = new ParamNode('x');
	c = new MinusNode(a, c);

	a = new ParamNode('a');
	b = new ParamNode('b');
	a = new PlusNode(a, b);

	c = new DivideNode(c , a);

	c = new PowNode(new NumNode(2), c);

	std::cout << c->str() << std::endl;
	double result = c->calc();
	std::cout << c->str() << " = " << result << std::endl;

	std::cout << "TeX: " << c->tex() << std::endl;
*/
	return 0;
}
