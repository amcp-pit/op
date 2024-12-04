#include <iostream>
#include <limits>
#include "utils.h"

int get_int(){
	int tmp;
	std::cin >> tmp;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return tmp;
}

int menu() {
	for (int i = 0; i < 40; ++i) std::cout.put('*');
	std::cout << std::endl;
	std::cout << "1. Open database\n";
	std::cout << "2. Print database\n";
	std::cout << "3. Save database\n";
	std::cout << "4. Export database\n";
	std::cout << "5. Add student\n";
	std::cout << "6. Set marks\n";
	std::cout << "7. Delete record\n";
	std::cout << "8. Sort students\n";
	std::cout << "0. Exit" << std::endl;
	return  get_int();
}

int sortMenu(){
	std::cout << "------------- Sorting method -------------\n";
	std::cout << "1. By number\n";
	std::cout << "2. By surname name\n";
	std::cout << "3. By marks" << std::endl;
	return  get_int();
}

int get_number(){
	std::cout << "Student number: ";
	return get_int();
}
