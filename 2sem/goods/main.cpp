#include <iostream>
#include <fstream>
#include "goods.h"

void eat(goods A){
	std::cout <<" Eat: " << A.getName();
	std::cout <<", health+"<< A.getRealPrice() << std::endl;
}

int main(){
	const int N = 5;
	goods shop[N] = {
					goods("apple", 30.0),
					goods("orange", 45.0),
					goods("pineapple", 100.0),
					goods("banana", 24.0)
	};
	std::cout << "-------- Initialization --------------------" << std::endl;

	for(int i=0; i < N; ++i){
		std::cout<< i+1 << ". " << shop[i] << std::endl;
	}
	std::cout<<"Total: " << goods::total() << std::endl;
	//std::cout<<"Total: " << shop[0].total()<< std::endl;

	eat(shop[3]);
	
	shop[N-1] = goods("tomato", 200.0);

	std::cout << "-------- After adding a product  ------------" << std::endl;
	for(int i=0; i < N; ++i){
		std::cout<< i+1 << ". " << shop[i] << std::endl;
	}

	std::cout << "-------- Change percent to 20% --------------" << std::endl;
	// goods::percent = 0.2;
	goods::setPercent(0.2);
	for(int i=0; i < N; ++i){
		std::cout<< i+1 << ". " << shop[i] << std::endl;
	}
	std::cout<<"Total: " << goods::total() << std::endl;


	std::cout << "-------- Christmas discount ------------------" << std::endl;
	shop[0].setPercent(0.01);
	for(int i=0; i < N; ++i){
		std::cout<< i+1 << ". " << shop[i] << std::endl;
	}
	std::cout<<"Total: " << goods::total() << std::endl;

	std::ofstream outFile("basa.txt");
	for(int i=0; i<N; ++i){
		outFile << shop[i];
	}
	outFile.close();

	return 0;
}