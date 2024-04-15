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
			std::cout << str_postfix <<std::endl;
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
