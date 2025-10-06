#include <iostream>

void foo(int a, int b){
	int tmp = a;
	a = b;
	b = tmp;
}

void foo(int *a, int *b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void bar(int &a, int &b){
	int tmp = a;
	a = b;
	b = tmp;
}


void print(int x, int y, const char * msg=""){
	std::cout << msg <<"x = " << x <<", y = " << y << std::endl;
}

int main(){
	int x = 1, y = 2;
	print(x, y, "Before: ");
	foo(x, y);
	print(x, y, "After foo: ");
	foo(&x, &y);
	print(x, y, "After foo pointers: ");
	bar(x, y);
	print(x, y);
	return 0;
}
