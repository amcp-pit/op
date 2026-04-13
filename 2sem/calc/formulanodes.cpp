#include "formulanodes.hpp"
/*
const FunctionsTable::Func FunctionsTable::FTable[] = {
        {std::asin, "asin", 128},
        {std::acos, "acos", 129},
        {std::sin, "sin", 130},
        {std::cos, "cos", 131},
        {std::atan, "arctg", 132},
        {std::tan, "tg", 133},
        {std::log, "ln", 134},
        {std::exp, "exp", 135},
        {std::sqrt, "sqrt", 136},
        {std::sinh, "sh", 137},
        {std::cosh, "ch", 138},
        {std::fabs, "abs", 139}
    };
const int FunctionsTable::sizeFTable = sizeof(FTable)/sizeof(FTable[0]);
*/

AVLTree<ParamValue> Workspace;
FunctionsTable FunTable;
