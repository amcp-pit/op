#ifndef ERRORS_H_
#define ERRORS_H_

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

class ErrorOutOfBounds : public Error {
	int minimum;
	int value;
	int maximum;
public:
	ErrorOutOfBounds(int left=0, int right=0, int val=0) : 
			minimum(left), maximum(right), value(val) {}
    std::string what() const {
        return std::string("Out of bounds: ")
			   +std::to_string(value)
			   +std::string(" not in [")
               +std::to_string(minimum) + std::string(", ")
               +std::to_string(maximum) + std::string("]");
    }
};

class ErrorPostfix : public Error {
	std::string str;
	int index;
public:
	ErrorPostfix(const char *s, int position): str(s), index(position) {}
	std::string what() const{
		return std::string("Error in postfix string: '")
				+ str
				+ std::string("' at position ")
				+ std::to_string(index + 1);
	}
};

class ErrorBracketsClose : public Error {
    std::string str;
    int index;
public:
    ErrorBracketsClose(const char *s, int position): str(s), index(position) {}
    std::string what() const{
        return std::string("Error in string: '")
                + str
                + std::string("' at position ")
                + std::to_string(index + 1)
				+ std::string(", extra close bracket");
    }
};

class ErrorBracketsOpen : public Error {
    std::string str;
    int index;
public:
    ErrorBracketsOpen(const char *s, int position): str(s), index(position) {}
    std::string what() const{
        return std::string("Error in string: '")
                + str
                + std::string("' at position ")
                + std::to_string(index + 1)
                + std::string(", extra open bracket");
    }
};

class ErrorRValue : public Error {
public:
	std::string what() const {
		return std::string("To the left of = should be lvalue");
	}
};

class ErrorUnknownFunction : public Error {
	std::string str;
public:
	ErrorUnknownFunction(const char * s) : str(s) {}
	ErrorUnknownFunction(char s): str(1, s) {}
	std::string what()const {
		return std::string("Unknown function name '")
			   + str + std::string("'");}
};

class ErrorFunctionBrackets : public Error {
	std::string str;
	int index;
public:
	ErrorFunctionBrackets(const char *s, int position) : str(s), index(position) {}
	std::string what() const {
		return std::string("Error with brackets after function in '")
			   + str
			   + std::string("' at position ")
			   + std::to_string(index+1);
	}
};

class ErrorFunctionArguments : public Error {
public:
	std::string what() const {
		return std::string("Function without arguments");
	}
};

#endif
