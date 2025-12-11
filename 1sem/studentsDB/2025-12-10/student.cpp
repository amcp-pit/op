#include <limits>
#include <cstring>
#include "student.h"

std::ostream & operator << (std::ostream & out, const student& x){
	out << "st" << x.number <<", "
		<< x.surname <<" "
		<< x.name <<": ";
	for(int i=0; i< marks_count; ++i){
		out << static_cast<int>(x.marks[i]) <<" ";
	}
	return out;
}

std::istream & operator >> (std::istream & in, student& x){
	std::cout << "Student number: ";
	in >> x.number;
	in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Surname: ";
	in.getline(x.surname, 32);
	std::cout << "Name: ";
	in.getline(x.name, 16);
	for(int i=0; i<marks_count; ++i) x.marks[i] = 0;
	return in;
}

void setMarks(student & x){
	std::cout << "Input " << marks_count << " marks for "
		      << x.surname <<" " << x.name<<": ";
	int tmp;
	for(int i=0; i<marks_count; ++i){
		std::cin >> tmp;
		x.marks[i] = (tmp<0)? -tmp : tmp;
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool compByNumber(const student& left, const student& right){
	return left.number < right.number;
}

bool compBySurname(const student& left, const student& right){
	return strcmp(left.surname, right.surname) < 0;
}

double marksAverage(const unsigned char marks[], int size){
	int cnt = 0;
	double result = 0;
	for(int i=0; i<size; ++i){
		if (marks[i] != 0){
			result += static_cast<double>(marks[i]);
			++cnt;
		}
	}
	return (cnt>0) ? result / cnt : 0;
}

bool compByMarks(const student& left, const student& right){
	return marksAverage(left.marks, marks_count) > marksAverage(right.marks, marks_count);
}

void sort(student* M, int size, bool (*comparator) (const student&, const student&)){
	for(int i = 0; i < size; ++i){
		int k = i;
		for(int j = i+1; j < size; ++j){
			if (comparator(M[j], M[k])) {
				k = j;
			}
		}
		if (i!=k){
			std::swap(M[i], M[k]);
		}
	}
}
