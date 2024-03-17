#include <iostream>
#include <fstream>
#include "dictpara.h"
#include "array.h"
#include <ctime>

int main(){

	const char fname[] = "en_ru.txt";
	std::ifstream inFile(fname);
	if(!inFile){
		std::cout<< "Can not open file "<< fname << std::endl;
		return 1;
	}
	
	Array<dictPara> Dictionary;
	dictPara X;
	int cnt=0;
	long tic = static_cast<long>(time(NULL));
	while(inFile.peek()!=EOF ){ // && cnt<10000
		inFile >> X;
		Dictionary.push_back(X);
		++cnt;
	}
	inFile.close();
	long toc = static_cast<long>(time(NULL));
	std::cout<< "Reading from file " << toc-tic << " sec" <<std::endl;
	std::cout<<"Total: "<< cnt << std::endl;
	std::cout<<"Size: "<< Dictionary.size() << std::endl;
	std::cout<<"Capacity: "<< Dictionary.capacity() << std::endl;

	Dictionary.sort();
/*
	for(int i=0; i<100 && i<Dictionary.size(); ++i){
		std::cout<< Dictionary[i];
	}
*/
	std::cout<< "\nFirst 100 words" <<std::endl;
	cnt = 0;
	for(auto pos = Dictionary.rbegin(); 
		pos != Dictionary.rend() && cnt <100; 
		++pos, ++cnt){
		std::cout << *pos;
	}

	std::cout<< "\nLast 100 words" <<std::endl;
	cnt = 0;
	for(auto pos = Dictionary.rbegin(); 
		pos != Dictionary.rend() && cnt <100; 
		++pos, ++cnt){
		std::cout << *pos;
	}


	char buf[128];
	do {
		std::cout << "> ";
		std::cin.getline(buf, 128);

		dictPara what(buf, "");
/*
	for(size_t i=0; i<Dictionary.size(); ++i){
			if (Dictionary[i] == what){
				std::cout << Dictionary[i];
			}
		}
*/
		auto pos = Dictionary.find(what);
		if (pos!=Dictionary.end()){
			std::cout<< *pos;
		}
	} while (strlen(buf) > 0);


	return 0;
}