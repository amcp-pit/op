#include <iostream>

void print(const int *M, int size, const char str[]=""){
	std::cout << str;
	for(int i=0; i<size; ++i)
		std::cout << M[i]<<" ";
	std::cout << std::endl;
}

int main(){
	int n;
	std::cout << "Array size: ";
	std::cin >> n;
	if (n<1)
		return 0;
	int *M = new int[n];

	for(int i=0; i<n; ++i)
		M[i] = rand() % 100;


	for(int i=0; i<n; ++i)
		std::cout << M[i]<<" ";
	std::cout << std::endl;

	print(M, n, "M = ");
	if (n>=5)
		print(M, 5, "first 5 elements: ");

	if (n>=2)
		print(M+2, n-2, "M[2],.... = ");

	delete[] M;

	char str1[] = {'h', 'e', 'l', 'l', 'o',',',' ', 'w'};
	int size1 = sizeof(str1)/sizeof(str1[0]);
	std::cout <<"size1 = "<< size1 << std::endl;
	for(int i=0; i<size1; ++i)
		std::cout << str1[i];
	std::cout << std::endl;

	std::cout << str1 << std::endl; // Можно выйти за пределы str1
									// Вывод до ближайшего \0


    char str2[] = "hello";
    int size2 = sizeof(str2)/sizeof(str2[0]);
    std::cout <<"size2 = "<< size2 << std::endl;
    for(int i=0; i<size2; ++i)
        std::cout << str2[i];
    std::cout << std::endl;
    std::cout << str2 << std::endl;

	return 0;
}
