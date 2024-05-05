#include <iostream>
 
template<class T>
class Auto_ptr1 {
	T* m_ptr;
public:
	// Получаем указатель для "владения" через конструктор
	Auto_ptr1(T* ptr=nullptr) : m_ptr(ptr) { } 	
	
	// Деструктор позаботится об удалении указателя
	~Auto_ptr1() {	
		delete m_ptr;

	}
 
	// Перегрузка оператора разыменования и оператора ->, чтобы иметь возможность использовать Auto_ptr1 как m_ptr
	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
};
 
class Item {
public:
    Item() { std::cout << "Item acquired\n"; }
    ~Item() { std::cout << "Item destroyed\n"; }
};
 
int main() {
	Auto_ptr1<Item> item(new Item); // динамическое выделение памяти
    // ... но никакого явного delete здесь не нужно
 
	return 0;
} // item выходит из области видимости здесь и уничтожает выделенный Item
