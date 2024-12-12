#include "student.h"

std::ostream& operator<< (std::ostream& out, const student& X) {
	out << "st" << X.number << ". "
		<< X.surname << " "
		<< X.name << ":";
	for (int i = 0; i < marks_count; ++i) {
		out << " " << static_cast<int>(X.marks[i]);
	}
	return out;
}

std::istream& operator>> (std::istream& in, student& X) {
	std::cout << "Student number: ";
	in >> X.number;
	in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Surname: ";
	in.getline(X.surname, 32);
	std::cout << "Name: ";
	in.getline(X.name, 16);
	for (int i = 0; i < marks_count; ++i) X.marks[i] = 0;
	return in;
}

void setMarks(student& X){
	std::cout<< "Input "<< marks_count << " marks for student "
			 << X.surname << " " << X.name <<": ";
	int tmp;
	for(int i=0; i<marks_count; ++i){
		std::cin >> tmp;
		X.marks[i] = (tmp<0)? -tmp : tmp;
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool compByNumber(const student& left, const student& right){
	return left.number < right.number;
}

bool compBySurname(const student& left, const student& right){
	int result = strcmp(left.surname, right.surname);
	if (result < 0)
		return true;
	if (result==0)
		return strcmp(left.name, right.name) < 0;
	return false;
}

inline double marksAverage(const unsigned char *marks, int size){
	int cnt = 0;
	double result = 0;
	for(int i=0; i<size; ++i){
		if (marks[i]>0){
			result += marks[i];
			++cnt;
		}
	}
	return (cnt>0) ? result/double(cnt) : 0;
}

bool compByMarks(const student& left, const student& right){
	return marksAverage(left.marks, marks_count) > marksAverage(right.marks, marks_count);
}

void sort(student* M, int size, bool (*comparator)(const student&, const student&) ){
	for(int i=0; i<size; ++i){
		int k = i;
		for(int j=i+1; j<size; ++j){
			if (comparator(M[j], M[k])){
				k = j;
			}
		}
		if (i<k){
			std::swap(M[i], M[k]);
		}
	}
}