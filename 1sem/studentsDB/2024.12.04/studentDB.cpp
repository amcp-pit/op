﻿#include <iostream>
#include "utils.h"
#include "student.h"
#include "mydatabase.h"

int main() {
	DataBase DB = {0, 0, nullptr};
	const char dbfilename[] = "student.db";
	const char exportfilename[] = "students.txt";
	int action;
	student tmp;
	int number;
	int index;

	do {
		action = menu();
		switch (action) {
		case 1: openDB(DB, dbfilename); break;
		case 2: printDB(DB); break;
		case 3: saveDB(DB, dbfilename); break;
		case 4: exportDB(DB, exportfilename); break;
		case 5: std::cin >> tmp;
				addRecord(DB, tmp);
				break;
		case 6:	number = get_number();
				index = findRecord(DB, number);
				if (index >= 0){
					tmp = getRecord(DB, index);
					setMarks(tmp);
					updateRecord(DB, index, tmp);
				} else {
					std::cout << "There are no any student with number " << number <<"\n";
				}
			   break;
		case 7: number = get_number();
				index = findRecord(DB, number);
				deleteRecord(DB, index);
			break;
		case 8: int tmp = sortMenu();
				switch(tmp){
				case 1: sort(DB, compByNumber);  break;
				case 2: sort(DB, compBySurname); break;
				case 3: sort(DB, compByMarks);   break;
				}
				std::cout << "Database sorted" << std::endl;
				break;
		}
	} while (action != 0);
	if (DB.data) {
		delete[] DB.data;
	}
	return 0;
}

