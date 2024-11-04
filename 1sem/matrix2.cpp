#include <iostream>

int** matrix(int n, int m);
void random_matrix(int **A, int n, int m);
int** plus(int**A, int**B, int n, int m);
void print(int **C, int n, int m);
void free_matrix(int **A, int n);

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

    int **A = matrix(n,m);
    int **B = matrix(n,m);
    random_matrix(A,n,m);
    random_matrix(B,n,m);
    int **C = plus(A,B,n,m); // C = A + B;
    print(A,n,m);
    print(B,n,m);
    print(C,n,m);
    free_matrix(A,n);
    free_matrix(B,n);
    free_matrix(C,n);

    return 0;
}


int** matrix(int n, int m) {
    // Выделение памяти для матриц
    int ** A = new int* [n]; 
    for (int i = 0; i < n; ++i) 
        A[i] = new int[m];
	return A;
}

void random_matrix(int **A, int n, int m){
    for(int i=0; i<n; ++i)
        for (int j = 0; j < m; ++j) {
            A[i][j] = rand() % 40 + 10;
        }
}
   
void print(int **C, int n, int m){
    // print matrix A
    std::cout << " = \n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cout << A[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}    

int** plus(int**A, int**B, int n, int m){
    // C = A + B
    int **C = matrix(n,m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
	return C;
}

void free_matrix(int **A, int n){
    // Free memory
    for (int i = 0; i < n; ++i) 
        delete[] A[i];
    delete[] A;
}
