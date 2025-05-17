#include <iostream>
#include <string>
#include <thread>

void run(std::string threadName) {
  for (int i = 0; i < 20; ++i) {
    std::string out = threadName + std::to_string(i) + "\n";
    std::cout << out;
  }
}

int main() {
  std::thread thrA(run, "A");
  std::thread thrB(run, "\tB");
  thrA.join();
  thrB.join();
}
