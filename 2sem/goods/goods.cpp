#include "goods.h"

double goods::percent = 0.25;
int goods::counter = 0;

std::ostream& operator<< (std::ostream& out, const goods & x) {
    out << x.getName() << ":\t" << x.getPrice();
    return out;
}

goods& goods::operator=(const goods& x){
	if (this != &x){
		delete[] name_;
		size_t len = strlen(x.name_);
		name_ = new char[len+1];
		strcpy(name_, x.name_);
		price_ = x.price_;
	}
	return *this;
}
