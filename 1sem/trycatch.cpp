#include <iostream>

int gcd(int x, int y){
	if (x==0 || y==0) throw 0ULL;
	if (x < 0) throw "First argument negative";
	if (y < 0) throw "Second argument negative";
	while(x!=y){
		if (x>y)
			x -= y;
		else
			y -= x;
	}
	return x;
}

int main(){
	int x, y;
	while(true){
		std::cout << "x = ";
		std::cin >> x;
		std::cout << "y = ";
		std::cin >> y;
		try{
			std::cout << "GCD(x, y) = " << gcd(x, y) << std::endl;
		}
		catch(int error){
			std::cout << "Error: " << error << std::endl;
		}
		catch(const char * error){
			std::cout << "Error: " << error << std::endl;
		}
		catch(...){
			std::cout << "Unknown error." << std::endl;
		}
	}
	return 0;
}
