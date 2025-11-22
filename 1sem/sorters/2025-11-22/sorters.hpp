#ifndef _SORTERS_2025_
#define _SORTERS_2025_
#include <ctime>

template <typename T>
void bubbleSort(T *M, size_t n)
{
#ifdef SORTSTAT
	unsigned long long count_less = 0;
	unsigned long long count_set = 0;
	clock_t tictok = clock();
#endif

    for(size_t j = 0; j < n; ++j){
        bool isSorted = true;
        for(size_t i = n - 1; i > j; --i){
#ifdef SORTSTAT
			++count_less;
#endif
            if (M[i] < M[i-1]){
                std::swap(M[i], M[i-1]);
#ifdef SORTSTAT
				count_set += 3;
#endif
                isSorted = false;
            }
        }
        if (isSorted) break;
    }

#ifdef SORTSTAT
	tictok = clock() - tictok;
	std::cout << " <" << count_less << ", =" << count_set
			  << ", tics: " << tictok << std::endl;
#endif
}

template <typename T>
void chooseSort(T *M, size_t n)
{
#ifdef SORTSTAT
    unsigned long long count_less = 0;
    unsigned long long count_set = 0;
    clock_t tictok = clock();
#endif

	for(size_t i = 0; i < n-1; ++i){
		size_t minindex = i;
		for(size_t j = minindex + 1; j < n; ++j){
#ifdef SORTSTAT
            ++count_less;
#endif
			if (M[j] < M[minindex]){
				minindex = j;
			}
		}
		if (minindex > i) {
			std::swap(M[i], M[minindex]);
#ifdef SORTSTAT
            count_set += 3;
#endif

		}
	}

#ifdef SORTSTAT
    tictok = clock() - tictok;
    std::cout << " <" << count_less << ", =" << count_set
              << ", tics: " << tictok << std::endl;
#endif
}

template <typename T>
void insertSort(T * M, size_t size){
#ifdef SORTSTAT
    unsigned long long count_less = 0;
    unsigned long long count_set = 0;
    clock_t tictok = clock();
#endif

	for(size_t j = 1; j < size; ++j){
		T tmp = M[j];
#ifdef SORTSTAT
        ++count_set;
#endif
		size_t i = j;
		for(; i > 0; --i){
#ifdef SORTSTAT
            ++count_less;
#endif
			if (tmp < M[i-1]) {
				M[i] = M[i-1];
#ifdef SORTSTAT
            ++count_set;
#endif
			} else {
				break;
			}
		}
		if (i != j){
			M[i] = tmp;
#ifdef SORTSTAT
    	    ++count_set;
#endif
		}
	}
#ifdef SORTSTAT
    tictok = clock() - tictok;
    std::cout << " <" << count_less << ", =" << count_set
              << ", tics: " << tictok << std::endl;
#endif
}

template <typename T>
void insertSortA(T * M, size_t size){
#ifdef SORTSTAT
    unsigned long long count_less = 0;
    unsigned long long count_set = 0;
    clock_t tictok = clock();
#endif

	for(size_t j = 1; j < size; ++j){
		size_t left = 0;
		size_t right = j;
		size_t mid;
		do{
			mid = left + (right - left) / 2;
#ifdef SORTSTAT
            ++count_less;
#endif
			if (M[j] < M[mid])
				right = mid;
			else
				left = mid + 1;
		} while(left < right);
		if (j > right){
			T tmp = M[j];
#ifdef SORTSTAT
            ++count_set;
#endif
			for(size_t i = j; i > right; --i){
				M[i] = M[i-1];
#ifdef SORTSTAT
      		    ++count_set;
#endif
			}
			M[right] = tmp;
#ifdef SORTSTAT
            ++count_set;
#endif
		}
	}
#ifdef SORTSTAT
    tictok = clock() - tictok;
    std::cout << " <" << count_less << ", =" << count_set
              << ", tics: " << tictok << std::endl;
#endif
}


template <typename T>
void quickSortR(T * M, size_t size){
	if (size < 2) return;
	size_t left = 0, right = size - 1;
	// size_t pindex = left + (right - left)/2;
	size_t pindex = rand() % size;
	T p = M[pindex];
	while (left < right){
		while(M[left] < p) ++left;
		while(p < M[right]) --right;
		if (left < right){
			std::swap(M[left], M[right]);
			++left;
			--right;
		} else if (left==right){
			++left;
			if (right > 0) --right;
		}
	}
	quickSortR(M, right + 1);
	quickSortR(M + left, size - left);
}


#endif

