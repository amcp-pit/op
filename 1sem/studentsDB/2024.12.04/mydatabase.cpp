#include "mydatabase.h"
#include <fstream>

int addRecord(DataBase& DB, const student& X) {
	if (DB.count >= DB.maxsize) {
		DB.maxsize = 2 * DB.maxsize + 1; 
		student* tmp = new student[DB.maxsize];
		for (int i = 0; i < DB.count; ++i) {
			tmp[i] = DB.data[i];
		}
		if (DB.data) {
			delete[] DB.data;
		}
		DB.data = tmp;
	}
	DB.data[DB.count] = X;
	++DB.count;
	return DB.count;
}

void printDB(const DataBase& DB) {
	for (int i = 0; i < DB.count; ++i) {
		std::cout << DB.data[i] << std::endl;
	}
}

void saveDB(const DataBase& DB, const char filename[]) {
	std::ofstream outFile(filename, std::ios_base::binary);
	if (!outFile.is_open()) {
		std::cout << "Can not open file '" << filename << "'\n";
		return;
	}
	outFile.write( (const char*)&(DB.count), sizeof(DB.count));
	outFile.write( (const char*)DB.data, sizeof(student)*DB.count );
	outFile.close();
}

void openDB(DataBase& DB, const char filename[]) {
	std::ifstream inFile(filename, std::ios_base::binary);
	if (!inFile.is_open()) {
		std::cout << "Can not open file '" << filename << "'\n";
		return;
	}
	int count;
	inFile.read( (char *)&count, sizeof(count));
	if (DB.data)
		delete[] DB.data;
	if (count > 0) {
		DB.data = new student[count];
		DB.count = count;
		DB.maxsize = count;
		inFile.read((char*)DB.data, sizeof(student) * count);
	} else {
		DB.data = nullptr;
		DB.count = DB.maxsize = 0;
	}
	inFile.close();
	return;
}

void exportDB(const DataBase& DB, const char filename[]) {
	std::ofstream outFile(filename);
	if (!outFile.is_open()) {
		std::cout << "Can not open file '" << filename << "'\n";
		return;
	}
	for (int i = 0; i < DB.count; ++i) {
		outFile << DB.data[i] << std::endl;
	}
	outFile.close();
}

int findRecord(const DataBase& DB, int what){
	for(int i=0; i < DB.count; ++i){
		if (DB.data[i].number == what)
			return i;
	}
	return -1;
}

void updateRecord(DataBase& DB, int index, const student& X){
	if (index>=0 && index<DB.count){
		DB.data[index] = X;
	}
}

student getRecord(DataBase& DB, int index){
	student tmp;
	if (index>=0 && index<DB.count){
		tmp = DB.data[index];
	}
	return tmp;
}

void deleteRecord(DataBase& DB, int index){
	if ( index>=0 && index<DB.count){
		std::cout << "Are you sure? (Y/N)";
		char ch[128];
		std::cin.get(ch, 128);
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (ch[0]=='Y' || ch[0]=='y') {
			DB.data[index] = DB.data[DB.count-1];
			--DB.count;
		}
	}
}

void sort(DataBase& DB, bool (*comparator)(const student&, const student&)){
	if (DB.count > 1){
		sort(DB.data, DB.count, comparator);
	}
}