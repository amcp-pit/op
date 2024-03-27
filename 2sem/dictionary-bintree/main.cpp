#include <iostream>
#include <fstream>
#include <ctime>
#include "dictpara.h"
#include "bintree.h"

int main(){
	const char fname[] = "en_ru.txt";
	std::ifstream inFile(fname);
	if(!inFile){
		std::cout<< "Can not open file "<< fname << std::endl;
		return 1;
	}
	
	BinTree<dictPara> Dictionary;
	dictPara X;
	int cnt=0;
	long tic = static_cast<long>(time(NULL));
	while(inFile.peek()!=EOF ){ // && cnt<10000
		inFile >> X;
		Dictionary.insert(X);
		++cnt;
	}
	inFile.close();
	long toc = static_cast<long>(time(NULL));
	std::cout<< "Reading from file " << toc-tic << " sec" <<std::endl;
	std::cout<<"Total: "<< cnt << std::endl;
	std::cout<<"Size: "<< Dictionary.size() << std::endl;
	std::cout<<"Height: "<< Dictionary.height() << std::endl;
	
	for(auto pos=Dictionary.begin(); pos!=Dictionary.end(); ++pos){
		std::cout << *pos ;
	}


/*
	char buf[128];
	do {
		std::cout << "> ";
		std::cin.getline(buf, 128);

		dictPara what(buf, "");

		long tic = static_cast<long>(time(NULL));
		auto pos = Dictionary.find(what);
		int cnt=1000;
		while(cnt>0){
			pos = Dictionary.find(what);
			--cnt;
		}
		long toc = static_cast<long>(time(NULL));
		std::cout<< "Find at " << toc-tic << " sec" <<std::endl;

		if (pos!=Dictionary.end()){
			std::cout<< *pos;
			Dictionary.erase(pos);
		}
	} while (strlen(buf) > 0);
*/
	return 0;
}