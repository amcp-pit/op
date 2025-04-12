#ifndef FORMULAE_H
#define FORMULAE_H

#include "formulanodes.h"

class Formula {
	FormulaNode * root;
	FormulaNode* Postfix2Tree(const char *);
public:
	Formula(const char * formulastr){
		try{
			root = Postfix2Tree(formulastr);
		} catch (...){
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
