#pragma once
#include "student.h"
struct DataBase {
	int count;
	int maxsize;
	student* data;
};

int addRecord(DataBase& DB, const student& X);
void printDB(const DataBase& DB);
void saveDB(const DataBase& DB, const char filename[]);
void openDB(DataBase& DB, const char filename[]);
void exportDB(const DataBase& DB, const char filename[]);
int findRecord(const DataBase& DB, int what);
void updateRecord(DataBase& DB, int index, const student& X);
student getRecord(DataBase& DB, int index);
void deleteRecord(DataBase& DB, int index);
void sort(DataBase& DB, bool (*comparator)(const student&, const student&));