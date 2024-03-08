#pragma once
#include <iostream>
#include <fstream>

class goods{
private:
	char *name_;
	double price_;
	static int counter;
	static double percent;
public:		
	goods(const char *name="", double price=0.0) : price_(price){
		size_t len = strlen(name)+1;
		name_ = new char[len];
		//strcpy(name_, name);
		strcpy_s(name_, len, name);
		++counter;
	}

	goods(const goods& X) : price_(X.price_) {
		size_t len = strlen(X.name_)+1;
		name_ = new char[len];
		//strcpy(name_, X.name_);
		strcpy_s(name_, len, X.name_);
		++counter;
	}

	~goods(){
		delete[] name_;
		--counter;
	}

	goods& operator=(const goods& X){
		if (this != &X) {
			price_ = X.price_;
			size_t len = strlen(X.name_)+1;
			delete[] name_;
			name_ = new char[len];
			strcpy_s(name_, len, X.name_);
		}
		return *this;
	}

	double getPrice() const {return this->price_*(1.0+percent);}
	double getRealPrice() const {return price_;}
	const char* getName() const {return name_;}
	static int total() { return counter;}
	static void setPercent(double p) { percent = (p<-1) ? -1.0 : p; }
};

std::ostream& operator<<(std::ostream& out, const goods& X);
std::istream& operator>> (std::istream& in, goods& X);
std::ofstream& operator<<(std::ofstream& out, const goods& X);
