#include "goods.h"

#include <iostream>
#include <cstring>
#include <fstream>

double goods::percent = 0.25;
int goods::counter = 0;

goods& goods::operator=(const goods& X){
		if (this != &X){
			delete[] name_;
	        size_t len =strlen(X.name_);
	        name_ = new char[len+1];
	        strcpy(name_, X.name_);
			price_ = X.price_;
		}
		return *this;
}


std::ostream& operator<< (std::ostream& out, const goods & X){
	out << X.getName() << ":\t" << X.getPrice();
	return out; 
}

std::ifstream& operator>> (std::ifstream& in, goods& X){
	char buf[1024];
	in.getline(buf, 1024);
	double p;
	in >> p;
	in.ignore();
	X = goods(buf, p);
	return in;
}

std::ofstream& operator<<(std::ofstream& out, goods& X){
	out << X.getName() << std::endl;
	out << X.getRealPrice() << std::endl;
	return out;
}
