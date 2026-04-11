#ifndef _FORMULAE_26_
#define _FORMULAE_26_

#include <cstring>
#include <string>
#include "formulanodes.hpp"

class Formula {
	FormulaNode * root;
	FormulaNode* Postfix2Tree(const char *);
	void Infix2Postfix(const char*, char*);
public:
	Formula(const char * formulastr) : root (nullptr) {
		char * str_postfix = nullptr;
		size_t len = std::strlen(formulastr) + 1;
		str_postfix = new char[len];
		Infix2Postfix(formulastr, str_postfix);
		root = Postfix2Tree(str_postfix);
		delete[] str_postfix;
	}
	double calc() const {
		return root ? root->calc() : 0;
	}
	std::string str() const {
		return root ? root->str() : std::string("");
	}
    std::string tex() const {
        return root ? root->tex() : std::string("");
    }
	~Formula() { delete root; }
	Formula(const Formula&) = delete;
	Formula& operator=(const Formula&) = delete;
};

#endif
