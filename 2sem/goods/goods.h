#include <cstring>
#include <iostream>

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

	goods(const goods& x) : price_(x.price_){
        size_t len = strlen(x.name_);
        name_ = new char[len+1];
        strcpy(name_, x.name_);
		++counter;
	}

	goods& operator=(const goods& x);

	~goods(){
		delete[] name_;
		--counter;
	}
	const char * getName() const {return name_;}
	double getPrice() const {return (1 + percent) * price_;}
    double getRealPrice() const {return price_;}
	static int total(){return counter;}
	static void setPercent(double p) {
		percent = (p < -1.0) ? -1.0 : p;
	}
};

std::ostream& operator<< (std::ostream&, const goods&);
