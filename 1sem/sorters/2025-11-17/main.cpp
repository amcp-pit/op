#include <iostream>
#include <utility>
#include "utils.hpp"
#include "sorters.hpp"

int main(){
	const int N = 20;
	int *A = new int[N];
	random(A, N);
	printArray(A, N, "before = ");
	bubbleSort(A, N);
	if (!isSorted(A, N)){
		std::cout << "ERROR: not sorted." << std::endl;
	}
	printArray(A, N, "after sorting = ");
	delete[] A;
	return 0;
}
