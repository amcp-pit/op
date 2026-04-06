#include "formulae.hpp"
#include "errors.hpp"
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
				if (ch>='0' && ch<='9') {
					result = new NumNode(ch-'0');
				} else if ( (ch>='a' && ch<='z') || (ch>='A' && ch<='Z')) {
					result = new ParamNode(ch);
				} else {
					throw 3;
				}
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
		throw ErrorPostfix(str, index);
	}
}

//-----------------------------------------
const unsigned char ActionsTable[][10] = {
//   0 + - * / ^ ( ) P =
	{5,2,2,2,2,2,2,6,1,2}, // empty
	{3,3,3,2,2,2,2,3,1,8}, // +
	{3,3,3,2,2,2,2,3,1,8}, // -
	{3,3,3,3,3,2,2,3,1,8}, // *
    {3,3,3,3,3,2,2,3,1,8}, // /
    {3,3,3,3,3,2,2,3,1,8}, // ^
    {7,2,2,2,2,2,2,4,1,2}, // (
    {3,2,2,2,2,2,2,3,1,2}  // =
};

int actionsRowNumber(char ch) {
	switch(ch) {
	case 0 : return 0;
	case '+' : return 1;
    case '-' : return 2;
    case '*' : return 3;
    case '/' : return 4;
    case '^' : return 5;
    case '(' : return 6;
    case '=' : return 7;
	}
	return 8;
}

int actionsColNumber(char ch) {
    switch(ch) {
    case 0 : return 0;
    case '+' : return 1;
    case '-' : return 2;
    case '*' : return 3;
    case '/' : return 4;
    case '^' : return 5;
    case '(' : return 6;
    case ')' : return 7;
    case '=' : return 9;
    }
	if (ch>='a' && ch<='z') return 8;
    if (ch>='A' && ch<='Z') return 8;
    if (ch>='0' && ch<='9') return 8;
    return 10;
}


