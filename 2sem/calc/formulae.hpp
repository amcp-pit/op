#ifndef _FORMULAE_26_
#define _FORMULAE_26_

#include <string>
#include "formulanodes.hpp"

class Formula {
	FormulaNode * root;
	FormulaNode* Postfix2Tree(const char *);
public:
	Formula(const char * formulastr) : root (nullptr) {
		root = Postfix2Tree(formulastr);
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
