#pragma once

template <typename T>
class AVLTree{
	struct Node{
		Node *left, *right, *parent;
		T data;
		signed char balance;
		Node(const T& x): left(nullptr), right(nullptr), parent(nullptr), data(x), balance(0) {}

		Node(const Node&) = delete;
		Node& operator=(const Node&) = delete;

		~Node() {
			delete left;
			delete right;
		}

		int height() const {
			int L = (left==nullptr) ? 0 : left->height();
			int R = (right==nullptr)? 0 : right->height();
			return R < L ? L+1 : R+1;
		}

		Node* minimum(){
			Node *current = this;
			while(current->left){
				current = current->left;
			}
			return current;
		}

		Node* next() {
			if (right)
				return right->minimum();
			Node *current = this;
			Node *p = parent;
			while (p){
				if (current == p->left)
					break;
				current = p;
				p = p->parent; // p = current->parent
			}
			return p;
		}
	};

	Node* rightRotate(Node *);
	Node* bigRightRotate(Node *);
    Node* leftRotate(Node *);
    Node* bigLeftRotate(Node *);

	Node *root;
	size_t count;
public:
	AVLTree() : root(nullptr), count(0) {}
	~AVLTree() {clear();}
	void clear() {delete root; root=nullptr; count=0;}
	void empty() {clear();}
	size_t size() const {return count;}
	void insert(const T&);
	int height() const { return root->height(); }

	class iterator{
		Node *current;
	public:
		iterator(Node *p=nullptr): current(p) {}
		T& operator*() const {return current->data;}
		bool operator== (const iterator &p) const {
			return current == p.current;
		}
        bool operator!= (const iterator &p) const {
            return current != p.current;
        }

		iterator operator++(int) {
			Node *tmp = current;
			if (current)
				current = current->next();
			else
				throw "Iterator: out of bounds";
			return iterator(tmp);
		}

		iterator& operator++(){
            if (current)
                current = current->next();
            else
                throw "Iterator: out of bounds";
            return *this;
		}
		friend class AVLTree;
	};

	iterator begin() const {
		if (root)
			return iterator(root->minimum());
		return end();
	}
	iterator end() const {
		return iterator(nullptr);
	}

	class reverse_iterator{
		// TODO
	};
	reverse_iterator rbegin() const;
	reverse_iterator rend() const;

	iterator find(const T&) const;
	void erase(const iterator&);
};

template <typename T>
void AVLTree<T>::insert(const T& x){
	++count;
	if (root == nullptr){
		root = new Node(x);
		return;
	}
	Node *current = root;
	Node *p;
	bool toLeft = true;
	do{
		p = current;
		if (x < current->data){
			current = current->left;
			toLeft = true;
		} else {
			current = current->right;
			toLeft = false;
		}

	}while(current);

	current = new Node(x);
	current->parent = p;
	if (toLeft){
		p->left = current;
	} else {
		p->right = current;
	}
	// Восстановление баланса
	do {
		if (current->parent->left == current) current->parent->balance -= 1;
		else current->parent->balance += 1;
		current = current->parent;
		switch (current->balance){
		case 2:
			if (current->right->balance == -1)
					current = bigLeftRotate(current);
			else
					current = leftRotate(current);
			break;
		case -2:
            if (current->left->balance == 1)
                    current = bigRightRotate(current);
            else
                    current = rightRotate(current);
			break;
		}
	} while (current!=root && current->balance != 0);
}

template <typename T>
typename AVLTree<T>::iterator AVLTree<T>::find(const T& x) const {
	Node *current = root;
	while (current){
		if (x == current->data) break;
		if (x < current->data)
			current = current->left;
		else
			current = current->right;
	}
	return iterator(current);
}

template <typename T>
void AVLTree<T>::erase(const typename AVLTree<T>::iterator& pos){
	Node *toDelete = pos.current;
	if (toDelete == nullptr) return;
	Node *alt;
	if (toDelete->right == nullptr)
		alt = toDelete->left; // Надо не забыть, что не факт что слева кто-то есть
	else if (toDelete->left == nullptr)
		alt = toDelete->right;
	else {
		alt = toDelete->right->minimum(); // toDelete->next()
		if (alt->parent != toDelete){
			alt->parent->left = alt->right;
			if (alt->right) alt->right->parent = alt->parent;
			alt->right = toDelete->right;
			toDelete->right->parent = alt;
		}
		alt->left = toDelete->left;
		toDelete->left->parent = alt;
	}

	Node *notBalanced;
	if (alt == nullptr){
		// удаляется сам toDelete
		notBalanced = toDelete->parent;
		if (notBalanced != nullptr){
			if (notBalanced->left == toDelete)
				notBalanced->balance += 1;
			else
				notBalanced->balance -= 1;
		}
	} else {
		alt->balance = toDelete->balance;
		if (alt->parent == toDelete){
			notBalanced = alt;
			if (alt == toDelete->left)
				notBalanced->balance += 1;
			else
				notBalanced->balance -= 1;
		} else {
			notBalanced = alt->parent;
			notBalanced->balance += 1;
		}
	}


	// Разбираемся с родителем узла toDelete
	if (toDelete->parent == nullptr)
		root = alt;
	else {
		if (toDelete->parent->left == toDelete)
			toDelete->parent->left = alt;
		else
			toDelete->parent->right = alt;
	}
	if (alt!=nullptr) alt->parent = toDelete->parent;

	// Удаляем toDelete. Но! Вспоминаем, что декструктор рекурсивный!
	toDelete->right = nullptr;
	toDelete->left = nullptr;
	delete toDelete;

	while(notBalanced){
		switch(notBalanced->balance){
		case 2:
			if (notBalanced->right->balance == -1)
				notBalanced = bigLeftRotate(notBalanced);
			else
				notBalanced = leftRotate(notBalanced);
			break;
		case -2:
            if (notBalanced->left->balance == 1)
                notBalanced = bigRightRotate(notBalanced);
            else
                notBalanced = rightRotate(notBalanced);
            break;
		}
		if (notBalanced->balance == 1 || notBalanced->balance == -1)
			break;
		if (notBalanced->parent){
			if (notBalanced->parent->left == notBalanced)
				notBalanced->parent->balance += 1;
			else
				notBalanced->parent->balance -= 1;
		}
		notBalanced = notBalanced->parent;
	}


	--count;
}

template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::rightRotate(typename AVLTree<T>::Node * b){
	if (b->balance != -2) return b;
	Node * a = b->left;
	if (a->balance == 1) return b;

	b->left = a->right;
	if (a->right) a->right->parent = b;

	a->parent = b->parent;
	if (b->parent){
		if (b->parent->left == b)
			b->parent->left = a;
		else
			b->parent->right = a;
	} else {
		root = a;
	}

	a->right = b;
	b->parent = a;

	if (a->balance == -1){
		a->balance = 0;
		b->balance = 0;
	} else {
		a->balance = 1;
		b->balance = -1;
	}
	return a;
}

template <typename T>
typename AVLTree<T>::Node*  AVLTree<T>::bigRightRotate(typename AVLTree<T>::Node * c){
	if (c->balance != -2) return c;
	Node * a = c->left;
	if (a->balance !=1) return c;
	Node * b = a->right;

	a->right = b->left; if (b->left) b->left->parent = a;
	c->left = b->right; if (b->right) b->right->parent = c;

	b->parent = c->parent;
	if (c->parent){
		if (c->parent->left == c)
			c->parent->left = b;
		else
			c->parent->right = b;
	} else {
		root = b;
	}

	b->left = a; a->parent = b;
	b->right= c; c->parent = b;

	if (b->balance ==0){
		a->balance = 0; c->balance = 0;
	} else if (b->balance ==1){
		a->balance = -1; c->balance = 0;
	} else {
		a->balance =0; c->balance = 1;
	}
	b->balance = 0;
	return b;
}

template <typename T>
typename AVLTree<T>::Node*  AVLTree<T>::leftRotate(typename AVLTree<T>::Node * a){
	if (a->balance != 2) return a;
	Node * b = a->right;
	if (b->balance == -1) return a;

	a->right = b->left;
	if (b->left) b->left->parent = a;

	b->parent = a->parent;
	if (a->parent){
		if (a->parent->left == a)
			a->parent->left = b;
		else
			a->parent->right = b;
	} else {
		root = b;
	}

	b->left = a;
	a->parent = b;

	if (b->balance == 1){
		a->balance = 0;
		b->balance = 0;
	} else {
		a->balance = 1;
		b->balance =-1;
	}

	return b;
}

template <typename T>
typename AVLTree<T>::Node*  AVLTree<T>::bigLeftRotate(typename AVLTree<T>::Node * a){
    if (a->balance != 2) return a;
    Node * c = a->right;
    if (c->balance != -1) return a;
    Node * b = c->left;

    a->right = b->left; if (b->left) b->left->parent = a;
    c->left = b->right; if (b->right) b->right->parent = c;

    b->parent = a->parent;
    if (a->parent){
        if (a->parent->left == a)
            a->parent->left = b;
        else
            a->parent->right = b;
    } else {
        root = b;
    }

    b->left = a; a->parent = b;
    b->right= c; c->parent = b;

    if (b->balance ==0){
        a->balance = 0; c->balance = 0;
    } else if (b->balance ==1){
        a->balance = -1; c->balance = 0;
    } else {
        a->balance =0; c->balance = 1;
    }
    b->balance = 0;
    return b;
}
