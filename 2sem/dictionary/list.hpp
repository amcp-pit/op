#ifndef _MY_LIST_26_
#define _MY_LIST_26

template <typename T>
class List {
	struct Node {
		Node * prev_;
		Node * next_;
		T data_;
		Node(const T& x) : prev_(nullptr), next_(nullptr), data_(x) {}
		Node(T&& x) : prev_(nullptr), next_(nullptr), data_(std::move(x)) {}
	};

	size_t size_;
	Node * first_;
	Node * last_;
	bool isSorted;

	void swap(List<T> & other) noexcept {
		std::swap(size_, other.size_);
		std::swap(first_, other.first_);
		std::swap(last_, other.last_);
		std::swap(isSorted, other.isSorted);
	}

public:
	List() : size_(0), first_(nullptr), last_(nullptr), isSorted(true) {}
	~List() { empty(); }
	List(const List&);

    List& operator= (const List& other) {
		if (this != &other){
			List<T> tmp(other);
			swap(tmp);
		}
		return *this;
	}

#ifndef NOMOVESEMANTICS
	List(List&& other) noexcept : size_(0), first_(nullptr), last_(nullptr), isSorted(true) {
		swap(other);
	}

    List& operator= (List&& other) {
		if (this != &other) {
			swap(other);
		}
		return *this;
	}
#endif

	size_t size() const { return size_; }
	size_t capacity() const { return -1; }

	void push_back(const T&);
	void empty();

	class iterator {
		Node* current;
		iterator(Node *p = nullptr) : current(p) {}
	public:
		T& operator*() { return current->data_;}
		const T& operator*() const {return current->data_;}
		bool operator==(const iterator& other) const {
			return current == other.current;
		}
        bool operator!=(const iterator& other) const {
            return current != other.current;
        }
		iterator& operator++() { // ++pos
			if (current) {current = current->next_;}
			else throw "iterator: out of bounds";
			return *this;
		}
		iterator operator++(int){ // pos++
			Node *tmp = current;
			if (current) {current = current->next_;}
            else throw "iterator: out of bounds";
			return iterator(tmp);
		}
		friend class List;
	};

	iterator begin() const { return iterator(first_); }
	iterator end() const {return iterator(nullptr);}

    class reverse_iterator {
        Node* current;
        reverse_iterator(Node *p = nullptr) : current(p) {}
    public:
        T& operator*() { return current->data_;}
        const T& operator*() const {return current->data_;}
        bool operator==(const reverse_iterator& other) const {
            return current == other.current;
        }
        bool operator!=(const reverse_iterator& other) const {
            return current != other.current;
        }
        reverse_iterator& operator++() { // ++pos
            if (current) {current = current->prev_;}
            else throw "iterator: out of bounds";
            return *this;
        }
        reverse_iterator operator++(int){ // pos++
            Node *tmp = current;
            if (current) {current = current->prev_;}
            else throw "iterator: out of bounds";
            return reverse_iterator(tmp);
        }
        friend class List;
    };

	reverse_iterator rbegin() const { return reverse_iterator(last_); }
	reverse_iterator rend() const { return reverse_iterator(nullptr); }

	iterator find(const T& x) const;
	void sort();
};


template <typename T>
void List<T>::push_back(const T& x) {
	if (first_ == nullptr) {
		first_ = last_ = new Node(x);
		isSorted = true;
	} else {
		last_->next_ = new Node(x);
		last_->next_->prev_ = last_;
		last_ = last_->next_;
		isSorted = false;
	}
	++size_;
}

template <typename T>
void List<T>::empty() {
	Node * tmp;
	while (first_) {
		tmp = first_;
		first_ = first_->next_;
		delete tmp;
	}
	size_ = 0;
	last_ = nullptr;
	isSorted = true;
}

template <typename T>
List<T>::List(const List<T> & other) {
	first_ = last_ = nullptr;
	size_ = 0;
	for(auto pos = other.begin(); pos!=other.end(); ++pos) {
		push_back(*pos);
	}
	isSorted = other.isSorted;
}


template <typename T>
typename List<T>::iterator List<T>::find(const T& x) const {
	if (isSorted) {
        Node * now = first_;
        while(now) {
            if (now->data_ == x) {
                return iterator(now);
            } else if (now->data_ < x) {
				now = now->next_;
			} else {
				break;
			}
        }
	} else {
		Node * now = first_;
		while(now) {
			if (now->data_ == x) {
				return iterator(now);
			}
			now = now->next_;
		}
	}
	return end();
}

template <typename T>
void List<T>::sort() {
	if (first_ == last_) return;
	isSorted = false;
	do {
		// Split
		Node * begins[2];
		Node * ends[2];
		unsigned char p = 0;
		begins[p] = ends[p] = first_;
		first_ = first_->next_;
		begins[1-p] = ends[1-p] = nullptr;
		while(first_) {
			if (first_->data_ < ends[p]->data_) p = 1 - p;
			if (!begins[p]) begins[p] = first_;
			else ends[p]->next_ = first_;
			ends[p] = first_;
			first_ = first_->next_;
		}
		if (ends[p]) ends[p]->next_ = nullptr;
        if (ends[1-p]) ends[1-p]->next_ = nullptr;

		// Merge
		if (begins[1-p]){
			bool s1, s2;
			p = (begins[0]->data_ < begins[1]->data_) ? 0 : 1;
			first_ = last_ = begins[p];
			begins[p] = begins[p]->next_;
			while (begins[p]){
				s1 = (begins[p]->data_ < last_->data_);
                s2 = (begins[1-p]->data_ < last_->data_);
				if (s1 == s2) {
					p = (begins[0]->data_ < begins[1]->data_) ? 0 : 1;
				} else {
					if (s1) p = 1 - p;
				}
				last_->next_ = begins[p];
				last_ = last_->next_;
				begins[p] = begins[p]->next_;
			}
			last_->next_ = begins[1-p];
		} else {
			first_ = begins[p];
			isSorted = true;
		}
	} while(!isSorted);

	// repair prev_ link
	first_->prev_ = nullptr;
	Node * now = first_;
	while(now->next_) {
		now->next_->prev_ = now;
		now = now->next_;
	}
	last_ = now;
}

#endif
