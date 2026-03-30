#include <iostream>
#include "formulanodes.hpp"

int main() {
	FormulaNode *x = new ParamNode('x');
	FormulaNode *y = new ParamNode('y');
	FormulaNode *z = new PlusNode(x, y);
	z = new MultNode(new NumNode(-1), z);
	z = new DivideNode(z, new MinusNode(new NumNode(2), new ParamNode('x')));
	std::cout << z->str() << std::endl;
	try {
		double result = z->calc();
	    std::cout << z->str() << " = " << result << std::endl;
    	std::cout << "TeX: " << z->tex() <<std::endl;
	} catch (const char * error) {
		std::cout <<"\nERROR: " << error << std::endl;
	} catch(...) {
		std::cout << "Unknown error" << std::endl;
	}

	return 0;
}
