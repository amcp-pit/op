#include <iostream>

class Parent{
public:
	virtual void foo() {std::cout << "Hi from Parent::foo()\n"; }
	void bar() {std::cout << "Hi from Parent::bar()\n"; }
};

class Child : public Parent {
	int x;
public:
	Child() : x(10) {}
	void foo() {std::cout << "Hi from Child::foo()\n";}
	void bar() {std::cout << "Hi from Child::bar()\n"; }
	void methodSpecific4Child(){
		std::cout << "Child::methodSpecific4Child(), x="<< x << "\n";
	}
};


void myfunction (Parent * p){
	std::cout << "------- Myfunction * ---------\n";
	p->foo();
	p->bar();

	Child* X = dynamic_cast<Child*>(p);
	if (X){
		X->methodSpecific4Child();
		X->foo();
		X->bar();
	}else
		std::cout << "Object is not like Child\n";
}

void myfunction(Parent &p){
    std::cout << "------- Myfunction & ---------\n";
    p.foo();
    p.bar();

	try{
		Child& X = dynamic_cast<Child&>(p);
		X.methodSpecific4Child();
		X.foo();
		X.bar();
	}catch(std::bad_cast &error){
		std::cout << error.what() <<std::endl;
		std::cout << "Object is not like Child\n";
	}

}



int main(){
	int a = 1, b = 2;
	double c;
	c = a / b;
	std::cout << "c = a/b = " << c << std::endl;

	c = (double)a / (double)b;
    std::cout << "c = " << c << std::endl;

	c = 1.0 / static_cast<double>(a);

	char ss[] = "Hello";
	//++ss;
	ss[0] = 'h';

	const char *str = "Hello 2";
	//++str;
	//str[0] = 'h';

	std::cout << ss << std::endl;

	char *s;
	s = const_cast<char*>(str);
	int length = 0;
	while(*(s++)!='\0') ++length;

	s = const_cast<char *>(str);
	// s[0] = 'h';
	std::cout << "Length of '" << s << "': " << length <<std::endl;


	Parent p;
	p.foo();
	p.bar();

	Child ch;
	ch.foo();
	ch.bar();
	ch.Parent::bar();
	ch.methodSpecific4Child();

	std::cout << "4 parent *: \n";
	myfunction(&p);

    std::cout << "4 child *: \n";
    myfunction(&ch);

    std::cout << "4 parent &: \n";
    myfunction(p);

    std::cout << "4 child &: \n";
    myfunction(ch);


	struct {double x; float y; } S;
	S.x = 1.0;
	S.y = 4.5;

	double *f;
	f = reinterpret_cast<double*>(&S);

	std::cout << "*f = " << *f << std::endl;
	*f = 2.0;
    std::cout << "S.x = " << S.x << std::endl;

	unsigned long z;
	z = reinterpret_cast<unsigned long>(&S);
	std::cout << "&S = " << &S << std::endl;
	std::cout << "z = " << z << std::endl;

	z += 8;

	float* d = reinterpret_cast<float*>(z);
	std::cout << "*d = " << *d << std::endl; 
	return 0;
}
