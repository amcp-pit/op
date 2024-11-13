#pragma once 

#include <iostream>
#include <utility>

template <typename T>
void bubbleSort(T* M, size_t size) {

#ifdef SORTSTAT
	unsigned long long count_less = 0;
	unsigned long long count_set = 0;
	clock_t ticktok = clock();
#endif

	for (size_t step = 1; step < size; ++step) {
		bool isSorted = true;
		for (size_t i = size - 1; i >= step; --i) {
#ifdef SORTSTAT
			++count_less;
#endif
			if (M[i] < M[i - 1]) {
				std::swap(M[i], M[i - 1]);
				isSorted = false;
#ifdef SORTSTAT
				count_set += 3;
#endif
			}
		}
		if (isSorted) break;
	}
#ifdef SORTSTAT	
	ticktok = clock() - ticktok;
	std::cout << "<" << count_less << ", =" << count_set
		<< ", tics: " << ticktok << std::endl;
#endif
}

template <typename T>
void chooseSort(T* M, size_t size) {
#ifdef SORTSTAT
	unsigned long long count_less = 0;
	unsigned long long count_set = 0;
	clock_t ticktok = clock();
#endif

	if (size == 0) return;
	for (int step = 0; step < size - 1; ++step) {
		size_t minimumIndex = step;
		for (size_t i = minimumIndex + 1; i < size; ++i) {
#ifdef SORTSTAT
			++count_less;
#endif
			if (M[i] < M[minimumIndex])
				minimumIndex = i;
		}
		if (step < minimumIndex) {
			std::swap(M[step], M[minimumIndex]);
#ifdef SORTSTAT
			count_set += 3;
#endif
		}
	}
#ifdef SORTSTAT	
	ticktok = clock() - ticktok;
	std::cout << "<" << count_less << ", =" << count_set
		<< ", tics: " << ticktok << std::endl;
#endif
}

template <typename T>
void insertSort(T* M, size_t size){
#ifdef SORTSTAT
	unsigned long long count_less = 0;
	unsigned long long count_set = 0;
	clock_t ticktok = clock();
#endif	
	for(size_t j=1; j<size; ++j){
		// j - номер вставляемого элемента
		T tmp = M[j];
#ifdef SORTSTAT
		++count_set;
#endif
		size_t i;
		for(i = j; i > 0; --i){
#ifdef SORTSTAT
			++count_less;
#endif
			if (tmp < M[i-1]){
				M[i] = M[i-1];
#ifdef SORTSTAT
				++count_set;
#endif
			} else break;
		}
		if (i!=j){
			M[i]= tmp;
#ifdef SORTSTAT
			++count_set;
#endif
		}
	}
#ifdef SORTSTAT	
	ticktok = clock() - ticktok;
	std::cout << "<" << count_less << ", =" << count_set
		<< ", tics: " << ticktok << std::endl;
#endif
}

void insertSortA(int *M, size_t size){
/*
	Необходимо внести изменения!
	Прежде чем добавлять вычисление статистики,
	надо сделать все индексы массива типа size_t.
*/	
	int tmp;
	for(int j = 1; j < size; ++j){
		// j - номер вставляемого элемента
		int left = 0, right = j; 
		int mid;
		do{
			mid = left + (right - left) / 2;
			if (M[j] < M[mid])
				right = mid - 1;
			else 
				left = mid + 1;
		} while (left < right);
		
		if (right >=0 ){
			if (M[j] < M[right])
				--right;
		}

		if (j > right+1){
			tmp = M[j];
			for(int i=j; i>right; --i){
				M[i] = M[i-1];
			}
			M[right+1] = tmp;
		}

	}
}