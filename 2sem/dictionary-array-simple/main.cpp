#include <iostream>
#include <fstream>
#include "dictpara.h"
#include "array.h"

int main(){
/*	stroka str("Hello");
	stroka str2("world");
	std::cout << str + " " + str2+ "!" <<std::endl;
*/
	const char fname[] = "en_zh.txt";

	std::ifstream inFile(fname);
	if(!inFile){
		std::cout<< "Can not open file "<< fname << std::endl;
		return 1;
	}
	
	Array<dictPara> Dictionary;
	dictPara X;
	int cnt=0;
	while(inFile.peek()!=EOF && cnt<1000){
		inFile >> X;
		Dictionary.push_back(X);
		++cnt;
	}
	inFile.close();

	std::cout<<"Total: "<< cnt << std::endl;


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