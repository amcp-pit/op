#ifndef _SORTERS_2025_
#define _SORTERS_2025_

template <typename T>
void bubbleSort(T *M, size_t n)
{
    for(size_t j = 0; j < n; ++j){
        bool isSorted = true;
        for(size_t i = n - 1; i > j; --i){
            if (M[i] < M[i-1]){
                std::swap(M[i], M[i-1]);
                isSorted = false;
            }
        }
        if (isSorted) break;
    }
}

#endif

