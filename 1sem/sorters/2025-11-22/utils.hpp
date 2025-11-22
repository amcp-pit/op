#pragma once

#include <utility>
#include <iostream>

void random(int * A, std::size_t size, int a = 0, int b=1000);
void sortedArray(int * A, size_t size);
void reversedArray(int * A, size_t size);
void constArray(int * A, size_t size);
void quickSortKiller(int * A, size_t size);

bool isSorted(int * A, std::size_t size);

template <typename T>
void printArray(T * A, std::size_t size, const char * pref)
{
    std::cout << pref;
    for(std::size_t i=0; i<size; ++i) {
        std::cout <<A[i] << " ";
    }
    std::cout << std::endl;
}


