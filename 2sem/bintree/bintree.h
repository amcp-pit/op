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
