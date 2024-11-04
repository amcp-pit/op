#include <iostream>

int main() {
    int n, m;
    std::cout << "Number of rows: ";
    std::cin >> n;
    if (n < 1) 
        return 1;
    
    std::cout << "Number of columns: ";
    std::cin >> m;
    if (m < 1)
        return 1;
    
    int** A, ** B, ** C;
    // Выделение памяти для матриц
    A = new int* [n]; 
    for (int i = 0; i < n; ++i) 
        A[i] = new int[m];

    B = new int* [n]; 
    for (int i = 0; i < n; ++i) 
        B[i] = new int[m];

    C = new int* [n]; 
    for (int i = 0; i < n; ++i) 
        C[i] = new int[m];

    for(int i=0; i<n; ++i)
        for (int j = 0; j < m; ++j) {
            A[i][j] = rand() % 40 + 10;
            B[i][j] = rand() % 40 + 10;
        }
   
    // print matrix A
    std::cout << "A = \n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cout << A[i][j] << ' ';
        }
        std::cout << "\n";
    }
    
    // print matrix B
    std::cout << "B = \n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cout << B[i][j] << ' ';
        }
        std::cout << "\n";
    }
    
    // C=A + B
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    // print matrix C
    std::cout << "C = \n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cout << C[i][j] << ' ';
        }
        std::cout << "\n";
    }

    // Free memory
    for (int i = 0; i < n; ++i) 
        delete[] A[i];
    delete[] A;

    for (int i = 0; i < n; ++i) 
        delete[] B[i];
    delete[] B;

    for (int i = 0; i < n; ++i) 
        delete[] C[i];
    delete[] C;

    return 0;
}
