#include "goods.h"

double goods::percent = 0.25;
int goods::counter = 0;

std::ostream& operator<< (std::ostream& out, const goods & x) {
    out << x.getName() << ":\t" << x.getPrice();
    return out;
}

std::ofstream& operator<< (std::ofstream& out, goods& x){
	out << x.getName() << std::endl;
	out << x.getRealPrice() << std::endl;
	return out;
}

std::ifstream& operator>> (std::ifstream& in, goods& x){
	char buf[1024];
	in.getline(buf, 1024);
	double p;
	in >> p;
	in.ignore();
	x = goods(buf, p);
	return in;
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
