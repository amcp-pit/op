#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
using namespace std;

void print_lists(const list<int> &L1, const list<int> &L2){
	cout << "List 1: ";
	copy(L1.begin(), L1.end(), ostream_iterator<int>(cout, " "));
	cout << "\nList 2: ";
    copy(L2.begin(), L2.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
}

int main(){
	list<int> A, B;
	for(int i=0; i<10; ++i){
		A.push_back(i);
		B.push_front(i);
	}
	print_lists(A, B);
//	cout << "sizeof(A) = " << sizeof(A) << endl;
//	cout << "A.size() = " << A.size() << endl;

	B.splice(find(B.begin(), B.end(), 3), A, A.begin(), find(A.begin(), A.end(), 6));
    print_lists(A, B);

	B.splice(B.end(), A);
    print_lists(A, B);

	B.sort();
	A = B;
    print_lists(A, B);

}
