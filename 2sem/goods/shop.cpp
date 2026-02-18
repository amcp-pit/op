#include <iostream>
#include "goods.h"

void info(){
    std::cout << "Total: " << goods::total() << std::endl;
}

void print(const goods shop[], int n){
	for(int i=0; i<n; ++i){
		std::cout << i+1 <<". " << shop[i] << std::endl;
	}
	info();
}

void eat(goods x){
	std::cout << "Eat: " << x.getName();
	std::cout << ", health += " << x.getRealPrice() << std::endl;
	info();
}

int main(){
	info();
	const char *dbname = "basa.txt";
	const int N = 5;
	goods shop[N] = {
					 goods("apple", 140.0),
					 goods("orange", 160.0),
					 goods("pineapple", 250.0),
					 goods("banana", 90.0)
					};

	print(shop, N);
	eat(shop[2]);
	print(shop, N);
	shop[N-1] = goods("tomato", 350.0);
	shop[0] = shop[0];
	print(shop, N);

	std::cout << "----------- Read from file -------------\n";
	std::ifstream inFile(dbname);
	if (inFile){
		int i = 0;
		while(inFile.peek()!=EOF && i<N){
			inFile >> shop[i];
			++i;
		}
		inFile.close();
	}
	print(shop, N);

	std::cout << "********** Christmas discount **********\n";
	// goods::percent = 0.0;
	shop[0].setPercent(0.1);
	print(shop, N);
	goods::setPercent(0.01);
	print(shop, N);

	std::ofstream outFile(dbname);
	if (outFile){
		for(int i=0; i<N; ++i){
			outFile << shop[i];
		}
		 outFile.close();
	}
	return 0;
}
