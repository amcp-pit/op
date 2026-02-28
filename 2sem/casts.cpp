#include <iostream>

class Parent {
public:
	virtual void foo () {
		std::cout << "Hi from Parent::foo()\n";
	}
	void bar() {
		std::cout << "Hi from Parent::bar()\n";
	}
};

class Child : public Parent {
	int x;
public:
	Child() : x(10) {}
	void foo () {
		std::cout << "Hi from Child::foo()\n";
	}
	void bar () {
		std::cout << "Hi from Child::bar()\n";
	}
	void methodSpecific4Child() {
		std::cout << "Child::methodSpecific4Child(), x=" << x << "\n";
	}
};

void myfunction(Parent * p){
	std::cout << "---------- Myfunction * -----------\n";
	p->foo();
	p->bar();

	Child* x = dynamic_cast<Child*>(p);
	if (x) {
		x->methodSpecific4Child();
		x->foo();
		x->bar();
	} else {
		std::cout << "Object is not like Child\n";
	}
}

void myfunction(Parent & p){
    std::cout << "---------- Myfunction & -----------\n";
    p.foo();
    p.bar();

	try{
		Child& x = dynamic_cast<Child&>(p);
        x.methodSpecific4Child();
        x.foo();
        x.bar();
	} catch(std::bad_cast &error) {
		std::cout << error.what() << std::endl; 
		std::cout << "Object is not like Child\n";
	}

}



int main() {
	int a = 1, b = 2;
	double c;
	c = a / b;
	std::cout << "c = a / b = " << c << std::endl;

    c = (double)a / (double)b;
    std::cout << "c = a / b = " << c << std::endl;

	c = 1.0 / static_cast<double>(b);
    std::cout << "c = 1 / b = " << c << std::endl;

	char ss[] = "Hello";
	std::cout << ss << std::endl;
	ss[0] = 'h';
    std::cout << ss << std::endl;
//	++ss;
//    std::cout << ss << std::endl;

	const char *str = "Hello 2";
//	str[0] = 'h';
	++str;
	std::cout << str << std::endl;

	char *s;
	s = const_cast<char*>(str);
	int len = 0;
	while( *(s++) != '\0') ++len;
	std::cout << "Length: " << len << std::endl;

	s = const_cast<char*>(str);
	//s[0] = '@';

    std::cout << str << std::endl;

	Parent p;
	p.foo();
	p.bar();

	Child ch;
	ch.foo();
	ch.bar();
    ch.Parent::foo();
	ch.Parent::bar();
	ch.methodSpecific4Child();

	std::cout << "4 Parent *:\n";
	myfunction(&p);

    std::cout << "4 Child *:\n";
    myfunction(&ch);

    std::cout << "4 Parent:\n";
    myfunction(p);

    std::cout << "4 Child:\n";
    myfunction(ch);


	return 0;
}
