#include <iostream>
#include <cstring>
#include <fstream>
#include "goods.h"

void eat(goods X){
	std::cout << "Eat: " << X.getName();
	std::cout << ", health+=" << X.getRealPrice() << std::endl;
    std::cout << "Total: " << goods::total() << std::endl;

}

int main(){
	const char dbname[] = "basa.txt";
	const int N = 5;
	goods shop[N] = { goods("apple", 140.0),
					  goods("orange", 160.0),
					  goods("pineapple", 250.0),
					  goods("banana", 90.0)
					};

	for(int i=0; i<N; ++i){
		std::cout << i+1 << ". " << shop[i] << std::endl;
	}
	std::cout << "Total: " << goods::total() << std::endl;

	eat(shop[2]);

	for(int i=0; i<N; ++i){
		std::cout<< i+1 << ". " << shop[i] << std::endl;
	}
    std::cout << "Total: " << goods::total() << std::endl;

	shop[N-1] = goods("tomato", 350.0);

	goods * ch = &shop[3];
	// .......................
	shop[3] = *ch;

    for(int i=0; i<N; ++i){
        std::cout<< i+1 << ". " << shop[i] << std::endl;
    }
    std::cout << "Total: " << goods::total() << std::endl;

	std::ifstream inFile(dbname);
	if (inFile){
		int i=0;
		while(inFile.peek()!=EOF && i<N){
			inFile >> shop[i];
			++i;
		}
		inFile.close();
	}



	std::cout << "************* Christmas discount *************\n";
	//goods::percent = 0.01;
	shop[0].setPercent(0.01);
	goods::setPercent(0.01);

    for(int i=0; i<N; ++i){
        std::cout<< i+1 << ". " << shop[i] << std::endl;
    }
    std::cout << "Total: " << goods::total() << std::endl;

	std::ofstream outFile(dbname);
	if (outFile){
		for(int i=0; i<N; ++i){
			outFile << shop[i];
		}
		outFile.close();
	}

}
