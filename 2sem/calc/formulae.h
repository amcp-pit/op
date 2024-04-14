#pragma once
#include "formulanodes.h"
#include <stack>

class Formula {
	FormulaNode * root;
	FormulaNode* Postfix2Tree(const char*);
	void InfixFilter(const char *, char *);
	void Infix2Postfix(const char*, char*);
public:
	Formula(const char* str) : root(nullptr){
		size_t len = strlen(str);
		len = (len<10) ? 20 : 2*len;
		char *str_infix = new char[len];
		char *str_postfix = new char[len];
		try{
			InfixFilter(str, str_infix);
			Infix2Postfix(str_infix, str_postfix);
			root = Postfix2Tree(str_postfix);
		} catch (...){
			delete[] str_infix;
			delete[] str_postfix;
			throw;
		}
		delete[] str_infix;
		delete[] str_postfix;
	}
	double calc() const {
		if (root) return root->calc();
		return 0;
	}
	std::string str() const {
		if (root) return root->str();
		return std::string("");
	}
	std::string tex() const {
		if (root) return root->tex();
		return std::string("");
	}
	~Formula(){
		if (root) delete root;
	}
};

FormulaNode* Formula::Postfix2Tree(const char* str){
	int index = 0;  // »ндекс элемент во входной строке
	std::stack<FormulaNode*> S;
	char ch;
	FormulaNode *result, *right, *left;
	try{
	while ( (ch=str[index]) != '\0'){
		left = right = nullptr;
		switch (ch)	{
		case '+': 
			if(S.empty()) throw 1; right = S.top(); S.pop();
			if(S.empty()) throw 1; left = S.top(); S.pop();
			result = new PlusNode(left, right);
			break;
		case '-': 
			if(S.empty()) throw 1; right = S.top(); S.pop();
			if(S.empty()) throw 1; left = S.top(); S.pop();
			result = new MinusNode(left, right);
			break;
		case '*': 
			if(S.empty()) throw 1; right = S.top(); S.pop();
			if(S.empty()) throw 1; left = S.top(); S.pop();
			result = new MultNode(left, right);
			break;
		case '/': 
			if(S.empty()) throw 1; right = S.top(); S.pop();
			if(S.empty()) throw 1; left = S.top(); S.pop();
			result = new DivNode(left, right);
			break;
		case '^': 
			if(S.empty()) throw 1; right = S.top(); S.pop();
			if(S.empty()) throw 1; left = S.top(); S.pop();
			result = new PowNode(left, right);
			break;
		default:
			if (ch>='0' && ch<='9')
				result = new NumNode(ch-'0');
			else if ( (ch>='a' && ch<='z') || (ch>='A' && ch<='Z') )
				result = new ParamNode(ch);
			else throw "Unknown character"; // TODO: разобратьс€ что делать ели неизвестные символы
		}
		S.push(result);
		++index;
	}
	if (S.size() != 1){
		left = right = nullptr;
		throw 2;
	}
	return S.top();

	} catch (...) {
		if (left) delete left;
		if (right) delete right;
		while(!S.empty()){
			left = S.top();
			S.pop();
			delete left;
		}
		throw ErrorPostfix(str, index);
	}
}

void Formula::InfixFilter(const char* instr, char* outstr){
	int index=0;
	while((outstr[index]=instr[index])!='\0'){
		++index;
	}
}

const unsigned char ActionsTable[][9]={
	// 0 + - * / ^ ( ) P
	 { 7,2,2,2,2,2,2,6,1}, // empty
	 { 3,3,3,2,2,2,2,3,1}, // +
	 { 3,3,3,2,2,2,2,3,1}, // -
	 { 3,3,3,3,3,2,2,3,1}, // *
	 { 3,3,3,3,3,2,2,3,1}, // /
	 { 3,3,3,3,3,2,2,3,1}, // ^
	 { 5,2,2,2,2,2,2,4,1}  // (
};

/*
	1. переместить из instr в outstr
	2. из входной переместить в стек
	3. из стека в outstr
	4. удалить из стека и переместитьс€ на один символ во входной строке
	5. ќшибка: нет закрывающей скобки
	6. ќшибка: лишн€€ закрывающа€ скобка
	7. успешное завершение
*/

void Formula::Infix2Postfix(const char *instr, char *outstr){

}