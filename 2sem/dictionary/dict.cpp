#include <iostream>
#include <fstream>
#include "stroka.h"
#include "dictpara.h"
#include "array.h"

std::ostream& operator<<(std::ostream& out, const DictPara& X){
	out << X.get_word() << ": " << X.get_translate() << "\n";
	return out;
}

std::ifstream& operator>> (std::ifstream& in, DictPara& X){
	char buf[1024];
	in.getline(buf, 1024);
	char* p = buf;
	while( (*p!='\t') && (*p!='\0') ){
		++p;
	}
	if (*p != '\0'){
		*p = '\0';
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

    DictPara X;
	Array<DictPara> dictionary;
    while(inFile.peek() != EOF){
        inFile >> X;
		dictionary.push_back(X);
    }
	inFile.close();
	std::cout << "Words: " << dictionary.size() << std::endl;
	std::cout << "Capacity: " << dictionary.capacity() << std::endl;
	std::cout << "sizeof(DictPara) : " << sizeof(DictPara) << std::endl;
	std::cout << "overhead (minimum): " << (dictionary.capacity() - dictionary.size()) * sizeof (DictPara) << std::endl; 

	for(size_t i=0; i < 10; ++i){
		std::cout << dictionary[i];
	}

	int counter = 10;
	for(auto pos=dictionary.rbegin();
		counter > 0 && pos!=dictionary.rend();
		++pos, --counter){
		std::cout << *pos;
	}

	dictionary.sort();

	char word[128];
	do{
		std::cout << "> ";
		std::cin.getline(word, 128);
		DictPara what(word, "");
/*
        for(size_t i=0; i < dictionary.size(); ++i){
            if (what == dictionary[i]){
                std::cout << dictionary[i] << std::endl;
            }
        }
*/
/*		for(auto pos = dictionary.begin();
			pos != dictionary.end();
			++pos){
			if (what == *pos){
				std::cout << *pos << std::endl;
			}
		}
*/
		auto pos = dictionary.find( what );
		for(int i=0; i<10000; ++i){
			pos = dictionary.find( what );
		}
		if (pos != dictionary.end()){
			std::cout << *pos << std::endl;
		}

	} while (stroka(word) != "");

	return 0;
}
