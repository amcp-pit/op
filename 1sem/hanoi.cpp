#include <iostream>

void hanoi(int n, int from=1, int to=3, int tmp=2){
    if(n>1){
        hanoi(n-1, from, tmp, to);
        hanoi(1, from, to, tmp);
        hanoi(n-1, tmp, to, from);
    } else {
        std::cout << from << " -> " << to << std::endl;
    }
}

int main(){
	hanoi(5);
	return 0;
}
