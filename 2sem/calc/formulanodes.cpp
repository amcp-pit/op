#include "formulanodes.h"

AVLTree<ParamValue> Workspace;
/*
const FunctionsTable::Func FunctionsTable::FTable[] = {
		{128, "arcsin", std::asin},
		{129, "arccos", std::acos},
		{130, "sin", std::sin},
		{131, "cos", std::cos},
		{132, "arctg", std::atan},
		{133, "tg", std::tan},
		{134, "ln", std::log},
		{135, "exp", std::exp},
		{136, "sqrt", std::sqrt},
		{137, "sh", std::sinh},
		{138, "ch", std::cosh},
		{139, "abs", std::fabs},
		{140, "sign", sign},
		{141, "sqr", sqr}
    };
const int FunctionsTable::sizeFTable = sizeof(FTable)/sizeof(FTable[0]);
*/

FunctionsTable FunTable;
