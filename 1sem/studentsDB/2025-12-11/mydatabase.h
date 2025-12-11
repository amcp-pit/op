#pragma once

#include "student.h"
#include <fstream>

struct Database;

Database* createDB();
void deleteDB(Database* & DB);
void destructor(Database* DB);

int addRecord(Database* DB, const student& x);
void printDB(const Database * DB);
bool saveDB(const Database* DB, const char filename[]);
bool openDB(Database* DB, const char filename[]);
bool exportDB(const Database* DB, const char filename[]);
int findRecord(const Database* DB, int what);
void updateRecord(Database* DB, int index, const student &x);
student getRecord(const Database* DB, int index);
void deleteRecord(Database* DB, int index);
void sort(Database* DB, bool (*comparator) (const student&, const student&));

