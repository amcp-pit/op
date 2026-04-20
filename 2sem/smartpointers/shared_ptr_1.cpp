#include <iostream>
#include <memory> // для std::shared_ptr
 
class Item {
public:
	Item() { std::cout << "Item acquired\n"; }
	~Item() { std::cout << "Item destroyed\n"; }
};
 
int main() {
	// Выделяем Item и передаем его в std::shared_ptr
	Item *item = new Item;
	std::shared_ptr<Item> ptr1(item);
	{
		std::shared_ptr<Item> ptr2(ptr1);
		std::cout << "Killing one shared pointer\n";
	} // ptr2 выходит из области видимости здесь
 
	std::cout << "Killing another shared pointer\n";
 
	return 0;
} 
// ptr1 выходит из области видимости здесь, 
// и выделенный Item уничтожается также здесь
