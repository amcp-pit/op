#include <iostream>

class number {
private:
	char ch;
protected:
	int value;
public:
	number(int x = 0, char name='d') : value(x), ch(name) {}
	void setval(int x) {value = x<0 ? -x : x;}
	virtual void show() = 0; // pure virtual
	virtual ~number() { std::cout<< "Kill like number (" << ch << ")" <<std::endl; }
};


class dectype : public number {
public:
	dectype(int x = 0) : number(x, 'd') {}
	void show() override {std::cout<< "Decimal: " << std::dec << value <<std::endl;}
    ~dectype() { std::cout<< "Kill like decimal"<<std::endl; }
};

class hextype : public number {
public:
    hextype(int x = 0) : number(x, 'h') {}
    void show() {std::cout<< "Hex: 0x" << std::hex << value <<std::endl;}
    ~hextype() { std::cout<< "Kill like hex"<<std::endl; }
};

class octtype : public number {
public:
    octtype(int x = 0) : number(x, 'o') {}
    void show() {std::cout<< "Octal: 0" << std::oct << value <<std::endl;}
    ~octtype() { std::cout<< "Kill like octal"<<std::endl; }
};

number* factory(){
	std::cout<<"Input integer type (1..3): ";
	int n;
	std::cin >> n;
	number *p;
	switch(n%3){
	case 1: p = new dectype; break;
	case 2: p = new octtype; break;
	default: p = new hextype;
	}
	return p;
}


int main(){
	// number x(1);

	dectype a(250);
	// a.value = 1;
	a.show();

	hextype b(250);
	b.show();

	number *p;
	int counter = 5;
	while(counter-- > 0){
		p = factory();
		p->setval(rand()%1000);
		p->show();
		delete p;
	}

	return 0;
}
