#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

int main() {
  vector<string> sentence;
  sentence.reserve(10);
  sentence.push_back("Hello");
  sentence.push_back("how");
  sentence.push_back("are");
  sentence.push_back("you");
  sentence.push_back("?");

  for (vector<string>::iterator pos = sentence.begin();
       pos != sentence.end();
       ++pos) {
    cout << *pos << ' ';
  }
  cout << endl;


  // Автоматический вывод типа для итератора
  for (auto pos = sentence.begin(); pos != sentence.end(); ++pos) {
    cout << *pos << ' ';
  }
  cout << endl;



  // Вывод элементов массива в обратном порядке
  for (vector<string>::reverse_iterator pos = sentence.rbegin();
       pos != sentence.rend(); ++pos) {
    cout << *pos << ' ';
  }
  cout << endl;



  // Вывод с помощью алгоритма copy (между словами знак '_' для примера)
  copy(sentence.begin(), sentence.end(), ostream_iterator<string>(cout, "_"));
  cout << endl;

  copy(sentence.rbegin(), sentence.rend(), ostream_iterator<string>(cout, "_"));
  cout << endl;



  // Пример поиска элемента в контейнере, вставки элемента и т.п.
  swap(sentence[1], sentence[3]);
  sentence.insert(find(sentence.begin(), sentence.end(), "?"), "always");
  sentence.back() = "!";

  copy(sentence.begin(), sentence.end(), ostream_iterator<string>(cout, " "));
  cout << endl;



  // Перестановка части массива (с первого элемента до восклицательного знака) в обратном порядке
  reverse(sentence.begin(), find(sentence.begin(), sentence.end(), "!"));
  copy(sentence.begin(), sentence.end(), ostream_iterator<string>(cout, " "));
  cout << endl;

  return 0;
}
