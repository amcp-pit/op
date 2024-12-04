#include <iostream>
#include <ctime>

#define SORTSTAT
#include "sorters.h"

template <typename T>
void printArray(T* M, size_t size, const char* str) {
	std::cout << str;
	for (size_t i = 0; i < size; ++i) {
		std::cout << " " << M[i];
	}
	std::cout << std::endl;
}

void randomArray(int* M, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		M[i] = rand() % 9000 + 1000;
	}
}

void sortedArray(int* M, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		M[i] = i + 1;
	}
}

void reversedArray(int* M, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		M[i] = n - i;
	}
}

void constArray(int* M, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		M[i] = 1;
	}
}


void quickSortKiller(int* M, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		M[i] = i;
	}
	for (size_t i = 2; i < n; ++i) std::swap(M[i], M[i / 2]);
}


template <typename T>
bool isSorted(T* M, size_t n) {
	for (size_t i = 1; i < n; ++i) {
		if (M[i] < M[i - 1])
			return false;
	}
	return true;
}

void sortArray(void (*sorter)(int*, size_t),
	int* M, size_t n,
	const char* arrayname) {
	std::cout << "--- Array: " << arrayname << std::endl;
	if (n < 25) printArray(M, n, "Before:");
	sorter(M, n);
	if (n < 25) printArray(M, n, "After: ");
	if (!isSorted(M, n)) {
		std::cout << "ERROR: not sorted!" << std::endl;
	}
}

void tester(void (*sorter)(int*, size_t),
	size_t n,
	const int* randArray,
	const char* sorterName) {
	std::cout << "\n=========== Method: " << sorterName
		<< "===========\n";
	int* A = new int[n];
	if (A == nullptr) {
		std::cout << "Out of memory\n";
		return;
	}
	sortedArray(A, n);
	sortArray(sorter, A, n, "sorted");

	reversedArray(A, n);
	sortArray(sorter, A, n, "reversed");

	constArray(A, n);
	sortArray(sorter, A, n, "const");

	quickSortKiller(A, n);
	sortArray(sorter, A, n, "quickSortKiller");

	for (size_t i = 0; i < n; ++i)
		A[i] = randArray[i];
	sortArray(sorter, A, n, "random");

	delete[] A;
}


int main() {
	int n;
	std::cout << "Size of array: ";
	std::cin >> n;
	if (n < 1) {
		std::cout << "Size must be positive.\n";
		return 1;
	}
	int* randArray = new int[n];
	if (randArray == nullptr) {
		std::cout << "Out of memory\n";
		return 2;
	}
	randomArray(randArray, n); // Массив со случайными числами для тестирования

	tester(bubbleSort, n, randArray, "BubbleSort");
	tester(chooseSort, n, randArray, "ChooseSort");
	tester(insertSort, n, randArray, "InsertSort");
	tester(insertSortA, n, randArray, "InsertSort Advanced");
	tester(quickSort, n, randArray, "QuickSort");

	delete[] randArray;

	system("pause");
	return 0;
}