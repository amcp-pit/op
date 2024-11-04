#include <iostream>
#include <time.h>
#include <cmath>

int main()
{
	srand( (unsigned int)time(NULL) );

	int marks[] = {2,3,4,2,3,4,4,5,5,4,3,5,3,2,4,5,4,3,5,3,5};
	int N = sizeof(marks)/sizeof(marks[0]);   // N = sizeof(marks)/sizeof(int)

	std::cout << "Marks: ";
	for (int i = 0; i < N; ++i) {
		std::cout << marks[i] << ' ';
	}
	std::cout << std::endl;


	for (int i = 0; i < N; ++i) {
		marks[i] = 2 + rand() % 4;
	}

	std::cout << "Marks: ";
	for (int i = 0; i < N; ++i) {
		std::cout << marks[i] << ' ';
	}
	std::cout << std::endl;

	double M = 0;
	for (int i = 0; i < N; ++i) {
		M += marks[i];
	}
	M /= N;
	std::cout << "Average: " << M << std::endl;;

	double D = 0;
	for (int i = 0; i < N; ++i) {
		D += (marks[i] - M) * (marks[i] - M);
	}
	D /= N;
	D = sqrt(D);
	std::cout << "Deviation: " << D << std::endl;;

/*
// Инициализация массивов
int M1[5] = {4, 3, 6, 7, 2};
int M2[5] = {4, 3, 6, 7, 2, 6}; // error
int M3[5] = {4, 3, 6}; // {4, 3, 6, 0, 0, 0}
int M0[];  // error
int M4[] = {1,2,3,4,5,6,7,8}; // int M4[8] = {1,2,3,4,5,6,7,8};

char str1[]="Hello";
char str2[]={'H','e','l','l','o',0};

char str3[]={'H','e','l','l','o'};
*/
	return 0;
}

