#ifndef FORMULA_NODES_H_
#define FORMULA_NODES_H_

#include <string>
#include <cmath>

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
		return tmp;
	}
};

//-----------------------------------------
class PlusNode : public FormulaNode {
	FormulaNode *left, *right;
public:
	PlusNode(FormulaNode* L, FormulaNode* R) : left(L), right(R) {}
	~PlusNode() {delete left; delete right;}
	double calc() const { return left->calc() + right->calc(); }
	std::string str() const {
		return left->str() + " + " + right->str();
	}
	std::string tex() const {
        return left->tex() + " + " + right->tex();
    }
};

#endif
