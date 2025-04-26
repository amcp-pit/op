#include <iostream>
 
template<class T>
class Auto_ptr4 {
	T* m_ptr;
public:
	Auto_ptr4(T* ptr = nullptr) : m_ptr(ptr) { }
	~Auto_ptr4() {
		delete m_ptr;
	}
 
	// Конструктор копирования, который выполняет глубокое копирование x.m_ptr в m_ptr
	Auto_ptr4(const Auto_ptr4& x) {
		m_ptr = new T;
		*m_ptr = *x.m_ptr;
	}
 
	// Конструктор перемещения, который передает право собственности на x.m_ptr в m_ptr
	Auto_ptr4(Auto_ptr4&& x) : m_ptr(x.m_ptr) {
		x.m_ptr = nullptr; 
	}
 
	// Оператор присваивания копированием, который выполняет глубокое копирование x.m_ptr в m_ptr
	Auto_ptr4& operator=(const Auto_ptr4& x) {
		if (&x != this){ // Проверка на самоприсваивание

			// Удаляем всё, что к этому моменту может хранить указатель 
			delete m_ptr;
 
			// Копируем передаваемый объект
			m_ptr = new T;
			*m_ptr = *x.m_ptr;
    	}
		return *this;
	}
 
	// Оператор присваивания перемещением, который передает право собственности на x.m_ptr в m_ptr
	Auto_ptr4& operator=(Auto_ptr4&& x) {
		if (&x != this){ // Проверка на самоприсваивание
 
			// Удаляем всё, что к этому моменту может хранить указатель 
			delete m_ptr;
 
			// Передаем право собственности на x.m_ptr в m_ptr
			m_ptr = x.m_ptr;
			x.m_ptr = nullptr; // мы поговорим об этом чуть позже
		} 
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
 
Auto_ptr4<Item> generateItem() {
	Auto_ptr4<Item> item(new Item);
	return item; // это возвращаемое значение приведет к вызову конструктора перемещения
}
 
int main() {
	Auto_ptr4<Item> mainItem;
	mainItem = generateItem(); // эта операция присваивания приведет к вызову оператора присваивания перемещением
 
	return 0;
}
