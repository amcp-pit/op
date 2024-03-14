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

	char buf[128];
	do {
		std::cout << "> ";
		std::cin.getline(buf, 128);

		dictPara what(buf, "");
		for(size_t i=0; i<Dictionary.size(); ++i){
			if (Dictionary[i] == what){
				std::cout << Dictionary[i];
			}
		}
	} while (strlen(buf) > 0);


	return 0;
}