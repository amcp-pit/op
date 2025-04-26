#include <iostream>
#include <memory> // для std::shared_ptr
 
class Item {
public:
	Item() { std::cout << "Item acquired\n"; }
	~Item() { std::cout << "Item destroyed\n"; }
};

int main() {
	// Выделяем Item и передаем его в std::shared_ptr
	auto ptr1 = std::make_shared<Item>();
	{
		auto ptr2 = ptr1; // создаем ptr2 из ptr1, 
                           //  используя семантику копирования
		std::cout << "Killing one shared pointer\n";
	} // ptr2 выходит из области видимости здесь, 
    // но ничего больше не происходит
 
	std::cout << "Killing another shared pointer\n";
 
	return 0;
} 
// ptr1 выходит из области видимости здесь, 
// и выделенный Item уничтожается также здесь
