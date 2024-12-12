#pragma once
#include <iostream>

const int marks_count = 5;

struct student {
	int number;
	char surname[32];
	char name[16];
	unsigned char marks[marks_count];
};

std::ostream& operator<< (std::ostream& out, const student& X);
std::istream& operator>> (std::istream& in, student& X);
void setMarks(student& X);

bool compByNumber(const student& left, const student& right);
bool compBySurname(const student& left, const student& right);
bool compByMarks(const student& left, const student& right);

void sort(student* M, int n, bool (*comparator)(const student&, const student&) );