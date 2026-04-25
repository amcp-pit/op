#include <algorithm>
#include <deque>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>

using namespace std;

int main() {
  deque<string> S;
  S.assign(4, string("string"));
  S.push_back("last string");
  S.push_front("first string");

  copy(S.begin(), S.end(), ostream_iterator<string>(cout, "\n"));



  S.pop_back();   // Удаление последнего элемента контейнера
  S.pop_front();  // Удаление первого элемента контейнера

  // доступ к элементам по индексу
  for (size_t i = 0; i < S.size(); ++i) {
    S[i] = "another " + S[i];
  }

  cout << setfill('=') << setw(20) << " " << setfill(' ') << '\n';
  copy(S.begin(), S.end(), ostream_iterator<string>(cout, "\n"));



  // Изменение размера котейнера (с указанием значения по умолчанию)
  S.resize(8, "new string");

  cout << setfill('=') << setw(20) << " " << setfill(' ') << '\n';
  copy(S.begin(), S.end(), ostream_iterator<string>(cout, "\n"));


  return 0;
}
