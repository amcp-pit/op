#include <iomanip>
#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
  multimap<int, string> M;
  M.insert(make_pair(4, "of"));
  M.insert(make_pair(2, "a"));
  M.insert(make_pair(5, "tagged"));
  M.insert(make_pair(1, "this"));
  M.insert(make_pair(6, "strings"));
  M.insert(make_pair(3, "multimap"));
  M.insert(make_pair(1, "is"));

  for (auto pos = M.begin(); pos != M.end(); ++pos) {
    cout << pos->second << " ";
  }
  cout << endl;

  for (auto pos = M.begin(); pos != M.end(); ++pos) {
    cout << pos->first << " " << pos->second << "\n";
  }
  cout << endl;

  map<string, float> C;
  C.insert(make_pair("e", 2.71));
  C.insert(make_pair("G", 6.67e-23));
  C["pi"] = 3.1415;
  C["g"] = 9.81;
  C["Null"] = 0;
  for (auto pos = C.begin(); pos != C.end(); ++pos) {
    cout << "key: " << pos->first << "\t = " << pos->second << endl;
  }
  cout << "result = " << C["G"] * 1e24 * C["pi"] / C["g"] << endl;

  return 0;
}
