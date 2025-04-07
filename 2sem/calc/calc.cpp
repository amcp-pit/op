#include <iostream>
#include "formulanodes.h"

int main(){
	FormulaNode *a, *b, *c;
	a = new NumNode(2);
	b = new ParamNode('x');
	c = new PlusNode(a, b);

	a = new PlusNode(new ParamNode('y'), new NumNode(-1));
	c = new PlusNode(c, a);

	std::cout << c->str() << std::endl;
	double result = c->calc();
	std::cout << c->str() << " = " << result << std::endl;

	return 0;
}
