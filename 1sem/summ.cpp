/*
	Вычисление суммы ряда.
            n
           ---                       2k+1
	       \                    k   x
    S(x)=  /   an, где an = (-1) -------
           ----                  (2k+1)!
            k=0
*/

#include <iostream>
#include <cmath>

int main()
{

	double x;
	std::cout << "Input x: ";
	std::cin >> x;

	int n;
	do {
		std::cout << "Input positive n = ";
		std::cin  >> n;
	} while(n<1);
	double S = 0.0;
	double ak = x;

/*
	int k = 1;
	do{
		S += ak; // S = S + ak;
		ak *= (-x * x / 2 / k / (2*k+1));
		++k; // k += 1; // k = k + 1;
	}while(k < n);
*/
	for(int k = 1; k <= n; ++k){
		S += ak;
		ak *= (-x * x / (2. * k * (2.*k+1.)));
	}

	std::cout << "S = " << S << std::endl;
	std::cout << "sin(x) = " << sin(x) << std::endl;
	return 0;
}

/*
// Цикл do...while
do
	команда
while (условие);

do{
	команда1;
	команда2;
	...
} while (условие);


// Цикл while

while (условие)
	команда;

while (условие){
	команда1;
	команда2;
	...
}

// Цикл for

for(инициализация; условие; действие в конце шага)
	команда;


for(инициализация; условие; действие в конце шага)
{
	команда1;
	команда2;
	...
}


// Бесконечный цикл
for(;;);
while(true);


//Следующие три цикла эквивалентны
while(условие)
	команда;

for(;условие;)
	команда;

for(;условие;команда);

*/
