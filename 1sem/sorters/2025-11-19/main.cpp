#include <iostream>
#include <utility>
#include "utils.hpp"

#define SORTSTAT

#include "sorters.hpp"

void sortArray( void (*sorter)(int*, size_t),
				  int* M, size_t n,
				  const char* arrayName)
{
	std::cout << "---- Array: " << arrayName<< " ----\n";
	if (n < 20) printArray(M, n, "before:");
	sorter(M, n);
	if (n < 20) printArray(M, n, "after:");
	if (!isSorted(M, n)){
		std::cout << "ERROR: not sorted!" << std::endl;
	}
}

void tester( void (*sorter)(int*, size_t),
             size_t n, const int* randArray,
             const char * sorterName)
{
	std::cout << "\n=========== Method: " << sorterName << " ==================\n";
	int *A = new int[n];
	if (A == nullptr){
		std::cout <<" Out of memory\n";
		return;
	}
	sortedArray(A, n);
	sortArray(sorter, A, n, "sorted");

    constArray(A, n);
    sortArray(sorter, A, n, "const");

	reversedArray(A, n);
	sortArray(sorter, A, n, "reversed");

	for(size_t i=0; i<n; ++i) {
		A[i] = randArray[i];
	}
	sortArray(sorter, A, n, "random");
}


int main(){
	int N;
	std::cout << "Size of array: ";
	std::cin >> N;
	if (N < 1) {
		std::cout << "Size must be positive\n";
		return 1;
	}
	int *randArray = new int[N];
	if (randArray == nullptr){
		std::cout << "Out of memmory\n";
		return 2;
	}
	random(randArray, N);
	tester(bubbleSort, N, randArray, "BubbleSort");
    tester(chooseSort, N, randArray, "ChooseSort");

//    tester(quickSort, N, randArray, "QuickSort");

	delete[] randArray;
	return 0;
}
