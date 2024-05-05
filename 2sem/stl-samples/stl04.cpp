#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>

using namespace std;

int main(){
	vector<int> v;
	for(int i=0; i<10; ++i)
		v.push_back(rand()%10-5);
	copy(v.begin(), v.end(), ostream_iterator<int>(cout," "));
	cout<<endl;
	
	/*
	int x=10;
	struct Comparator{
		int thex;
		Comparator():thex(0){}
		bool operator() (int left, int right) {
			// return left+thex < right;
			++thex;
			return abs(left)<abs(right);
		}
	};
	Comparator comparator;
	sort(v.begin(), v.end(), comparator);
	
	std::cout<< comparator.thex <<std::endl;
	*/

	int counter=0;
	sort(v.begin(), v.end(), 
		[&counter](int left, int right){
			++counter;
			return abs(left)<abs(right);
		});
	std::cout << counter << std::endl;
	copy(v.begin(), v.end(), ostream_iterator<int>(cout," "));
	cout<<endl;

	struct CounterPositive{
		int total;
		int poscnt;
		CounterPositive(): total(0), poscnt(0) {}
		void operator() (int elem) {
			total += elem; 
			if (elem>0) ++poscnt;
		}
		operator int(){ return poscnt; }
	};

	int result = for_each(v.begin(), v.end(), CounterPositive());
	cout << result <<std::endl;

	int total=0;
	int poscnt=0;
	for_each(v.begin(), v.end(), 
		     [&total, &poscnt](int elem){
				 total += elem; 
				 if (elem>0) ++poscnt;
	         });
	cout << total<<", " << poscnt <<std::endl;
	for_each(v.begin(), v.end(), [&total](int elem){total -= elem;});
	cout << total<<std::endl;

	for_each(v.begin(), v.end(), [](int elem){cout<<elem<<"...";});

	std::function<int(int,int)> mult = [](int x, int y) {return x*y;}; 
	cout<<"\n"<< mult(2, 3)<<endl;
	
	auto add = [](int x, int y)->bool {return x+y;};
	cout<<"\n"<< add(2, 3)<<endl;

	return 0;
}