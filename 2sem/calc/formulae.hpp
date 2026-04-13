#ifndef _FORMULAE_26_
#define _FORMULAE_26_

#include <cstring>
#include <string>
#include "formulanodes.hpp"

class Formula {
	FormulaNode * root;
	FormulaNode* Postfix2Tree(const char *);
	void InfixFilter(const char*, char*);
	void Infix2Postfix(const char*, char*);
public:
	Formula(const char * formulastr) : root (nullptr) {
		char * str_infix = nullptr;
		char * str_postfix = nullptr;
		size_t len = std::strlen(formulastr) + 1;
		len = (len < 10) ? 20 : 2*len;
		str_infix = new char[len];
		str_postfix = new char[len];
		try {
			InfixFilter(formulastr, str_infix);
			Infix2Postfix(str_infix, str_postfix);
			root = Postfix2Tree(str_postfix);
		} catch(...) {
        	delete[] str_postfix;
        	delete[] str_infix;
			throw;
		}
		delete[] str_postfix;
		delete[] str_infix;
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
