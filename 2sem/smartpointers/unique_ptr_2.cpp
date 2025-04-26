#include <iostream>
#include <memory> // для std::unique_ptr
 
class Item {
public:
	Item() { std::cout << "Item acquired\n"; }
	~Item() { std::cout << "Item destroyed\n"; }
};

std::ostream& operator<< (std::ostream& out, const Item& X) {
	out << "Item message\n";
	return out;
}

void takeOwnership(std::unique_ptr<Item> item) {
     if (item)
          std::cout << *item;
} // item уничтожается здесь

int main()
{
    auto ptr = std::make_unique<Item>();

//    takeOwnership(ptr); // это не скомпилируется. 
                          // Надо использовать семантику перемещения
    takeOwnership(std::move(ptr)); // используем семантику перемещения

    return 0;
}
