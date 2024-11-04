#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
	if (argc<3) {
		std::cout<<"Use " << argv[0] <<" source destination"<<std::endl;
		return 1;
	}

	std::ifstream inFile(argv[1], std::ios_base::binary);
	if (!inFile){
		std::cerr << "Can not open file " << argv[1] <<std::endl;
		return 1;
	}

	std::ofstream outFile(argv[2], std::ios_base::binary); // | std::ios_base::app
	if (!outFile){
		std::cerr << "Can not open file " << argv[2] <<std::endl;
		inFile.close();
		return 2;
	}

	int ch;
	int counter=0;
	while( (ch = inFile.get()) != EOF ){
		outFile.put(ch);
		++counter;
	}
	std::cout<<"Copied "<< counter << " bytes" <<std::endl;

	// Скопируем файл второй раз
	inFile.clear();
	inFile.seekg(0, std::ios_base::beg);
	counter=0;
	// std::ios_base::end, std::ios_base::cur
	while( (ch = inFile.get()) != EOF ){
		outFile << ch;
		++counter;
	}
	std::cout<<"Copied "<< counter << " bytes" <<std::endl;
	
	inFile.close();
	outFile.close();

	return 0;
}