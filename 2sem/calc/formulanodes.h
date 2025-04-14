#ifndef FORMULA_NODES_H_
#define FORMULA_NODES_H_

#include <iostream>
#include <string>
#include <cmath>
#include "errors.h"

class FormulaNode{
public:
	virtual double calc() const = 0;
	virtual std::string str() const = 0;
	virtual std::string tex() const = 0;
	virtual ~FormulaNode() {}
};

//-----------------------------------------
class NumNode : public FormulaNode {
	const double num;
public:
	NumNode(double x) : num(x) {}
	double calc() const { return num; }
	std::string str() const {
		if (num<0)
			return std::string("(") + std::to_string(num) + std::string(")");
		return std::to_string(num);
	}
	std::string tex() const {
		return str();
	}
};

//-----------------------------------------
class ParamNode : public FormulaNode {
	const char param;
public:
	ParamNode(char name) : param(name) {}
	std::string str() const { return std::string(1, param); }
	std::string tex() const { return str(); }
	double calc() const {
		double tmp;
		std::cout << param << " = ";
		std::cin >> tmp;
		std::cin.ignore();
		return tmp;
	}
};

//-----------------------------------------
class BinNode : public FormulaNode {
protected:
    FormulaNode *left, *right;
public:
    BinNode(FormulaNode* L, FormulaNode* R) : left(L), right(R) {}
	~BinNode() {delete left; delete right;}
};

//-----------------------------------------
class PlusNode : public BinNode {
public:
	PlusNode(FormulaNode* L, FormulaNode* R) : BinNode(L, R) {}
	double calc() const { return left->calc() + right->calc(); }
	std::string str() const { return left->str() + " + " + right->str(); }
	std::string tex() const { return left->tex() + " + " + right->tex(); }
};

//-----------------------------------------
class MinusNode : public BinNode {
public:
    MinusNode(FormulaNode* L, FormulaNode* R) : BinNode(L, R) {}
    double calc() const { return left->calc() - right->calc(); }
    std::string str() const { return left->str() + " - " + right->str(); }
    std::string tex() const { return left->tex() + " - " + right->tex(); }
};
//-----------------------------------------
class MultNode : public BinNode {
public:
    MultNode(FormulaNode* L, FormulaNode* R) : BinNode(L, R) {}
    double calc() const { return left->calc() * right->calc(); }
    std::string str() const {
		return "(" + left->str() + ") * (" + right->str() + ")";
	}
    std::string tex() const { return "(" + left->tex() + ") \\cdot (" + right->tex() +")"; }
};
//-----------------------------------------
class DivideNode : public BinNode {
public:
    DivideNode(FormulaNode* L, FormulaNode* R) : BinNode(L, R) {}
    double calc() const {
		double denum = right->calc();
		if (denum == 0.0) throw ErrorDivideByZero();
		return left->calc() / denum;
	}
    std::string str() const { return "(" + left->str() + ") / (" + right->str() + ")"; }
    std::string tex() const { return "\\frac{" + left->tex() + "}{" + right->tex() +"}"; }
};

//-----------------------------------------
class PowNode : public BinNode {
public:
    PowNode(FormulaNode* L, FormulaNode* R) : BinNode(L, R) {}
    double calc() const { return std::pow(left->calc(), right->calc()); }
    std::string str() const {
        return "(" + left->str() + ") ^ (" + right->str() + ")";
    }
    std::string tex() const { return "(" + left->tex() + ")^{" + right->tex() +"}"; }
};

#endif
