#include <iostream>

int main() {
	// Коэффициенты полинома
	double a[] = {1.0, -2.0, 3.0, 4.0, 0.0, -1.0, 5.0, -8.0};
	int n = sizeof(a)/sizeof(a[0]);
	std::cout << "n = " << n <<std::endl;

	double x0 = 1.0;
	// Вычисление значение полинома в точке x = x0.
	double f = a[0];
	for(int i=1; i<n ; ++i){
		f = f*x0 + a[i];
	}
	std::cout << "f(" << x0 << ") = " << f <<std::endl;
	return 0;
}
