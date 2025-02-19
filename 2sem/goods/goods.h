//#pragma once

#include <iostream>
#include <cstring>
#include <fstream>

class goods{
	char * name_;
	double price_;
	static double percent;
	static int counter;
public:
	goods(const char *name="", double price=0.0) : price_(price){
		size_t len = strlen(name);
		name_ = new char[len+1];
		strcpy(name_, name);
		++counter;
	}

	goods(const goods& X) : price_(X.price_) {
		size_t len =strlen(X.name_);
		name_ = new char[len+1];
		strcpy(name_, X.name_);
		++counter;
	}

	~goods(){
		delete[] name_;
		--counter;
	}

	goods& operator=(const goods& X);

	double getPrice() const { return (1.0 + percent)*price_; }
	double getRealPrice() const { return price_; }
	const char* getName() const { return name_; }
	static void setPercent(double p) {
		percent = (p<=0) ? 0.01 : p;
	}
	static int total() {return counter;}
}; // end of class goods

std::ostream&  operator<< (std::ostream& out, const goods & X);
std::ofstream& operator<< (std::ofstream& out, goods & X);
std::ifstream& operator>> (std::ifstream& in, goods & X);

