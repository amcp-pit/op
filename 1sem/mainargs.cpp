#include <iostream>

int main(int argc, char* argv[], char* env[]) {
	std::cout << "argc = " << argc <<std::endl;

	for(int i = 0; i < argc; ++i) {
		std::cout<< i <<": \t" << argv[i] <<std::endl;
	}

	int j = 0;
	while(env[j] != nullptr) {
		std::cout<< j <<": \t" << env[j] <<std::endl;
		++j;
	}

	j=0;
	char* username = nullptr;
	while(env[j] != nullptr){
		if(strstr(env[j], "USERNAME") != nullptr){
			username = strstr(env[j], "=") + 1;
			break;
		}
		++j;
	}
	if (username) {
		std::cout<<"Hello, " << username <<std::endl;
	}

	return 0;
}