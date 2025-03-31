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
//	tree.print();
	for(auto pos=tree.begin(); pos!=tree.end(); ++pos){
		std::cout << *pos <<", ";
	}
	std::cout << std::endl;

	int tmp;
	do {
		std::cout << "> ";
		std::cin >> tmp;
		auto pos = tree.find(tmp);
		if (pos!=tree.end()) {
            tree.erase(pos);
			std::cout << "was at set\n";
		} else {
			std::cout << "not at set\n";
		}
	} while (tmp>0);


    for(auto pos=tree.begin(); pos!=tree.end(); ++pos){
        std::cout << *pos <<", ";
    }
    std::cout << std::endl;

	return 0;
}
