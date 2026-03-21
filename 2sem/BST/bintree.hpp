#ifndef _BINTREE_26_
#define _BINTREE_26_

template <typename T>
class BinTree{
	struct Node {
		Node *left;
		Node *right;
		Node *parent;
		T data;
		Node(const T& x) : left(nullptr), right(nullptr), parent(nullptr), data(x) {}
		~Node() {
			delete left;
			delete right;
		}
		Node(const Node&) = delete;
		Node& operator=(const Node&) = delete;
		size_t height() const {
			size_t L = (left==nullptr) ? 0 : left->height();
			size_t R = (right==nullptr)? 0 : right->height();
			return (R < L) ? L+1 : R+1;
		}
		Node* minimum() {
			Node *current = this;
			while(current->left){
				current = current->left;
			}
			return current;
		}
		Node* next() {
			if (right) {
				return right->minimum();
			}
			Node* current = this;
			Node* p = parent;
			while (p) {
				if (current == p->left){
					break;
				}
				current = p;
				p = p->parent;
			}
			return p;
		}

	};
	Node * root;
	size_t count;
public:
	BinTree() : root(nullptr), count(0) {}
	~BinTree() { empty(); }
	void empty() { delete root; root = nullptr; count = 0; }
	void insert(const T& x);
	size_t size() const { return count; }
	size_t height() const { return root->height(); }

	class iterator {
		Node * current;
		iterator(Node * p = nullptr) : current (p) {}
	public:
		T& operator*() const { return current->data; }
		bool operator== (const iterator& other) const {
			return current == other.current;
		}
        bool operator!= (const iterator& other) const {
            return current != other.current;
        }
		iterator& operator++() {
			if (current) {
				current = current->next();
			} else {
				throw "iterator: out of bounds";
			}
			return *this;
		}
		iterator operator++(int) {
			Node* tmp = current;
            if (current) {
                current = current->next();
            } else {
                throw "iterator: out of bounds";
            }
			return iterator(tmp);
		}
		friend class BinTree;
	};
	iterator begin() const {
		if (root) {
			return iterator(root->minimum());
		}
		return end();
	}
	iterator end() const {
		return iterator(nullptr);
	}
};


template <typename T>
void BinTree<T>::insert(const T& x) {
	++count;
	if (root == nullptr) {
		root = new Node(x);
		return;
	}
	Node * current = root;
	Node * parent;
	bool toLeft = true;
	do {
		parent = current;
		if (x < current->data) {
			current = current->left;
			toLeft = true;
		} else {
			current = current->right;
			toLeft = false;
		}
	} while(current != nullptr);

	current = new Node(x);
	current->parent = parent;

	if (toLeft) {
		parent->left = current;
	} else {
		parent->right= current;
	}
}

#endif
