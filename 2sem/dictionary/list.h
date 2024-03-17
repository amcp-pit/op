#pragma once

template <typename ElementType>
class List {
	struct Node {
		Node* prev, * next;
		ElementType data;
		Node(const ElementType& X) : prev(nullptr), next(nullptr), data(X) {}
		Node(ElementType&& X) : prev(nullptr), next(nullptr), data(std::move(X)) {}
	};
	Node* first, * last;
	size_t count;
	bool isSorted;
	void swap(List& other) {
		std::swap(isSorted, other.isSorted);
		std::swap(count, other.count);
		std::swap(first, other.first);
		std::swap(last, other.last);
	}
public:
	List() : first(nullptr), last(nullptr), count(0), isSorted(true) {}
	List(const List&);
	List(List&&);
	~List() { clear(); }
	List& operator=(const List&);
	List& operator=(List&&);

	void clear();
	void empty() { clear(); }
	size_t size() const { return count; }
	size_t capacity() const { return -1; }
	void push_back(const ElementType&);

	class iterator {
		Node* current;
	public:
		iterator(Node* p = nullptr) : current(p) {}
		ElementType& operator*() { return current->data; }
		const ElementType& operator*() const { return current->data; }
		bool operator==(const iterator& p) const { return current == p.current; }
		bool operator!=(const iterator& p) const { return current != p.current; }
		iterator& operator++() { 
			if (current) current = current->next;
			else throw "Iterator: out of bounds";
			return *this; 
		}
		iterator operator++(int) { 
			Node* tmp = current; 
			if (current) current = current->next;
			else throw "Iterator: out of bounds";
			return iterator(tmp);
		}
		friend class List;
	};

	iterator begin() const { return iterator(first); }
	iterator end() const { return iterator(nullptr); }

	class reverse_iterator{
		Node* current;
	public:
		reverse_iterator(Node* p = nullptr) : current(p) {}
		ElementType& operator*() { return current->data; }
		const ElementType& operator*() const { return current->data; }
		bool operator==(const reverse_iterator& p) const { return current == p.current; }
		bool operator!=(const reverse_iterator& p) const { return current != p.current; }
		reverse_iterator& operator++() {
			if (current) current = current->prev;
			else throw "Iterator: out of bounds";
			return *this;
		}
		reverse_iterator operator++(int) {
			Node* tmp = current;
			if (current) current = current->prev;
			else throw "Iterator: out of bounds";
			return reverse_iterator(tmp);
		}
	};

	reverse_iterator rbegin() const { return reverse_iterator(last); };
	reverse_iterator rend() const { return reverse_iterator(nullptr); }

	iterator find(const ElementType&)const;
	void sort();
	void erase(const iterator&);
};
//-------------------------------------------------------------------------------------------
template <typename ElementType>
List<ElementType>::List(const List<ElementType>& X) {
	first = last = nullptr;
	count = 0;
	for (auto pos = X.begin(); pos != X.end(); ++pos) {
		push_back(*pos);
	}
	isSorted = X.isSorted;
}
//-------------------------------------------------------------------------------------------
template <typename ElementType>
List<ElementType>::List(List<ElementType>&& X) {
	count = X.count;
	first = X.first;
	last = X.last;
	isSorted = X.isSorted;
	X.count = 0;
	X.first = nullptr;
	X.last = nullptr;
}
//-------------------------------------------------------------------------------------------
template <typename ElementType>
List<ElementType>& List<ElementType>::operator=(const List<ElementType>& X) {
	if (this != &X) {
		/*
		clear();
		for (auto pos = X.begin(); pos != X.end(); ++pos) {
			push_back(*pos);
		}
		isSorted = X.isSorted;
		*/
		List<ElementType> tmp(X);
		swap(tmp);
	}
	return *this;
}
//-------------------------------------------------------------------------------------------
template <typename ElementType>
List<ElementType>& List<ElementType>::operator=(List<ElementType>&& X) {
	if (this != &X) {
		/*
		clear();
		count = X.count;
		first = X.first;
		last = X.last;
		isSorted = X.isSorted;
		X.count = 0;
		X.first = nullptr;
		X.last = nullptr;
		*/
		swap(X);
	}
	return *this;
}
//-------------------------------------------------------------------------------------------
template <typename ElementType>
void List<ElementType>::push_back(const ElementType& X) {
	if (!first) { // Пустой список
		first = last = new Node(X);
	}
	else {
		last->next = new Node(X);
		last->next->prev = last;
		last = last->next;
	}
	++count;
	isSorted = false;
}
//-------------------------------------------------------------------------------------------
template <typename ElementType>
void List<ElementType>::clear() {
	Node* tmp;
	while (first) {
		tmp = first;
		first = first->next;
		delete tmp;
	}
	count = 0; 
	last = nullptr; //first = nullptr; Уже, так как циклом while прошлись до конца.
}
//-------------------------------------------------------------------------------------------
template <typename ElementType>
typename List<ElementType>::iterator List<ElementType>::find(const ElementType& X)const {
	Node* now = first;
	if (isSorted) {
		while (now) {
			if (now->data < X) {
				now = now->next;
			} 
			else if (now->data == X) {
				return iterator(now);
			}
			else {
				break;
			}
		}
	} else {
		while (now) {
			if (now->data == X) {
				return iterator(now);
			}
			now = now->next;
		}
	}
	return end();
}
//-------------------------------------------------------------------------------------------
template <typename ElementType>
void List<ElementType>::erase(typename const List<ElementType>::iterator& pos) {
	if (pos == end()) return;
	Node* p = pos.current->prev;
	Node* n = pos.current->next;
	if (p != nullptr) {
		p->next = n;
	}
	else { // Значит удаляем первый элемент
		first = n;
	}

	if (n != nullptr) {
		n->prev = p;
	}
	else { // Значит удаляем последний в списке
		last = p;
	}
	delete pos.current;
	--count;
}
//-------------------------------------------------------------------------------------------
template <typename ElementType>
void List<ElementType>::sort() {
	if (first == last) return;
	isSorted = false;
	do {
		//split
		Node* begins[2], * ends[2];
		unsigned char p = 0; // номер текущего списка (в который добавляем)
		begins[p] = ends[p] = first;
		first = first->next;
		begins[!p] = ends[!p] = nullptr;

		while (first) {
			if (first->data < ends[p]->data) p = !p; // p = 1-p;
			if (!begins[p]) begins[p] = first;
			else ends[p]->next = first;
			ends[p] = first;
			first = first->next;
		}
		if (ends[p]) ends[p]->next = nullptr;
		if (ends[!p]) ends[!p]->next = nullptr;

		//merge
		if (begins[!p]) { // Значит второй список не пустой и нужно делать слияние
			bool s1, s2;
			p = (begins[0]->data < begins[1]->data) ? 0 : 1;
			first = last = begins[p];
			begins[p] = begins[p]->next;
			while (begins[p]) {
				s1 = (begins[p]->data < last->data);
				s2 = (begins[!p]->data < last->data);
				if (s1 == s2)
					p = (begins[0]->data < begins[1]->data) ? 0 : 1;
				else
					if (s1) p = !p;
				last->next = begins[p];
				last = last->next;
				begins[p] = begins[p]->next;
			}
			last->next = begins[!p];
		}
		else {
			first = begins[p];
			isSorted = true;
		}
	} while (!isSorted);

	// Восстановить связь prev
	first->prev = nullptr;
	Node* now = first;
	while (now->next) {
		now->next->prev = now;
		now = now->next;
	}
	last = now;
}
//-------------------------------------------------------------------------------------------

