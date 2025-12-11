#include "mydatabase.h"

int addRecord(Database& DB, const student& x){
	if (DB.count >= DB.maxsize) {
		// Добавляем место в DB.data
		DB.maxsize = (DB.count==0) ? 1 : 2 * DB.count;
		student * tmp = new student[DB.maxsize];
		for(int i=0; i< DB.count; ++i) tmp[i] = DB.data[i];
		delete[] DB.data;
		DB.data = tmp;
	}
	DB.data[DB.count] = x;
	++DB.count;
	return DB.count;
}

void printDB(const Database & DB) {
	for(int i=0; i<DB.count; ++i)
		std::cout << DB.data[i] <<std::endl;
}

bool saveDB(const Database& DB, const char filename[]){
	std::ofstream outFile(filename, std::ios_base::binary);
	if (!outFile) return false;
	outFile.write((const char *)&(DB.count), sizeof(DB.count));
	outFile.write((const char *)DB.data, DB.count * sizeof(DB.data[0]));
	outFile.close();
	return true;
}

bool openDB(Database& DB, const char filename[]){
	std::ifstream inFile(filename, std::ios_base::binary);
	if (!inFile) return false;
	int count ;
	inFile.read((char *)&count, sizeof(count));
	if (DB.data)
		delete[] DB.data;

	if (count > 0){
		DB.data = new student[count];
		DB.count = count;
		DB.maxsize = count;
		inFile.read((char *)DB.data, count * sizeof(DB.data[0]));
	} else {
		DB.data = nullptr;
		DB.maxsize = DB.count = 0;
	}
	inFile.close();
	return true;
}

bool exportDB(const Database& DB, const char filename[]){
	std::ofstream outFile(filename);
	if (!outFile) return false;
	for(int i = 0; i < DB.count; ++i){
		outFile << DB.data[i] <<std::endl;
	}
	outFile.close();
	return true;
}

int findRecord(const Database& DB, int what){
	for(int i=0; i < DB.count; ++i){
		if (DB.data[i].number == what)
			return i;
	}
	return -1;
}

void updateRecord(Database& DB, int index, const student &x){
	if (index >= 0 && index < DB.count)
		DB.data[index] = x;
}

student getRecord(const Database& DB, int index){
	student tmp = {0};
	if (index >= 0 && index < DB.count)
		tmp = DB.data[index];
	return tmp;
}

void deleteRecord(Database& DB, int index){
	if (index >= 0 && index < DB.count){
		DB.data[index] = DB.data[DB.count-1];
		--DB.count;
	}
}

void sort(Database& DB, bool (*comparator) (const student&, const student&)){
	if (DB.count > 1){
		sort(DB.data, DB.count, comparator);
	}
}
