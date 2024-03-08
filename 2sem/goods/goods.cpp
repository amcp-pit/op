#include "goods.h"

int goods::counter = 0;
double goods::percent = 0.5;

std::ostream& operator<<(std::ostream& out, const goods& X){
	out<< X.getName() <<":\t"<< X.getPrice();
	return out;
}

std::istream& operator>> (std::istream& in, goods& X){
	char tmp[1024];
	in.getline(tmp, 1024);
	double p;
	in >> p;
	X = goods(tmp, p);
	return in;
}

std::ofstream& operator<<(std::ofstream& out, const goods& X){
	out.write(X.getName(), strlen(X.getName()));
	out << std::endl;
	out << X.getRealPrice() << std::endl;
	return out;
}
