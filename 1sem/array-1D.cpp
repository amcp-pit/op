#include <iostream>

int main() {

/*
    // Инициализация массивов
    int M0[6]; // OK
    int M0[];  // error
    int M1[5] = {4, 3, 6, 7, 2};
    int M2[5] = {4, 3, 6, 7, 2, 6}; // error
    int M3[5] = {4, 3, 6}; // {4, 3, 6, 0, 0, 0}
    int M4[] = {1,2,3,4,5,6,7,8}; // int M4[8] = {1,2,3,4,5,6,7,8};
    const int n = 6;
    double a[n] = {1.0, -2.0, 3.0, 4.0, 0.0, -1.0};
*/

	int M[] = {1, 2, 3, 4, 5, 6, 7};
	int n = sizeof(M) / sizeof(M[0]);

	int * p = &(M[0]);
    std::cout << "M = " << M << std::endl;
    std::cout << "p = " << p << std::endl;

	for (int i=0; i<n; ++i){
		std::cout << p[i] << " ";
	}
	std::cout << std::endl;

    p = &(M[0]);
    for (int i=0; i<n; ++i){
        std::cout << *(p+i) << " ";
    }
    std::cout << std::endl;

    p = &(M[0]);
    for (int i=0; i<n; ++i){
        std::cout << *p << " ";
        ++p;
    }
    std::cout << std::endl;

	return 0;
}
