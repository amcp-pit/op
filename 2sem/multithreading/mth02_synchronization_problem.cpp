#include <iostream>
#include <string>
#include <thread>

void runA(bool& value, int i) {
  if(value) {
	  int res = 0;
	  for(int j=0; j<=10000*(i+1); ++j) res+=i;

      std::string out = "[ " + std::to_string(i) + " ] value "
                         + std::to_string(value) ;
      std::cout << out;
	  if (!value){
		std::cout << " " << res;
	  }
	  std::cout <<"\n";
  }
}

void runB(bool& value) {
    value = false;
}

int main() {
    for(int i = 0; i < 20; i++) {
        bool value = true; //1
        std::thread tA(runA, std::ref(value), i);
        std::thread tB(runB, std::ref(value));
        tA.join();
        tB.join();
    }
}
