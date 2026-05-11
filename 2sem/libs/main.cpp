#include "my_math.h"
#include <iostream>

int main() {
  double d = 100;
  std::cout << "sqrt(" << d << ") = ";
  std::cout << calcSqrt(d) << std::endl;
  return 0;
}
