#include <iostream>
#include <memory> // для std::unique_ptr
 
class Item {
public:
	Item() { std::cout << "Item acquired\n"; }
	~Item() { std::cout << "Item destroyed\n"; }
};
 
int main()
{
	// Выделяем объект класса Item 
  // и передаем право собственности на него std::unique_ptr
	std::unique_ptr<Item> item1(new Item);
	std::unique_ptr<Item> item2; // присваивается значение nullptr
 
	// item2 = item1; // не скомпилируется: семантика копирования отключена
	item2 = std::move(item1); // item2 теперь владеет item1, 
                            // а для item1 присваивается значение null
 
	return 0;
} 
// item1, item2 выходят из области видимости и уничтожаются
