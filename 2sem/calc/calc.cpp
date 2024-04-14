#include <iostream>
#include "formulae.h"
#include "errors.h"

int main(){
	/*
	FormulaNode *a = new ParamNode('a');
	FormulaNode *b = new ParamNode('b');
	FormulaNode *c = new PlusNode(a, b);
	b = new MinusNode(new ParamNode('c'), c);
	a = new MinusNode(new NumNode(2), new ParamNode('x')) ;
	c = new MultNode(a, b);
	b = new DivNode(new NumNode(1), c);
	c = new PowNode(b, new ParamNode('y'));
	*/
	char str[1024];
	try{
		while(true){
			std::cout << "> ";
			std::cin.getline(str, 1024);
			if (strcmp(str, "quit")==0)
				break;
			try {
				Formula c(str);
				// std::cout << c.tex() << std::endl;
				std::cout << c.str() << std::endl;
				double ans = c.calc();
				std::cout << " = " << ans <<std::endl;
			} catch (const Error& error){
				std::cout<< "Error: " << error.what() << std::endl;
			}
		} // end of while
	} catch (...) {
		std::cout<< "Unknown error." << std::endl;
	}
	
//	delete c;
	return 0;
}