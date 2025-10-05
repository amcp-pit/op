/*
Динамическое выделение памяти для многомерных массивов.
Вектор Айлиффа (Iliffe vector).
Функции.
*/

#include <iostream>
#include <limits> // for std::numeric_limits

int get_int(const char * question);
int** matrix(int n, int m);
void random_matrix(int **A, int n, int m);
int** plus(int **A, int **B, int n, int m);
void print(int **A, int n, int m);
void free_matrix(int **A, int n);

int main() {
    int n = get_int("Number of rows");
    if (n < 1)
        return 1;

    int m = get_int("Number of columns");
    if (m < 1)
        return 1;

    int **A = matrix(n, m);
    int **B = matrix(n, m);
    random_matrix(A, n, m);
    random_matrix(B, n, m);
    int **C = plus(A, B, n, m); // C = A + B;
    print(A, n, m);
    print(B, n, m);
    print(C, n, m);
    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(C, n);

    return 0;
}

int get_int(const char * question){
    while (true) { // Будем считывать до тех пор, пока пользователь не введет число
        std::cout << question << ": ";
        int x{};
        std::cin >> x;

        if (!std::cin) {
            // Если извлечение не удалось
            std::cin.clear(); // Вернемся в нормальное состояние
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Уберем все символы из буфера до \n
            continue;
        }
        return x;
    }
}

int** matrix(int n, int m) {
    // Выделение памяти для матриц
    int ** A = new int* [n];
	// Здесь должна быть проверка: удалось ли выделить память.
	// Но пока вопрос, а что делать, если не удалось
    for (int i = 0; i < n; ++i)
        A[i] = new int[m];
	    // Здесь должна быть проверка: удалось ли выделить память.
    	// Но пока вопрос, а что делать, если не удалось
	return A;
}

void random_matrix(int **A, int n, int m){
    for(int i=0; i<n; ++i)
        for (int j = 0; j < m; ++j) {
            A[i][j] = rand() % 40 + 10;
        }
}

void print(int **A, int n, int m){
    // print matrix A
    std::cout << "ans = \n";
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
