#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <functional>

using namespace std;

template <typename T>
void insert_elements(T& M, int first, int last){
	for(int i=first; i<=last; ++i)
		M.insert(M.end(), i);
}

template <typename T>
void print_elements(const T& M, const char* optstr=""){
	cout<< optstr;
	for(auto pos=M.begin(); pos!=M.end(); ++pos){
		cout<< ' '<< *pos; 
	}
	cout<<endl;
}

void print(int Element){
	cout<<"a"<<Element<<", ";
}

void add10(int & Element){
	Element += 10;
}

template <typename T>
class AddValue{
	T theValue;
public:
	AddValue(const T & v) : theValue(v) {}
	void operator()(T& Element) { Element += theValue++;}
};

class MeanValue{
	long sum, num;
public:
	MeanValue(): sum(0), num(0) {}
	void operator()(int Element) {sum+=Element; ++num;}
	operator double() {
		if (num==0) return 0;
		return static_cast<double>(sum)/static_cast<double>(num);
	}
};

bool isEven(int Element) { return (Element%2) == 0;}

bool absLess(int a, int b){
	return abs(a)<abs(b);
}

int main(){
	vector<int> A;
	insert_elements(A, 1, 9);
	copy(A.begin(), A.end(), ostream_iterator<int>(cout, " "));
	cout<<endl;
	print_elements(A, "One more time:");
	
	cout<< "And one more time: ";
	for_each(A.begin(), A.end(), print);
	cout<<endl;
	for_each(find(A.begin(), A.end(), 3), A.end(), print);
	cout<<endl;

	for_each(A.begin(), A.end(), add10);
	print_elements(A, "After add10:");

	for_each(A.begin(), A.end(), AddValue<int>(100));
	print_elements(A, "After AddValue<100>:");

	for_each(A.begin(), A.end(), AddValue<int>(-50));
	print_elements(A, "After AddValue<-50>:");

	for_each(A.begin(), A.end(), AddValue<int>( -*A.begin() ));
	print_elements(A, "After AddValue<???>:");

	double mv = for_each(A.begin(), A.end(), MeanValue());
	cout <<"Mean value: "<< mv <<endl;

	MeanValue MV;
	MV = for_each(A.begin(), A.end(), MV);
	cout <<"Mean value 2: "<< double(MV) <<endl;
	list<int> B;
	insert_elements(B, -20, -9);
	print_elements(B, "Container B:");
	MV = for_each(B.begin(), B.end(), MV);
	cout <<"Mean value A+B: "<< double(MV) <<endl;

	int num;
	num = count(A.begin(), A.end(), 4);
	cout <<"Number of elements equal to 4: "<< num <<endl;

	num = count_if(A.begin(), A.end(), isEven);
	cout <<"Number of elements with even value: "<< num <<endl;

	num = count_if(A.begin(), A.end(),  bind2nd(greater<int>(), 4)   );
	cout <<"Number of elements greater than 4: "<< num <<endl;

	insert_elements(A, -3, 5);
	print_elements(A, "A insert:");

	cout << "minimum A: "<< *min_element(A.begin(), A.end()) <<endl;
	cout << "maximum A: "<< *max_element(A.begin(), A.end()) <<endl;
	cout << "minimum |A|: "<< *min_element(A.begin(), A.end(), absLess) <<endl;
	
	transform(A.begin(), A.end(), // source range
			  A.begin(),          // destination range
			  negate<int>()
		);
	print_elements(A, "A after first transform:");

	list<int> C;
	transform(A.begin(), A.end(), // source range
			  front_inserter(C), // destination
			  bind2nd(multiplies<int>(), 10));
	print_elements(A, "A after transform (multiplies):");
	print_elements(C, "C after transform (multiplies):");

	transform(C.begin(), C.end(), 
		      ostream_iterator<int>(cout, "_"),
			  negate<int>());
	cout<<endl;

	return 0;
}