#pragma once

template <typename T>
class BinTree{
	struct Node{
		Node *left, *right, *parent;
		T data;
		Node(const T& X): left(nullptr), right(nullptr), parent(nullptr), data(X) {}
		~Node(){
			delete left;
			delete right;
		}
		size_t height() const {
			size_t L = (left==nullptr) ? 0 : left->height();
			size_t R = (right==nullptr) ? 0 : right->height();
			return R<L ? L+1 : R+1;
		}
		Node* minimum() {
			Node* now = this;
			while(now->left != nullptr){
				now = now->left;
			}
			return now;
		}
		Node* maximum(){
			Node* now = this;
			while(now->right != nullptr){
				now = now->right;
			}
			return now;
		}
		Node* next() {
			if (right!=nullptr)
				return right->minimum();
			Node * now = this;
			Node * p = parent;
			while (p!=nullptr){
				if (now == p->left)
					break;
				now = p;
				p = now->parent;
			}
			return p;
		}

		Node* prev(){
			if (left!=nullptr)
				return left->maximum();
			Node* now = this;
			Node* p = parent;
			while(p != nullptr){
				if (now == p->right)
					break;
				now = p;
				p = now->parent;
			}
			return p;
		}

	};
	Node* root;
	size_t count;
public:
	BinTree(): root(nullptr), count(0) {}
	~BinTree() {clear();}
	void clear(){
		delete root;
		root=nullptr; 
		count=0;
	}
	void empty() {clear();}
	size_t size() const {return count;}
	size_t height() const {return root->height();}
	void insert(const T&);

	class iterator{
		Node * current;
	public:
		iterator(Node *p=nullptr): current(p) {}
		const T& operator*() const {return current->data;}
		bool operator==(const iterator& p) const {return current==p.current;}
		bool operator!=(const iterator& p) const {return current!=p.current;}
		iterator& operator++(){
			if (current)
				current = current->next();
			else 
				throw "Iterator: out of bounds";
			return *this;
		}
		iterator operator++(int){
			Node * tmp = current;
			if (current)
				current = current->next();
			else 
				throw "Iterator: out of bounds";
			return iterator(tmp);
		}
		friend class BinTree;
	};
	iterator begin() const { 
		if (root!=nullptr) 
			return iterator(root->minimum());
		return end();
	}
	iterator end() const { return iterator(nullptr); }

	class reverse_iterator{
		Node * current;
	public:
		reverse_iterator(Node *p=nullptr): current(p) {}
		const T& operator*() const {return current->data;}
		bool operator==(const reverse_iterator& p) const {return current==p.current;}
		bool operator!=(const reverse_iterator& p) const {return current!=p.current;}
		reverse_iterator& operator++(){
			if (current)
				current = current->prev();
			else 
				throw "Iterator: out of bounds";
			return *this;
		}
		reverse_iterator operator++(int){
			Node * tmp = current;
			if (current)
				current = current->prev();
			else 
				throw "Iterator: out of bounds";
			return reverse_iterator(tmp);
		}
	};
	reverse_iterator rbegin() const { 
		if (root!=nullptr) 
			return reverse_iterator(root->maximum());
		return rend();
	}
	reverse_iterator rend() const { return reverse_iterator(nullptr); }

	iterator find(const T&) const;
	void erase(const iterator&);

	void balance();
};

template <typename T>
void BinTree<T>::insert(const T& X){
	++count;
	if (root==nullptr){
		root = new Node(X);
		return;
	}

	Node *now = root;
	Node * p; 
	do {
		p = now;
		if (X < now->data){
			now = now->left;
		} else {
			now = now->right;
		}
	} while(now);

	now = new Node(X);
	now->parent = p;
	if (X < p->data){
		p->left = now;
	} else {
		p->right = now;
	}
}

template <typename T>
typename BinTree<T>::iterator BinTree<T>::find(const T& X) const{
	Node* now = root;
	while(now){
		if (X == now->data) break;
		if (X < now->data)
			now = now->left;
		else
			now = now->right;
	}
	return iterator(now);
}

template <typename T>
void BinTree<T>::erase(typename const BinTree<T>::iterator& pos){
	Node* toDelete = pos.current;
	if (toDelete == nullptr) return;
	Node* alt;
	if (toDelete->right == nullptr)
		alt = toDelete->left;
	else if (toDelete->left == nullptr)
		alt = toDelete->right;
	else {
		alt = toDelete->right->minimum();
		if (alt->parent != toDelete){
			alt->parent->left = alt->right;
			if(alt->right) alt->right->parent = alt->parent;
			alt->right = toDelete->right;
			toDelete->right->parent = alt; 
		}
		alt->left = toDelete->left;
		toDelete->left->parent = alt;
	}
	// Разберемся с родителями узла toDelete
	if (toDelete->parent==nullptr){
		root = alt;
	} else {
		if (toDelete->parent->left == toDelete)
			toDelete->parent->left = alt;
		else 
			toDelete->parent->right = alt;
	}
	if(alt!=nullptr) alt->parent = toDelete->parent;

	// Удаляем toDelete, но вспоминаем, что деструктор рекурсивный!
	toDelete->left=nullptr;
	toDelete->right=nullptr;
	delete toDelete;
	--count;
}


template <typename T>
void BinTree<T>::balance(){
	if (root == nullptr)
		return;
	// Вытянуть в лозу (левоассоциативное дерево)
	Node *p, *r, *q;
	p = root;
	while(p!=nullptr){
		if (p->right == nullptr)
			p = p->left;
		else {
			r = p->right;
			q = p->parent;
			if (q) q->left = r; else root = r;
			r->parent = q;
			p->right = r->left;
			if (r->left) r->left->parent = p;
			r->left = p;
			p->parent = r;
			p = r;
		}
	}
	// Сломать "лишнее"
	int n = 0, n2=1;
	for(int i=count+1; i>1; ++n, n2<<=1, i>>=1);
	int Lishnee = count-(n2-1);
//	int Lishnee = count-((1<<n)-1);
	Node *red, *black;
	red = root;
	while(Lishnee>0){
		black = red->left;
		black->right = red;
		black->parent = red->parent;
		if (red->parent) red->parent->left = black;
		else root = black;
		red->parent = black;
		red->left = nullptr;
		--Lishnee;
		red = black->left;
	}
	// Ломать лозу с 2^n-1 узлами
	int blackInStep = (n2-1)/2;
	for(int step = 1; step < n; ++step, blackInStep/=2){
		red = root;
		for(int i=0; i<blackInStep; ++i){
			black = red->left;

			black->parent = red->parent;
			if (red->parent) red->parent->left = black;
			else root = black;

			red->left = black->right;
			if (black->right) black->right->parent = red;

			black->right = red;
			red->parent = black;

			red = black->left;
		}
	}
}
