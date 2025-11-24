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


template <typename T>
void quickSort(T * M, size_t size){
	if (size < 2) return;
	
#ifdef SORTSTAT
    unsigned long long count_less = 0;
    unsigned long long count_set = 0;
    clock_t tictok = clock();
#endif

	size_t leftStack[64];
	size_t rightStack[64];
	size_t sizeStack = 0;

	// Положим на стек границы сортируемого диапазона
	leftStack[sizeStack] = 0;
	rightStack[sizeStack] = size - 1;
	++sizeStack;

	while(sizeStack > 0){
		--sizeStack;
		size_t from = leftStack[sizeStack];
		size_t to = rightStack[sizeStack];
		size_t left = from;
		size_t right = to;
		size_t pindex = from + rand() % (to - from);
		T p = M[pindex];
#ifdef SORTSTAT
        ++count_set;
#endif
#ifdef SORTSTAT
       count_less += to - from;
#endif
		while (left < right){
			while(M[left] < p) ++left;
			while(p < M[right]) --right;
			if (left < right){
				std::swap(M[left], M[right]);
#ifdef SORTSTAT
			     count_set += 3;
#endif
				 ++left;
				--right;
			} else if (left==right){
				++left;
				if (right > 0) --right;
			}
		}

		if ( (right - from) < (to-left) ){
			// Справа больше , чем слева
			if (left < to) {
				leftStack[sizeStack] = left;
				rightStack[sizeStack] = to;
				++sizeStack;
			}
			if (right > from) {
				leftStack[sizeStack] = from;
				rightStack[sizeStack] = right;
				++sizeStack;
			}
		} else {
			// Слева больше, чем справа
			if (right > from) {
				leftStack[sizeStack] = from;
				rightStack[sizeStack] = right;
				++sizeStack;
			}
			if (left < to) {
				leftStack[sizeStack] = left;
				rightStack[sizeStack] = to;
				++sizeStack;
			}
		}
	}
#ifdef SORTSTAT
    tictok = clock() - tictok;
    std::cout << " <" << count_less << ", =" << count_set
              << ", tics: " << tictok << std::endl;
#endif
}

template <typename T>
void _merge(T * M, size_t first, size_t middle, size_t last){
	size_t size = last - first + 1;
	T * tmp = new T[size];
	size_t indextmp = 0;
	size_t start1 = first, end1 = middle;
	size_t start2 = middle+1, end2 = last;
	while (start1<=end1 && start2<=end2){
		if (M[start1] < M[start2]){
			tmp[indextmp++] = M[start1++];
		} else {
			tmp[indextmp++] = M[start2++];
		}
	}
	while(start1<=end1) {tmp[indextmp++] = M[start1++];}
	while(start2<=end2) {tmp[indextmp++] = M[start2++];}

	// Копируем обратно из tmp в M
	indextmp = 0;
	while (first <=last) {M[first++] = tmp[indextmp++];}
	delete[] tmp;
}

template <typename T>
void _split(T * M, size_t  from, size_t to){
    if (from < to){
        size_t middle = from + (to - from) / 2;
        _split(M, from, middle);
        _split(M, middle+1, to);
        _merge(M, from, middle, to);
    }
}

template <typename T>
void mergeSort(T * M, size_t size){
#ifdef SORTSTAT
    clock_t tictok = clock();
#endif

	_split(M, 0, size - 1);

#ifdef SORTSTAT
    tictok = clock() - tictok;
    std::cout << " tics: " << tictok << std::endl;
#endif

}


#endif

