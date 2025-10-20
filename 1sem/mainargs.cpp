#include <iostream>

int main(int argc, char* argv[], char* env[]){

	for(int i=0; i<argc; ++i){
		std::cout << i << ": " << argv[i] << std::endl;
	}

	int j = 0;
	while(env[j] != nullptr){
		std::cout << j <<": " << env[j] << std::endl;
		++j;
	}

	return 0;
}
