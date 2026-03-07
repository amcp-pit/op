#include <iostream>
#include <fstream>
#include "stroka.hpp"
#include "dictpara.hpp"
#include "array.hpp"

std::ostream& operator<< (std::ostream& out, const DictPara& X) {
	out << X.get_word()<<": " << X.get_translate() << "\n";
	return out;
}

std::ifstream& operator>> (std::ifstream& in, DictPara& X) {
	char buf[1024];
	in.getline(buf, 1024);
	char* p = buf;
	while( (*p!='\t') && (*p!='\0')){
		++p;
	}
	if (*p != '\0') {
		*p= '\0';
		++p;
	}
	X = DictPara(buf, p);
	return in;
}



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

/*
	DictPara X;
	char word[128];
	std::cout << "> ";
	std::cin.getline(word, 128);
	DictPara what(word, "");
	while(inFile.peek() != EOF){
        inFile >> X;
		if (X == what) {
			std::cout << X << std::endl;
			break;
		}
	}
*/

    DictPara X;
	Array<DictPara> dictionary;

	// Read from file
    while(inFile.peek() != EOF){
        inFile >> X;
		dictionary.push_back(X);
    }

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
