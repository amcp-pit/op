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




#endif

