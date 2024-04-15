#pragma once
#include <string>

class Error{
public:
	virtual std::string what() const{
		return std::string("Unknown error");
	}
};

class ErrorDivideByZero : public Error {
public:
	std::string what() const {
		return std::string("Divide by zero");
	}
};

class ErrorPostfix : public Error {
	std::string str;
	int index;
public:
	ErrorPostfix(const char *s, int position) : str(s), index(position) {}
	std::string what() const {
		return std::string("Error in postfix string '")
			   + str
			   + std::string("' at position ")
			   + std::to_string(index+1);
	}
};

class ErrorBracketsClose : public Error {
	std::string str;
	int index;
public:
	ErrorBracketsClose(const char *s, int position) : str(s), index(position) {}
	std::string what() const {
		return std::string("Error with brackets. There are no '(' for ')' in '")
			   + str
			   + std::string("' at position ")
			   + std::to_string(index+1);
	}
};
class ErrorBracketsOpen : public Error {
	std::string str;
	int index;
public:
	ErrorBracketsOpen(const char *s, int position) : str(s), index(position) {}
	std::string what() const {
		return std::string("Error with brackets. There are no ')' for '(' in '")
			   + str
			   + std::string("' at position ")
			   + std::to_string(index+1);
	}
};

class ErrorUnknownFunction : public Error {
	std::string str;
	int index;
public:
	ErrorUnknownFunction(const char *s) : str(s) {}
	ErrorUnknownFunction(char s) : str(1, s) {}
	std::string what() const {
		return std::string("Unknown function name '")
			   + str
			   + std::string("'");
	}
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

