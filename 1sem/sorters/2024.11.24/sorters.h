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
void insertSort(T* M, size_t size) {
#ifdef SORTSTAT
	unsigned long long count_less = 0;
	unsigned long long count_set = 0;
	clock_t ticktok = clock();
#endif	
	for (size_t j = 1; j < size; ++j) {
		// j - номер вставляемого элемента
		T tmp = M[j];
#ifdef SORTSTAT
		++count_set;
#endif
		size_t i;
		for (i = j; i > 0; --i) {
#ifdef SORTSTAT
			++count_less;
#endif
			if (tmp < M[i - 1]) {
				M[i] = M[i - 1];
#ifdef SORTSTAT
				++count_set;
#endif
			}
			else break;
		}
		if (i != j) {
			M[i] = tmp;
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

template <typename T>
void insertSortA(T* M, size_t size) {
#ifdef SORTSTAT
	unsigned long long count_less = 0;
	unsigned long long count_set = 0;
	clock_t ticktok = clock();
#endif	
	T tmp;
	for (size_t j = 1; j < size; ++j) {
		// j - номер вставляемого элемента
		size_t left = 0, right = j;
		size_t mid;
		do {
			mid = left + (right - left) / 2;
#ifdef SORTSTAT
			++count_less;
#endif
			if (M[j] < M[mid])
				right = mid;
			else
				left = mid + 1;
		} while (left < right);

		if (j > right) {
			tmp = M[j];
#ifdef SORTSTAT
			++count_set;
#endif
			for (size_t i = j; i > right; --i) {
				M[i] = M[i - 1];
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
	ticktok = clock() - ticktok;
	std::cout << "<" << count_less << ", =" << count_set
		<< ", tics: " << ticktok << std::endl;
#endif

}

template <typename T>
void insertSortA_bad(T* M, size_t size) {
#ifdef SORTSTAT
	unsigned long long count_less = 0;
	unsigned long long count_set = 0;
	clock_t ticktok = clock();
#endif	
	T tmp;
	for (size_t j = 1; j < size; ++j) {
		// j - номер вставляемого элемента
		size_t left = 0, right = j;
		size_t mid;
		do {
			mid = left + (right - left) / 2;
#ifdef SORTSTAT
			++count_less;
#endif
			if (M[j] < M[mid])
				right = mid ? (mid - 1) : 0; // Запрещаем когда 0-1
			else
				left = mid + 1;
		} while (left < right);
		// Возможен случай, когда надо вставлять ПЕРЕД первым
		right += (M[j] < M[right]) ? 0 : 1;
#ifdef SORTSTAT
		++count_less;
#endif

		if (j > right) {
			tmp = M[j];
#ifdef SORTSTAT
			++count_set;
#endif
			for (size_t i = j; i > right; --i) {
				M[i] = M[i - 1];
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
	ticktok = clock() - ticktok;
	std::cout << "<" << count_less << ", =" << count_set
		<< ", tics: " << ticktok << std::endl;
#endif

}

template <typename T>
void quickSortS(T* M, size_t size) {
	if (size < 2) return;
#ifdef SORTSTAT
	unsigned long long count_less = 0;
	unsigned long long count_set = 0;
	clock_t ticktok = clock();
#endif	

	size_t leftStack[64];
	size_t rightStack[64];
	size_t sizeStack = 0;
	// Положим на стек сортируемый диапазон [0, size-1]
	leftStack[sizeStack] = 0;
	rightStack[sizeStack] = size - 1;
	++sizeStack;
	while (sizeStack > 0) {
		// Заберём значения левой и правой границ сортируемого диапазона
		--sizeStack;
		size_t from = leftStack[sizeStack];
		size_t to = rightStack[sizeStack];

		size_t left = from, right = to;
		size_t pindex = left + rand() % (right - left);
		//size_t pindex = left + (right-left)/2;
		T pivot = M[pindex];
#ifdef SORTSTAT
		++count_set;
		count_less += (right - left);
#endif
		while (left < right) {
			while (M[left] < pivot) { ++left; }
			while (pivot < M[right]) { --right; }
			if (left < right) {
				std::swap(M[left], M[right]);
#ifdef SORTSTAT
				count_set += 3;
#endif
				++left;
				--right;
			}
			else if (left == right) {
				++left;
				if (right > 0) --right;
			}
		}

		// Сначала на стек поместить больший диапазон
		// потом меньший диапазон
		if (right - from < to - left) {
			// Справа больше, чем слева
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
		}
		else {
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
		} // if (right-from < to-left)
	}// while(sizeStack > 0)
#ifdef SORTSTAT	
	ticktok = clock() - ticktok;
	std::cout << "<" << count_less << ", =" << count_set
		<< ", tics: " << ticktok << std::endl;
#endif
}

template <typename T>
void quickSort(T* M, size_t size) {
	if (size < 2) return;
	size_t left = 0, right = size - 1;
	// size_t pindex = left + (right - left) / 2;
	// size_t pindex = 0;
	size_t pindex = rand() % size;
	T p = M[pindex];
	while (left < right) {
		while (M[left] < p) { ++left; }
		while (p < M[right]) { --right; }
		if (left < right) {
			std::swap(M[left], M[right]);
			++left;
			--right;
		}
		else if (left == right) {
			++left;
			if (right > 0) --right;
		}
	}
	quickSort(M, right + 1);
	quickSort(M + left, size - left);
}

template <typename T>
void _merge(T* M, size_t first, size_t middle, size_t last) {
	size_t size = last - first + 1;
	T* tmp = new int[size];
	size_t indextmp = 0;
	size_t start1 = first, end1 = middle;
	size_t start2 = middle + 1, end2 = last;
	while (start1 <= end1 && start2 <= end2) {
		if (M[start1] < M[start2]) {
			tmp[indextmp++] = M[start1++];
		}
		else {
			tmp[indextmp++] = M[start2++];
		}
	}
	while (start1 <= end1) { tmp[indextmp++] = M[start1++]; }
	while (start2 <= end2) { tmp[indextmp++] = M[start2++]; }

	// Копируем обратно в M
	indextmp = 0;
	while (first <= last) { M[first++] = tmp[indextmp++]; }

	delete[] tmp;
}
template <typename T>
void _split(T* M, size_t first, size_t last) {
	if (first < last) {
		size_t middle = first + (last - first) / 2;
		_split(M, first, middle);
		_split(M, middle + 1, last);
		_merge(M, first, middle, last);
	}
}

template <typename T>
void mergeSort(T* M, size_t size) {
	if (size < 2) return;

#ifdef SORTSTAT
	clock_t ticktok = clock();
#endif	

	_split(M, 0, size - 1);

#ifdef SORTSTAT	
	ticktok = clock() - ticktok;
	std::cout << "tics: " << ticktok << std::endl;
#endif

}

template <typename T>
void mergeSortA(T* M, size_t size) {
	if (size < 2) return;
#ifdef SORTSTAT
	clock_t ticktok = clock();
#endif	
	T* tmp = new int[size];
	T* from = M;
	T* to = tmp;
	for (size_t step = 1; step < size; step *= 2) {
		size_t start1, end1, start2, end2;
		size_t indexto = 0;
		for (size_t start = 0; start < size; start += 2 * step) {
			start1 = start; end1 = start1 + step; end1 = end1 < size ? end1 : size;
			start2 = end1;  end2 = start2 + step;   end2 = end2 < size ? end2 : size;
			while (start1 < end1 && start2 < end2) {
				to[indexto++] = (from[start1] < from[start2]) ? from[start1++] : from[start2++];
			}
			while (start1 < end1) to[indexto++] = from[start1++];
			while (start2 < end2) to[indexto++] = from[start2++];
		}
		std::swap(from, to);
	}

	if (from != M) {
		size_t index = 0;
		while (index < size) {
			M[index] = tmp[index];
			++index;
		}
	}

	delete[] tmp;
#ifdef SORTSTAT	
	ticktok = clock() - ticktok;
	std::cout << "tics: " << ticktok << std::endl;
#endif
}

template <typename T>
void heapSort(T* M, size_t size) {
	if (size < 2) return;

#ifdef SORTSTAT
	unsigned long long count_less = 0;
	unsigned long long count_set = 0;
	clock_t ticktok = clock();
#endif	

	// make heap
	for (size_t i = 1; i < size; ++i) {
		size_t pos = i;
		while (pos != 0) {
			size_t parent = (pos - 1) / 2;
#ifdef SORTSTAT
			++count_less;
#endif
			if (M[parent] < M[pos]) {
				std::swap(M[parent], M[pos]);
#ifdef SORTSTAT
				count_set += 3;
#endif
				pos = parent;
			}
			else
				break;
		}
	}

	// shift down each element
	size_t N = size; // Кол-во элементов в пирамиде
	for (size_t i = 1; i < size; ++i) {
		--N;
		std::swap(M[N], M[0]);
#ifdef SORTSTAT
		count_set += 3;
#endif
		size_t pos = 0;
		size_t posMaxChild;
		while ((posMaxChild = 2 * pos + 1) < N) { // Пока есть элемент слева
			if (posMaxChild + 1 < N) { // Есть ещё кто-то справа
#ifdef SORTSTAT
				++count_less;
#endif
				if (M[posMaxChild] < M[posMaxChild + 1]) {
					++posMaxChild;
				}
			}
#ifdef SORTSTAT
			++count_less;
#endif
			if (M[pos] < M[posMaxChild]) {
				std::swap(M[pos], M[posMaxChild]);
#ifdef SORTSTAT
				count_set += 3;
#endif
				pos = posMaxChild;
			}
			else break;
		}
	}
#ifdef SORTSTAT	
	ticktok = clock() - ticktok;
	std::cout << "<" << count_less << ", =" << count_set
		<< ", tics: " << ticktok << std::endl;
#endif
}

template <typename T>
void shift_down(T* M, size_t size, size_t pos, 
				unsigned long long &count_less,
				unsigned long long &count_set) 
{
	size_t posMaxChild;
	while ((posMaxChild = 2 * pos + 1) < size) { // Пока есть элемент слева
		if (posMaxChild + 1 < size) { // Есть ещё кто-то справа
			++count_less;
			if (M[posMaxChild] < M[posMaxChild + 1]) {
				++posMaxChild;
			}
		}
		++count_less;
		if (M[pos] < M[posMaxChild]) {
			std::swap(M[pos], M[posMaxChild]);
			count_set += 3;
			pos = posMaxChild;
		}
		else break;
	}
}

template <typename T>
void heapSortA(T* M, size_t size) {
	if (size < 2) return;

	unsigned long long count_less = 0;
	unsigned long long count_set = 0;
#ifdef SORTSTAT
	clock_t ticktok = clock();
#endif	

	// make heap
	for (size_t i = size / 2; i > 0; --i) {
		shift_down(M, size, i-1, count_less, count_set);
	}

	// shift down each element
	size_t N = size; // Кол-во элементов в пирамиде
	for (size_t i = 1; i < size; ++i) {
		--N;
		std::swap(M[N], M[0]);
		count_set += 3;
		shift_down(M, N, 0, count_less, count_set);
	}

#ifdef SORTSTAT	
	ticktok = clock() - ticktok;
	std::cout << "<" << count_less << ", =" << count_set
		<< ", tics: " << ticktok << std::endl;
#endif
}