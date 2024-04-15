#pragma once
#include <cmath>
#include <cstring>
#include "errors.h"

typedef double (*pfun)(double);

double sign(double x) {
	return x==0 ? 0 : (x<0 ? -1.0 : 1.0);
}

struct FuncInfo{
	char shortName;
	const char* longName;
	pfun fun;
};

const FuncInfo FTable[] = {
	{128, "arcsin", std::asin},
	{129, "arccos", std::acos},
	{130, "sin", std::sin},
	{131, "cos", std::cos},
	{132, "arctg", std::atan},
	{133, "tg", std::tan},
	{134, "ln", std::log},
	{135, "exp", std::exp},
	{136, "abs", std::fabs},
	{137, "sh", std::sinh},
	{138, "ch", std::cosh},
	{139, "sqrt", std::sqrt},
	{140, "sign", sign}
};
const int sizeFTable = sizeof(FTable)/sizeof(FTable[0]);

int funcNumberByShortName(char s){
	for(int i=0; i<sizeFTable; ++i){
		if (FTable[i].shortName == s)
			return i;
	}
	throw ErrorUnknownFunction(s);
}

int funcNumberByLongName(const char *s){
	for(int i=0; i<sizeFTable; ++i){
		if ( strcmp(FTable[i].longName,s)==0 )
			return i;
	}
	throw ErrorUnknownFunction(s);
}

