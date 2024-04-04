#include <iostream>

class number{ // abstract class
private:
	char ch;
protected:
	int value;
public:
	number(int x=0, char name='d') : value(x), ch(name) {}
	void setval(int x) { value=x; }
	virtual void show() = 0; // pure virtual
	virtual ~number() { std::cout<< "Kill as number (" << ch <<") "<< value << std::endl;}
};

class dectype : public number {
public:
	dectype(int x=0) : number(x) {}
	void show(){
		std::cout << "Decimal: " << std::dec << number::value << std::endl;
	}
	~dectype() {std::cout << "Kill as decimal "<< value << std::endl;}
};

class hextype : public number{
public:
	hextype(int x=0) : number(x, 'h') {}
	void show(){
		std::cout << "Hex: 0x" << std::hex << value << std::dec << std::endl;
	}
	~hextype() {std::cout << "Kill as hex "<< value << std::endl;}
};

class octtype : public number{
public:
	octtype(int x=0) : number(x, 'o') {}
	void show(){
		std::cout << "Oct: 0" << std::oct << value << std::dec << std::endl;
	}
	~octtype() {std::cout << "Kill as oct "<< value << std::endl;}
};

number* factory(){
	std::cout<<"Input integer type (1..3): ";
	int N;
	std::cin >> N;
	switch(N%3){
	case 1: return new dectype; break;
	case 2: return new hextype; break;
	default: return new octtype;
	}
}

int main(){
	dectype A(rand());
	hextype B(rand());
	A.show();
	B.show();

	number* p;
	int counter = 5;
	while(counter--){
		p = factory();
		p->setval(rand()%1000);
		p->show();
		delete p;
	}

	return 0;
}