#pragma once
#include "student.h"

struct Node {
	student data;
	Node* next;
	Node* prev;
};

struct DataBase {
	int count;
	Node* begin;
	Node* end;
};

int addRecord(DataBase& DB, const student& X);
void deleteDB(DataBase& DB);
void printDB(const DataBase& DB);
void saveDB(const DataBase& DB, const char filename[]);
void openDB(DataBase& DB, const char filename[]);
void exportDB(const DataBase& DB, const char filename[]);
Node* findRecord(const DataBase& DB, int what);
void updateRecord(DataBase& DB, Node* index, const student& X);
student getRecord(DataBase& DB, Node* index);
void deleteRecord(DataBase& DB, Node* index);
void sort(DataBase& DB, bool (*comparator)(const student&, const student&));