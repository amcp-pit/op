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
	void sayHello() { std::cout << "Hello!\n"; }
};

void myFunction() {
	Auto_ptr1<Item> ptr(new Item); // ptr теперь "владеет" Item-ом
	int a;
	std::cout << "Enter an integer: ";
	std::cin >> a;
	if (a == 0) {
		return; // досрочный возврат функции
	}
	// Использование ptr
	ptr->sayHello();
}
 
int main() {
	myFunction();
	return 0;
} 

/*
Если пользователь введет ненулевое целое число, то результат выполнения программы: 
Item acquired
Enter an integer: 1
Hello!
Item destroyed

Если же пользователь введет ноль, то функция myFunction() завершит свое выполнение досрочно, 
и увидим:
Item acquired
Enter an integer: 0
Item destroyed

*/