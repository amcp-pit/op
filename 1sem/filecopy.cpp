#include <iostream>
#include <fstream>

int main(int argc, char* argv[]){
	if (argc != 3){
		std::cout << "Use: \t "<<argv[0]<< " from_file to_file" << std::endl;
		return 0;
	}
    std::ifstream inFile;
    inFile.open(argv[1]);
    if (!inFile){
        std::cout << "Can not open file '" << argv[1] <<"'" <<std::endl;
        return 1;
    }

    std::ofstream outFile;
    outFile.open(argv[2]);
    if (!outFile){
        std::cout << "Can not open file '" << argv[2] <<"'" <<std::endl;
		inFile.close();
        return 2;
    }

	int ch;
	unsigned int counter = 0;
    while( (ch = inFile.get()) != EOF ) {
        outFile.put(ch);
		++counter;
    }

    inFile.close();
	outFile.close();
	std::cout << "Total " << counter << " bytes" << std::endl;
    return 0;
}

