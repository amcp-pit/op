#include "goods.h"

void stor(const goods & X){
	std::cout << X.getName() 
			  << ": " << X.getRealPrice() 
			  << std::endl;
}
