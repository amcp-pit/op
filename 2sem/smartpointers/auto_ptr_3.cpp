#include <iostream>
 
/*
Умный указатель, в котором конструктор копирования и оператор присваивания
копированием переопределены для выполнения глубокого копирования.
*/
template<class T>
class Auto_ptr3 {
	T* m_ptr;
public:
	Auto_ptr3(T* ptr = nullptr) : m_ptr(ptr) { }
	~Auto_ptr3() {
		delete m_ptr;
	}

	// Конструктор копирования, который выполняет глубокое копирование x.m_ptr в m_ptr
	Auto_ptr3(const Auto_ptr3& x) {
		m_ptr = new T;
		*m_ptr = *x.m_ptr;
	}

	// Оператор присваивания копированием, который выполняет глубокое копирование x.m_ptr в m_ptr
	Auto_ptr3& operator=(const Auto_ptr3& x) {
		// Проверка на самоприсваивание
		if (&x == this)
			return *this;

		// Удаляем всё, что к этому моменту может хранить указатель
		delete m_ptr;

		// Копируем передаваемый объект
		m_ptr = new T;
		*m_ptr = *x.m_ptr;

		return *this;
	}

	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
	bool isNull() const { return m_ptr == nullptr; }
};

class Item {
public:
	Item() { std::cout << "Item acquired\n"; }
	~Item() { std::cout << "Item destroyed\n"; }
};

Auto_ptr3<Item> generateItem() {
	Auto_ptr3<Item> item(new Item);
	std::cout << "Generate Item\n";
	return item; // это возвращаемое значение приведет к вызову конструктора копирования
}

int main() {
	Auto_ptr3<Item> mainItem;
	std::cout << "before operator = \n";
	mainItem = generateItem(); // эта операция присваивания приведет к вызову
							   // оператора присваивания копированием
	std::cout << "after operator = \n";
	return 0;
}
