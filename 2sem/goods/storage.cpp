#include "goods.h"

void stor(const goods & x){
	std::cout << x.getName() << ": " << x.getRealPrice() << std::endl;
}
