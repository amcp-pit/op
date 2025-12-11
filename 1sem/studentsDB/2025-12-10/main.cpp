#include <iostream>
#include <limits>
#include "student.h"
#include "mydatabase.h"

int get_int(){
	int tmp;
	std::cin >> tmp;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return tmp;
}

int menu() {
	for(int i = 0; i<40; ++i) std::cout.put('-');
	std::cout << std::endl;
	std::cout << "1. Open database\n";
	std::cout << "2. Print database\n";
	std::cout << "3. Save database\n";
	std::cout << "4. Export database\n";
	std::cout << "5. Add student\n";
	std::cout << "6. Set marks\n";
	std::cout << "7. Delete record\n";
	std::cout << "8. Sort\n";
	std::cout << "0. Exit\n";
	std::cout <<"> ";
	return get_int();
}

int sortMenu(){
	std::cout << "---------- Sorting methods ----------\n";
	std::cout << "1. By number\n";
	std::cout << "2. By surname\n";
	std::cout << "3. By marks\n";
	std::cout << "> ";
	return get_int();
}

int main(){
#if 0
	student x = {1, "Ivanov", "Ivan", {5, 4}};
	std::cout << x << std::endl;
	std::cin >> x;
	std::cout << x << std::endl;
	setMarks(x);
	std::cout << x << std::endl;
#endif
	Database DB = {0, 0, nullptr};

	const char dbfilename[] = "students.db";
	student tmp;
	int number, index;

	int action;
	do{
		action = menu();
		switch(action){
		case 1:
			if (!openDB(DB, dbfilename))
				std::cout << "Can not open file " << dbfilename << "\n" ;
			break;
		case 2: printDB(DB); break;
		case 3:
			if (!saveDB(DB, dbfilename))
				std::cout << "Can not write to file " << dbfilename << "\n" ;
			break;
		case 4:
			if (!exportDB(DB, "output.txt"))
				std::cout << "Can not write to file " << "output.txt" << "\n" ;
			break;
		case 5:
			std::cin >> tmp;
			addRecord(DB, tmp);
			break;
		case 6:
				number = get_int();
				index = findRecord(DB, number);
				if (index >=0 ){
					tmp = getRecord(DB, index);
					setMarks(tmp);
					updateRecord(DB, index, tmp);
				} else {
					std::cout << "There are no any student with st" << number << std::endl;
				}
			break;
		case 7:
			number = get_int();
			index = findRecord(DB, number);
			if (index != -1){
				std::cout << "Are you sure? (Y/N)";
				char ch[128];
				std::cin.get(ch, 128);
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				if (ch[0]=='Y' || ch[0]=='y'){
					deleteRecord(DB, index);
				}
			}
			break;
		case 8:
			number = sortMenu();
			switch(number){
			case 1: sort(DB, compByNumber); break;
			case 2: sort(DB, compBySurname); break;
			case 3: sort(DB, compByMarks);break;
			}
			std::cout << "Database sorted\n";
			break;
		}
	} while(action != 0);

	delete[] DB.data;

	return 0;
}

