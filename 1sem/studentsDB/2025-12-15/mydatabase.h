#pragma once

#include "student.h"
#include <fstream>

struct Database;
struct Index;

Database* createDB();
void deleteDB(Database* & DB);
void destructor(Database* DB);

bool eodb(Index * index);

int addRecord(Database* DB, const student& x);
void printDB(const Database * DB);
bool saveDB(const Database* DB, const char filename[]);
bool openDB(Database* DB, const char filename[]);
bool exportDB(const Database* DB, const char filename[]);
Index* findRecord(const Database* DB, int what);
void updateRecord(Database* DB, Index* index, const student &x);
student getRecord(const Database* DB, Index* index);
void deleteRecord(Database* DB, Index* index);
void sort(Database* DB, bool (*comparator) (const student&, const student&));

