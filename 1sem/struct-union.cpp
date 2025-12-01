#include <iostream>

union bytecod {
	unsigned char ch;
	struct {
		unsigned char a0 : 1;
		unsigned char a1 : 1;
		unsigned char a2 : 1;
		unsigned char a3 : 1;
		unsigned char a4 : 1;
		unsigned char a5 : 1;
		unsigned char a6 : 1;
		unsigned char a7 : 1;
	} byte;
};

std::ostream& operator<< (std::ostream& out, const bytecod& b){
	out << (int)b.byte.a7 
		<< (int)b.byte.a6
		<< (int)b.byte.a5
		<< (int)b.byte.a4
		<< (int)b.byte.a3
		<< (int)b.byte.a2
		<< (int)b.byte.a1
		<< (int)b.byte.a0;
	return out;
}

union cod32 {
	int x;
	bytecod b[4];
};

std::ostream& operator<< (std::ostream& out, const cod32& c){
	out << c.x <<": ";
	for(int i=3; i>=0; --i){
		out << (int)c.b[i].ch << ".";
	}
	std::cout << ": ";
	for(int i=3; i>=0; --i){
		out << c.b[i] << ".";
	}
	return out;
}

int main(){
	bytecod x;
	x.ch = 'a';
	std::cout << "x = " << x << std::endl;

	cod32 y;
	y.x = 256;
	std::cout << "y = " << y << std::endl;
	do {
		std::cout <<"> ";
		std::cin >> y.x;
		std::cout << "y = " << y << std::endl;
	}while(y.x!=0);

	return 0;
}
