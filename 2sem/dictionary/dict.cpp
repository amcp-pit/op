#include <iostream>
#include <fstream>
#include "stroka.hpp"

int main(int argc, char* argv[]){
	if (argc!=2){
		std::cout << "Use "<< argv[0] << " dictionary_file_name\n";
		return 0;
	}
	char* fname = argv[1];

	std::ifstream inFile(fname);
	if (!inFile){
		std::cerr << "Can not open file "<< fname << "\n";
		return 1;
	}

/* TODO:
    DictPara X;
	Array<DictPara> dictionary;

	// Read from file
    while(inFile.peek() != EOF){
        inFile >> X;
		dictionary.push_back(X);
    }
*/
	inFile.close();

/* TODO:
	std::cout << "Words: " << dictionary.size() << std::endl;
	std::cout << "Capacity: " << dictionary.capacity() << std::endl;

	// First 10 records

	for(size_t i=0; i < 10; ++i){
		std::cout << dictionary[i];
	}

	char word[128];
	do{
		std::cout << "> ";
		std::cin.getline(word, 128);
		DictPara what(word, "");
		auto pos = dictionary.find( what );
		if (pos != dictionary.end()){
			std::cout << *pos << std::endl;
		}
	} while (stroka(word) != "");
*/

	return 0;
}
