#pragma once

template <typename T>
class List{
	struct Node{
		Node *prev, *next;
		T data;
		Node(const T& x) : prev(nullptr), next(nullptr), data(x) {}
		Node(T&& x) : prev(nullptr), next(nullptr), data(std::move(x)) {}
	};
	Node *first, *last;
	size_t size_;
	bool isSorted;

	void swap(List<T> &other) noexcept {
		std::swap(first, other.first);
		std::swap(last, other.last);
		std::swap(isSorted, other.isSorted);
		std::swap(size_, other.size_);
	}
public:
	List() : first(nullptr), last (nullptr), size_(0), isSorted(true) {}
	~List() { clear(); }
	List(const List&);
	List(List&& other) noexcept;
	List& operator=(const List& other) {
		if (this!=&other){
			List<T> tmp(other);
			swap(tmp);
		}
		return *this;
	}
	List& operator=(List&& other) noexcept {
		if (this!=&other){
			swap(other);
		}
		return *this;
	}
	size_t size() const { return size_; }
	size_t capacity() const { return -1; }
	void push_back(const T&);
	void clear();
	void empty() { clear(); }

	class iterator {
		Node* current;
	public:
		iterator(Node *p=nullptr) : current(p) {}
		T& operator*() { return current->data; }
		const T& operator*() const { return current->data; }
		bool operator==(const iterator& other) const {
			return current == other.current;
		}
        bool operator!=(const iterator& other) const {
            return current != other.current;
        }
		iterator& operator++() {
			if (current) current = current->next;
			else throw "Iterator: out of bounds";
			return *this;
		} // ++pos
		iterator operator++(int) { // pos++
			Node* tmp = current;
            if (current) current = current->next;
            else throw "Iterator: out of bounds";
			return iterator(tmp);
		}
	};
	iterator begin() const { return iterator(first); }
	iterator end() const { return iterator(nullptr); }

	class reverse_iterator{
        Node* current;
    public:
        reverse_iterator(Node *p=nullptr) : current(p) {}
        T& operator*() { return current->data; }
        const T& operator*() const { return current->data; }
        bool operator==(const reverse_iterator& other) const {
            return current == other.current;
        }
        bool operator!=(const reverse_iterator& other) const {
            return current != other.current;
        }
        reverse_iterator& operator++() {
            if (current) current = current->prev;
            else throw "Iterator: out of bounds";
            return *this;
		} // ++pos
        reverse_iterator operator++(int) { // pos++
            Node* tmp = current;
            if (current) current = current->prev;
            else throw "Iterator: out of bounds";
            return iterator(tmp);
        }
	};
	reverse_iterator rbegin() const { return reverse_iterator(last); }
	reverse_iterator rend() const { return reverse_iterator(nullptr); }

	iterator find(const T& x)const;
	void sort();
};

template <typename T>
void List<T>::push_back(const T& x){
	if (first == nullptr){
		first = last = new Node(x);
		isSorted = true;
	} else {
		last->next = new Node(x);
		last->next->prev = last;
		last = last->next;
		isSorted = false;
	}
	++size_;
}

template <typename T>
void List<T>::clear(){
	Node* tmp;
	while(first){
		tmp = first;
		first = first->next;
		delete tmp;
	}
	size_ = 0;
	last = nullptr;
}

template <typename T>
List<T>::List(const List<T>& other){
	first = last = nullptr;
	size_ = 0;
	for(auto pos=other.begin(); pos!=other.end(); ++pos){
		push_back(*pos);
	}
	isSorted = other.isSorted;
}

template <typename T>
List<T>::List(List<T>&& other) noexcept{
	first = last = nullptr;
	size_ = 0;
	isSorted= true;
	swap(other);
}

template <typename T>
typename List<T>::iterator List<T>::find(const T& x)const{
	Node* now = first;
	while(now){
		if(now->data == x){
			return iterator(now);
		}
		now = now->next;
	}
	return end();
}

template <typename T>
void List<T>::sort() {
	if (first == last) return;
	isSorted = false;
	do {
		//split
		Node *begins[2], *ends[2];
		unsigned char p = 0;
		begins[p] = ends[p] = first;
		first = first->next;
		begins[1-p] = ends[1-p] = nullptr;
		while(first){
			if(first->data < ends[p]->data) p = 1-p;
			if (!begins[p]) begins[p] = first;
			else ends[p]->next = first;
			ends[p] = first;
			first = first->next;
		}
		if (ends[p]) ends[p]->next = nullptr;
        if (ends[1-p]) ends[1-p]->next = nullptr;

		if (begins[1-p]){
	        //merge
			bool s1, s2;
			p = (begins[0]->data < begins[1]->data) ? 0 : 1;
			first = last = begins[p];
			begins[p] = begins[p]->next;
			while(begins[p]){
				s1 = (begins[p]->data < last->data);
                s2 = (begins[1-p]->data < last->data);
				if (s1 == s2){
					p = (begins[0]->data < begins[1]->data) ? 0 : 1;
				} else {
					if (s1) p = 1-p;
				}
				last->next = begins[p];
				last = last->next;
				begins[p] = begins[p]->next;
			}
			last->next = begins[1-p];
		} else {
			first = begins[p];
			isSorted = true;
		}
	}while(!isSorted);

	// repair prev link
	first->prev = nullptr;
	Node *now = first;
	while(now->next){
		now->next->prev = now;
		now = now->next;
	}
	last = now;
	// isSorted = true;
}
