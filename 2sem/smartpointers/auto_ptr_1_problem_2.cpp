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

	// Перегрузка оператора разыменования и оператора ->,
	// чтобы иметь возможность использовать Auto_ptr1 как m_ptr
	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
};

class Item {
public:
    Item() { std::cout << "Item acquired\n"; }
    ~Item() { std::cout << "Item destroyed\n"; }
};
 

int main() {

	{
		Auto_ptr1<Item> item1(new Item);
		Auto_ptr1<Item> item2;
		item2 = item1;
	}

	return 0;
}

/*
Результат выполнения программы:
	Item acquired
	Item destroyed
	Item destroyed
	и далее, очень вероятно, что произойдет сбой в программе,
	так как будет освобождение памяти по одному и тому же адресу дважды.
*/
