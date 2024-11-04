/*
	Вычисление суммы ряда с заданной точностью ε.
           ---                       2n+1
	       \                    n   x
    S(x)=  /   an, где an = (-1) -------
           ----                  (2n+1)!
            n=0
          |an|>ε
*/

#include <iostream>
#include <cmath>

int main()
{
	const double  eps = 1e-12; // Заданная точность вычисления

	double x;
	std::cout << "Input x: ";
	std::cin >> x;

	double S = 0.0;
	double an = x;
	int n = 1;

	while (an <= -eps || an >= eps) {
		S += an;
		an *= -x*x/(2*n*(2*n+1)); 
		++n;
	}

	std::cout << "S = " << S << std::endl;
	std::cout << "Total: " << n << " steps" << std::endl;
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