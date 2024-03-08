#include <iostream>
#include "mycomplex.h"

int main(){
	Complex x (3, 2);
	Complex x1 = x.conj();
	const Complex y(1, -4);
	Complex y1(-1, 5);
	Complex z;
	try{
		z = x*y-x1*y1;
		z += 2;
		z /= (x-y);
		std::cout<< "z = " << z <<std::endl;
	}catch(const char* error){
			std::cout << "Error: " << error <<std::endl;
	}
	return 0;
}