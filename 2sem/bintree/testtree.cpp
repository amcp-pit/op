#include <iostream>
#include "bintree.h"

int main(){
	BinTree<int> tree;
	for(int i=0; i<20; ++i){
		int tmp = rand()%1000;
		tree.insert(tmp);
		std::cout << "inserted " << tmp <<", height " << tree.height() << std::endl;
	}
	std::cout << std::endl;
	std::cout << "From tree: ";
	tree.print();

	return 0;
}
