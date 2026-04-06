#ifndef ERRORS_26_
#define ERRORS_26_

#include <string>

class Error {
public:
	virtual std::string what() const {
		return std::string("Unknown error");
	}
};

class ErrorDivideByZero : public Error {
public:
	std::string what() const {
		return std::string("Divide by zero");
	}
};

class ErrorRValue : public Error {
public:
	std::string what() const {
		return std::string("To the left of = should be lvalue");
	}
};

class ErrorPostfix : public Error {
	std::string str;
	int index;
public:
	ErrorPostfix(const char *s, int position) : str(s), index(position) {}
	std::string what() const {
		return std::string("Error in postfix string: '")
			   + str
			   + std::string("' at position ")
			   + std::to_string(index + 1);
	}
};

#endif
