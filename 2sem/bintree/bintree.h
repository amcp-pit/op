#pragma once
#include <iostream>

template <typename T>
class BinTree{
	struct Node{
		Node *left, *right, *parent;
		T data;
		Node(const T& x): left(nullptr), right(nullptr), parent(nullptr), data(x){}

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

		void print() const {
			if (left) left->print();
			std::cout << data <<", ";
			if (right) right->print();
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
	Node *root;
	size_t count;
public:
	BinTree() : root(nullptr), count(0) {}
	~BinTree() {clear();}
	void clear() {delete root; root=nullptr; count=0;}
	void empty() {clear();}
	size_t size() const {return count;}
	void insert(const T&);
	int height() const { return root->height(); }
	void print()const {root->print(); }

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
		friend class BinTree;
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
void BinTree<T>::insert(const T& x){
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
}

template <typename T>
typename BinTree<T>::iterator BinTree<T>::find(const T& x) const {
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
void BinTree<T>::erase(const typename BinTree<T>::iterator& pos){
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

	--count;
}


