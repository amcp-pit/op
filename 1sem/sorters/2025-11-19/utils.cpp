#include "utils.hpp"
#include <iostream>

void random(int * A, size_t size, int a, int b)
{
    if (b < a) {
        std::swap(a, b);
    }
    int width = (b==a) ? 1 : (b - a);
    for(size_t i = 0; i < size; ++i) {
        A[i] = rand()%width + a;
    }
}

void sortedArray(int * A, size_t size)
{
	for(size_t i=0; i < size; ++i){
		A[i] = i + 1;
	}
}

void reversedArray(int * A, size_t size)
{
    for(size_t i = 0; i < size; ++i){
        A[i] = size - i;
    }
}

void constArray(int * A, size_t size)
{
    for(size_t i = 0; i < size; ++i){
        A[i] = 42;
    }
}


bool isSorted(int * A, size_t size)
{
    for(size_t i = 1; i < size; ++i){
        if (A[i] < A[i-1]) return false;
    }
    return true;
}
