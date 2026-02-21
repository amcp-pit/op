#include <iostream>

class number {
protected:
	int value_;
public:
	number(int x = 0) : value_(x) {}
	void setval(int x) { value_ = (x < 0) ? -x : x; }
	virtual void show() = 0; // pure virtual
	virtual ~number() { std::cout << "Kill like number" << std::endl; }
};
// class number abstract class, because show() is pure virtual


class dectype : public number {
public:
	dectype(int x=0) : number(x) {}
	void show() {std::cout << "Decimal: " << std::dec << value_ << std::endl;}
	~dectype() { std::cout << "Kill like decimal " << std::endl; }
};

class octtype : public number {
public:
	octtype(int x=0) : number(x) {}
    void show() {std::cout << "Octal: 0" << std::oct << value_ << std::endl;}
    ~octtype() { std::cout << "Kill like oct " << std::endl; }
};


class hextype : public number {
public:
	hextype(int x=0) : number(x) {}
    void show() {std::cout << "Hex: 0x" << std::hex << value_ << std::endl;}
    ~hextype() { std::cout << "Kill like hex " << std::endl; }
};


number * factory(){
	std::cout << "Input integer type (1..3): ";
	int n;
	std::cin >> n;
	number * p = nullptr;
	switch(n%3){
	case 1: p = new dectype; break;
	case 2: p = new octtype; break;
	default: p = new hextype;
	}
	return p;
}

int main(){
	// number x(1);
	dectype a(317);
	a.show();

	hextype b(250);
	b.show();

	number * p;
	int counter = 5;
	while(counter-- > 0){
		p = factory();
		p->setval(rand()%1000);
		p->show();
		delete p;
	}

	return 0;
}
