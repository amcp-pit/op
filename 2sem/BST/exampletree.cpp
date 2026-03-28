#include <iostream>
#include "bintree.hpp"
#include "AVLtree.hpp"

int main() {
	BinTree<int> tree;
	for(int i=0; i < 2000; ++i) {
		int tmp = rand()%1000;
		tree.insert(tmp);
/*		std::cout << "inserted " << tmp
				  << ", height: " << tree.height()
				  << std::endl;
*/
	}

    std::cout << "height: " << tree.height()
                  << std::endl;

/*	for(auto pos = tree.begin(); pos!=tree.end(); ++pos) {
		std::cout<< *pos << " ";
	}
    std::cout << std::endl;
*/
	int tmp = 0;
	do {
		std::cout << "> ";
		std::cin >> tmp;
		auto pos = tree.find(tmp);
		if (pos != tree.end()){
			tree.erase(pos);
			std::cout << "was in set\n";
		} else {
			std::cout << "not in set\n";
		}
	} while(tmp > 0);

    for(auto pos = tree.begin(); pos!=tree.end(); ++pos) {
        std::cout<< *pos << " ";
    }
	std::cout << std::endl;
	return 0;
}
