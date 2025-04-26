#ifndef FORMULAE_H
#define FORMULAE_H
#include <cstring>
#include "formulanodes.h"
#include "errors.h"

#include <iostream>

class Formula {
	FormulaNode * root;
	FormulaNode* Postfix2Tree(const char *);
	void Infix2Postfix(const char *, char *);
	void InfixFilter(const char*, char *);
public:
	Formula(const char * formulastr){
		char * str_infix = nullptr;
		char * str_postfix = nullptr;
		try{
			size_t len = strlen(formulastr);
			len = (len<10) ? 20 : 2 * len;
			str_infix = new char[len];
			InfixFilter(formulastr, str_infix);
			str_postfix = new char[len];
			Infix2Postfix(str_infix, str_postfix);
			root = Postfix2Tree(str_postfix);
		} catch (...){
			delete[] str_infix;
			delete[] str_postfix;
			throw;
		}
	}
	double calc() const{
		return (root) ? root-> calc() : 0.0;
	}
	std::string str() const {
		return root ? root->str() : std::string("");
	}
	std::string tex() const{
        return root ? root->tex() : std::string("");
    }

	~Formula() { delete root; }
};

#endif
