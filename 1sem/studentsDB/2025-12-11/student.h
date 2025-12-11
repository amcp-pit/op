#ifndef __STUDENT_2025__
#define __STUDENT_2025__

#include <iostream>
const int marks_count = 5;

struct student {
	int number;
	char surname[32];
	char name[16];
	unsigned char marks[marks_count];
};

std::ostream & operator << (std::ostream & out, const student& x);
std::istream & operator >> (std::istream & in, student& x);
void setMarks(student & x);

bool compByNumber(const student& left, const student& right);
bool compBySurname(const student& left, const student& right);
bool compByMarks(const student& left, const student& right);

void sort(student* M, int size, bool (*comparator) (const student&, const student&));

#endif

