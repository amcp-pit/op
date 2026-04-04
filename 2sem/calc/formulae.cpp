#include "formulae.hpp"
#include <stack>

FormulaNode* Formula::Postfix2Tree(const char * str) {
	int index = 0;
	std::stack<FormulaNode*> S;
	char ch;
	FormulaNode *left, *right, *result;
	try{
	while( (ch = str[index]) != '\0' ){
		left = right = result = nullptr;
		switch(ch) {
		case '+':
				if (S.empty()) throw 1; right = S.top(); S.pop();
				if (S.empty()) throw 1; left = S.top();  S.pop();
				result = new PlusNode(left, right);
				break;
        case '-':
                if (S.empty()) throw 1; right = S.top(); S.pop();
                if (S.empty()) throw 1; left = S.top();  S.pop();
                result = new MinusNode(left, right);
                break;
        case '*':
                if (S.empty()) throw 1; right = S.top(); S.pop();
                if (S.empty()) throw 1; left = S.top();  S.pop();
                result = new MultNode(left, right);
                break;
        case '/':
                if (S.empty()) throw 1; right = S.top(); S.pop();
                if (S.empty()) throw 1; left = S.top();  S.pop();
                result = new DivideNode(left, right);
                break;
        case '^':
                if (S.empty()) throw 1; right = S.top(); S.pop();
                if (S.empty()) throw 1; left = S.top();  S.pop();
                result = new PowNode(left, right);
                break;
        case '=':
                if (S.empty()) throw 1; right = S.top(); S.pop();
                if (S.empty()) throw 1; left = S.top();  S.pop();
                result = new AssignmentNode(left, right);
                break;
		default:
				if (ch>='0' && ch<='9')
					result = new NumNode(ch-'0');
				if ( (ch>='a' && ch<='z') || (ch>='A' && ch<='Z'))
					result = new ParamNode(ch);
		}
		S.push(result);
		++index;
	}
	if (S.size() != 1) {
		left = right = nullptr;
		throw 2;
	}
	return S.top();
	} catch(...) {
		if (left) delete left;
		if (right) delete right;
		while(!S.empty()) {
			left = S.top();
			S.pop();
			delete left;
		}
		throw "Error Postfix";
	}
}
