#include <iostream>
 
/*
Различие указателя на одиночный объект и указателя на массив 
через параметр шаблона и частичную специализацию.
*/
template<class T>
class Auto_ptr6 {
	T* m_ptr;
public:
	Auto_ptr6(T* ptr = nullptr) : m_ptr(ptr) { }
	~Auto_ptr6() { 
	    std::cout << "- Delete object\n";
		delete m_ptr; 
	    std::cout << "- Object deleted\n";
	}

	Auto_ptr6(const Auto_ptr6& x) = delete;
	Auto_ptr6(Auto_ptr6&& x) : m_ptr(x.m_ptr) {	x.m_ptr = nullptr; }

	Auto_ptr6& operator=(const Auto_ptr6& x) = delete;
	Auto_ptr6& operator=(Auto_ptr6&& x) {
		if (&x == this)
			return *this;

		delete m_ptr;
		m_ptr = x.m_ptr;
		x.m_ptr = nullptr;
 
		return *this;
	}

	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
	bool isNull() const { return m_ptr == nullptr; }
};

template<class T>
class Auto_ptr6<T[]> {
	T* m_ptr;
public:
	Auto_ptr6(T* ptr = nullptr) : m_ptr(ptr) { }
	~Auto_ptr6() {
	    std::cout << "- Delete array\n";
		delete[] m_ptr; 
	    std::cout << "- Array deleted\n";
	}

	Auto_ptr6(const Auto_ptr6& x) = delete;
	Auto_ptr6(Auto_ptr6&& x) : m_ptr(x.m_ptr) {	x.m_ptr = nullptr; }

	Auto_ptr6& operator=(const Auto_ptr6& x) = delete;
	Auto_ptr6& operator=(Auto_ptr6&& x) {
		if (&x == this)
			return *this;

		delete[] m_ptr;
		m_ptr = x.m_ptr;
		x.m_ptr = nullptr;
 
		return *this;
	}

	// Нет operator-> и operator*
	bool isNull() const { return m_ptr == nullptr; }
};
 
class Item {
public:
	Item() { std::cout << "Item acquired\n"; }
	~Item() { std::cout << "Item destroyed\n"; }
};
 
int main() {
	{   // Одиночный объект
		std::cout << "--- Single Item\n";
		Auto_ptr6<Item> p1(new Item);
	} // Выполнится delete

	{   // Массив
		std::cout << "--- Array of Items\n";
		Auto_ptr6<Item[]> p2(new Item[5]);
    } // Выполнится delete[]

	{   // ОШИБКА! Неправильное удаление
		std::cout << "--- Error\n";
		Auto_ptr6<Item> p3(new Item[5]);
    } // Выполнится delete, а надо было бы delete[]

	return 0;
}
