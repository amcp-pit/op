#include <iostream>
#include <cstring>

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

	goods& operator=(const goods& X){
		if (this != &X){
			delete[] name_;
	        size_t len =strlen(X.name_);
	        name_ = new char[len+1];
	        strcpy(name_, X.name_);
			price_ = X.price_;
		}
		return *this;
	}

	double getPrice() const { return (1.0 + percent)*price_; }
	double getRealPrice() const { return price_; }
	const char* getName() const { return name_; }
	static void setPercent(double p) {
		percent = (p<=0) ? 0.01 : p;
	}
	static int total() {return counter;}
};

double goods::percent = 0.25;
int goods::counter = 0;

std::ostream& operator << (std::ostream& out, const goods & X){
	out << X.getName() << ":\t" << X.getPrice();
	return out; 
}

void eat(goods X){
	std::cout << "Eat: " << X.getName();
	std::cout << ", health+=" << X.getRealPrice() << std::endl;
    std::cout << "Total: " << goods::total() << std::endl;

}


int main(){
	const int N = 5;
	goods shop[N] = { goods("apple", 140.0),
					  goods("orange", 160.0),
					  goods("pineapple", 250.0),
					  goods("banana", 90.0)
					};

	for(int i=0; i<N; ++i){
		std::cout << i+1 << ". " << shop[i] << std::endl;
	}
	std::cout << "Total: " << goods::total() << std::endl;

	eat(shop[2]);

	for(int i=0; i<N; ++i){
		std::cout<< i+1 << ". " << shop[i] << std::endl;
	}
    std::cout << "Total: " << goods::total() << std::endl;

	shop[N-1] = goods("tomato", 350.0);

	goods * ch = &shop[3];
	// .......................
	shop[3] = *ch;

    for(int i=0; i<N; ++i){
        std::cout<< i+1 << ". " << shop[i] << std::endl;
    }
    std::cout << "Total: " << goods::total() << std::endl;



	std::cout << "************* Christmas discount *************\n";
	//goods::percent = 0.01;
	shop[0].setPercent(0.01);
	goods::setPercent(0.01);

    for(int i=0; i<N; ++i){
        std::cout<< i+1 << ". " << shop[i] << std::endl;
    }
    std::cout << "Total: " << goods::total() << std::endl;

}
