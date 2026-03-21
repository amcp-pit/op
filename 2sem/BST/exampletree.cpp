#include <iostream>
#include "bintree.hpp"

int main() {
	BinTree<int> tree;
	for(int i=0; i < 20; ++i) {
		int tmp = rand()%1000;
		tree.insert(tmp);
		std::cout << "inserted " << tmp
				  << ", height: " << tree.height()
				  << std::endl;
	}

	for(auto pos = tree.begin(); pos!=tree.end(); ++pos) {
		std::cout<< *pos << " ";
	}
	return 0;
}
