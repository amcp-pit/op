#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

using namespace std;

template <typename T> void insert_elements(T &M, int first, int last) {
  for (int i = first; i <= last; ++i) {
    M.insert(M.end(), i);
  }
}

template <typename T> void print_elements(const T &M, const char *optstr = "") {
  cout << optstr;
  for (auto pos = M.begin(); pos != M.end(); ++pos) {
    cout << ' ' << *pos;
  }
  cout << endl;
}

void print(int Element) { cout << "x" << Element << ", "; }

void square(int & Element) { Element *= Element; }

void add10(int & Element) { Element += 10; }

template <typename T> class AddValue {
  T theValue;
public:
  AddValue(const T & value) : theValue(value) {}
  void operator()(T &element) { element += theValue++; }
};

class MeanValue {
  long sum, num;
public:
  MeanValue() : sum(0), num(0) {}
  void operator()(int Element) {
    sum += Element;
    ++num;
  }
  operator double() {
    if (num == 0)
      return 0;
    return static_cast<double>(sum) / static_cast<double>(num);
  }
};

bool isEven(int Element) { return (Element % 2) == 0; }

int main() {
  vector<int> A;
  insert_elements(A, 1, 15);
  print_elements(A, "A = ");
  copy(A.begin(), A.end(), ostream_iterator<int>(cout, " "));
  cout << endl;

  cout << "One more time: ";
  for_each(A.begin(), A.end(), print);
  cout << endl;
  cout << "reversed: ";
  for_each(A.rbegin(), A.rend(), print);
  cout << endl;

  for_each(A.begin(), A.end(), add10);
  print_elements(A, "A = ");

  for_each(A.begin(), A.end(), AddValue<int>(10));
  print_elements(A, "A = ");

  for_each(A.begin(), A.end(), AddValue<int>(-10));
  print_elements(A, "A = ");

  for_each(A.begin(), A.end(), AddValue<int>(-*A.begin()));
  print_elements(A, "after AddValue<int>(-*A.begin()) = ");

  MeanValue MV;
  MV = for_each(A.begin(), A.end(), MV);
  cout << "Mean value: " << double(MV) << endl;
  cout << "Mean value: " << MV << endl;

  list<int> B;
  insert_elements(B, -20, 3);
  print_elements(B, "Container B: ");

  MV = for_each(B.begin(), B.end(), MV);
  cout << "Mean value A+B: " << double(MV) << endl;

  MV = for_each(B.begin(), B.end(), MeanValue());
  cout << "Mean value B: " << double(MV) << endl;

  A[7] = 4;
  A[10] = 4;
  int num = count(A.begin(), A.end(), 4);
  print_elements(A, "Container A: ");
  cout << "Number of elements equal to 4: " << num << endl;

  num = count_if(A.begin(), A.end(), isEven);
  cout << "Number of elements with even value: " << num << endl;

  num = count_if(A.begin(), A.end(), bind2nd(greater<int>(), 4));
  cout << "Number of elements greate then 4: " << num << endl;

  insert_elements(A, -3, 5);
  print_elements(A, "Container A: ");

  transform(A.begin(), A.end(), // source range
            A.begin(),          // destination
            negate<int>());
  print_elements(A, "A after first transform: ");

  list<int> C;
  transform(A.begin(), A.end(), front_inserter(C),
            bind2nd(multiplies<int>(), 10));
  print_elements(A, "A after second transform: ");
  print_elements(C, "C after second transform: ");

  transform(C.begin(), C.end(), ostream_iterator<int>(cout, "_"),
            negate<int>());
  cout << endl;

  return 0;
}
