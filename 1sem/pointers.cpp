#include <iostream>

int main() {
	double x = 23456789234.5;
	std::cout << "         x = " << x << std::endl;
	std::cout << " sizeof(x) = " << sizeof(x) << std::endl;

	double *px; // указатель на double
	px = &x;    // указатель на переменную x
	std::cout << "        px = " << px << std::endl;         // будет выведен адрес переменной x
	std::cout << "sizeof(px) = " << sizeof(px) << std::endl; // будет выведен размер переменной px
	std::cout << "       *px = " << *px << std::endl;        // будет выведено значение переменной x

	double y = 4.56;
	px = &y;    // теперь указатель показывает на переменную y
	std::cout << "        px = " << px << std::endl;         // будет выведен адрес переменной y
	std::cout << "       *px = " << *px << std::endl;        // будет выведено значение переменной y

	double **pp;
	pp = &px;   // указатель на переменную px
	std::cout << "        pp = " << pp << std::endl;         // будет выведен адрес переменной px
	std::cout << "sizeof(pp) = " << sizeof(pp) << std::endl; // будет выведен размер переменной pp
	std::cout << "       *pp = " << *pp << std::endl;        // будет выведено значение переменной px (а там сейчас записан адрес переменной y)
	std::cout << "      **pp = " << **pp << std::endl;       // будет выведено значение переменной y

	**pp = 1.0; // Изменится y, так как пошли по адресу, который записан в pp, а так как там был адрес px, то пришли к px. 
                // Пошли дальше по адресу, который записан там (а там был адрес y), пришли в y и записали туда 1. 
	std::cout << "         y = " << y << std::endl; // Поэтому выведется, что теперь y = 1.0

	*px = 2.0;
	std::cout << "         y = " << y << std::endl; // А теперь y = 2.0

	int *p;
	p = (int*)&x;   // в p запишем адрес переменной x, но будем считать, что это адрес переменной типа int, а не double
	std::cout << "        &x = " << &x << std::endl; 
	std::cout << "         p = " << p << std::endl;
	std::cout << "        *p = " << *p << std::endl; // увидим целое число, которое получается из половины бит, которые задают вещественное x

	unsigned char* c = (unsigned char *)&x;    // в c записшем адрес переменной x, но будем считать, что это адрес переменной типа unsigned char
	std::cout << "        *c = " << (int)*c << std::endl;
	++c;
	std::cout << "        *c = " << (int)*c << std::endl;
	++c;
	std::cout << "        *c = " << (int)*c << std::endl;
	++c;
	std::cout << "        *c = " << (int)*c<< std::endl;
	++c;
	std::cout << "        *c = " << (int)*c << std::endl;
	++c;
	std::cout << "        *c = " << (int)*c << std::endl;
	++c;
	std::cout << "        *c = " << (int)*c << std::endl;
	++c;
	std::cout << "        *c = " << (int)*c << std::endl; // В итоге вывели значение всех 8 байт, которые задают переменную x

	int M[] = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

	p = &(M[0]); // в p записали адрес первого элемента массива M
	std::cout << "         p = " << p << std::endl;
	std::cout << "        *p = " << *p << std::endl;
	std::cout << "        *p = " << *(p + 1) << std::endl; // увидим значение M[1], то есть 12
	std::cout << "        *p = " << *(p + 2) << std::endl; // увидим значение M[2], то есть 13
	std::cout << "        *p = " << *(p + 3) << std::endl; // увидим значение M[3], то есть 14
	std::cout << "        *p = " << *(p + 4) << std::endl; // увидим значение M[4], то есть 15

	/*
	M[i]    *(M+i)
	++p; // можно
	++M; // нельзя
	*/

	return 0;
}
