#ifndef _FORMULA_NODES_26
#define _FORMULA_NODES_26
#include <string>
#include <cmath>
#include <iostream>
#include "../BST/AVLtree.hpp"
#include "errors.hpp"

class FormulaNode {
public:
	virtual double calc() const = 0;
	virtual std::string str() const = 0;
	virtual std::string tex() const = 0;
	virtual ~FormulaNode() {}
};

class NumNode : public FormulaNode {
	const double num;
public:
	NumNode(double x) : num(x) {}
	double calc() const { return num; }
	std::string str() const {
		if (num<0) {
			return std::string("(") + std::to_string(num) + std::string(")");
		}
		return std::to_string(num);
	}
	std::string tex() const {
		return str();
	}
};

class ParamValue {
	const char ch;
	const double val;
public:
	ParamValue(char c, double value) : ch(c), val(value) {}
	double getValue()const { return val; }
	bool operator<(const ParamValue& other) const { return ch < other.ch; }
    bool operator==(const ParamValue& other) const { return ch == other.ch; }
};

extern AVLTree<ParamValue> Workspace;

class ParamNode : public FormulaNode {
	const char param;
public:
	ParamNode(char name) : param(name) {}
	std::string str() const override { return std::string(1, param); }
	std::string tex() const override { return str(); }
	double calc() const override {
		auto pos = Workspace.find(ParamValue(param ,0));
		if (pos != Workspace.end()){
			return (*pos).getValue();
		}
		double tmp;
		std::cout << param << " = ";
		std::cin >> tmp;
		std::cin.ignore();
		Workspace.insert(ParamValue(param, tmp));
		return tmp;
	}
};


class BinNode : public FormulaNode {
protected:
    FormulaNode *left, *right;
public:
	BinNode(FormulaNode* L, FormulaNode* R) : left(L), right(R) {}
	~BinNode() { delete left; delete right; }
};

class PlusNode : public BinNode {
public:
	PlusNode(FormulaNode* L, FormulaNode* R) : BinNode(L, R) {}
	double calc() const { return left->calc() + right->calc(); }
	std::string str() const { return left->str() + " + " + right->str(); }
	std::string tex() const { return left->tex() + " + " + right->tex(); }
};

class MinusNode : public BinNode {
public:
    MinusNode(FormulaNode* L, FormulaNode* R) : BinNode(L, R) {}
    double calc() const { return left->calc() - right->calc(); }
    std::string str() const { return left->str() + " - (" + right->str() + ")"; }
    std::string tex() const { return left->tex() + " - (" + right->tex() + ")"; }
};

class MultNode : public BinNode {
public:
    MultNode(FormulaNode* L, FormulaNode* R) : BinNode(L, R) {}
    double calc() const { return left->calc() * right->calc(); }
    std::string str() const {
		return "(" + left->str() + ") * (" + right->str() + ")";
	}
    std::string tex() const {
		return "(" + left->tex() + ") \\cdot (" + right->tex() + ")";
	}
};

class DivideNode : public BinNode {
public:
    DivideNode(FormulaNode* L, FormulaNode* R) : BinNode(L, R) {}
    double calc() const {
		double denum = right->calc();
		if (denum == 0.0) throw ErrorDivideByZero();
		return left->calc() / denum;
	}
    std::string str() const {
        return "(" + left->str() + ") / (" + right->str() + ")";
    }
    std::string tex() const {
        return "\\frac{" + left->tex() + "}{" + right->tex() + "}";
    }
};

class PowNode : public BinNode {
public:
    PowNode(FormulaNode* L, FormulaNode* R) : BinNode(L, R) {}
    double calc() const { return std::pow(left->calc(), right->calc()); }
    std::string str() const {
        return "(" + left->str() + ") ^ (" + right->str() + ")";
    }
    std::string tex() const {
        return "(" + left->tex() + ")^{" + right->tex() + "}";
    }
};

class AssignmentNode : public FormulaNode {
	ParamNode *left;
	FormulaNode* right;
public:
	AssignmentNode(FormulaNode *L, FormulaNode* R) : left(nullptr), right(R) {
		left = dynamic_cast<ParamNode*>(L);
		if (left == nullptr) {
			throw ErrorRValue();
		}
	}
	~AssignmentNode() {
		delete left;
		delete right;
	}
	std::string str() const {
		return left->str() + std::string(" := ") + right->str();
	}
    std::string tex() const {
        return left->tex() + std::string(" = ") + right->tex();
    }
	double calc() const {
		double result = right->calc();
		char paramName = left->str()[0];
		auto pos = Workspace.find(ParamValue(paramName, 0));
		if (pos != Workspace.end()) {
			Workspace.erase(pos);
		}
		Workspace.insert(ParamValue(paramName, result));
		return result;
	}
};

#endif
