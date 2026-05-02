#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>

int main() {
	std::vector<int> v = {-3, 2, -5, -1, 6, 7, 0, -4, 5};
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

/*
	struct Comparator {
		bool operator() (int left, int right) const {
			return abs(left) < abs(right);
		}
	};
	Comparator x;
	std::cout << "x(5, 1) = " << x(5, 1) << std::endl;

	std::sort(v.begin(), v.end(), Comparator());
*/

	std::sort(v.begin(), v.end(),
			  [](int left, int right) {return abs(left) < abs(right);}
			);

    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

	struct Counter {
		int total;
		Counter() : total(0) {}
		void operator() (int element) { total += element; }
		operator int() { return total; }
	};
	int result = std::for_each(v.begin(), v.end(), Counter());
	std::cout << std::endl << "result = " << result << std::endl;

	int total = 0;
	std::for_each(v.begin(), v.end(), [&total](int elem) { total += elem; });
    std::cout << "total = " << total << std::endl;

    std::for_each(v.begin(), v.end(), [total](int &elem) { elem -= total; });
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    std::for_each(v.begin(), v.end(), [](int elem) {std::cout << elem <<"...";} );
    std::cout << std::endl;

	std::function<int(int,double)> mult = [](int x, double y) {return x*y;};
	std::cout << "mult(2, 3.1) = " << mult(2, 3.1) << std::endl;

    auto mult2 = [](int x, double y) {return x*y;};
    std::cout << "mult2(2, 3.1) = " << mult2(2, 3.1) << std::endl;

	auto add = [](int x, int y)->bool {return x + y;} ;
    std::cout << "add(2, 3) = " << add(2, 3) << std::endl;

	auto foo = [](int x, double y)->double {if (x<0) return x; else return y;};
	std::cout << foo(2, 5.3) << std::endl;

/*
	[объявления лямбда выражения](список аргументов)->возвращаемый_тип {тело лямбда выражения;}

	int total, factor, x;

	[&total, factor] - передаем factor по значению, передаем total по ссылке
	[total, &factor, x] - передаем total и x по значению, factor - по ссылке
	[&, factor] - передаем все переменные кроме factor по ссылке, factor - по значению
	[=, &total] - передаем все переменные кроме total по значению, total - по ссылке
	[=] - передаем все переменные по значению
	[&] - передаем все переменные по ссылке
*/

	return 0;
}
