#pragma once

template <typename T>
class Array{
	T* data_;
	size_t size_;
	size_t maxsize_;
	bool is_Sorted_;
	void swap(Array& other){
		std::swap(data_, other.data_);
		std::swap(size_, other.size_);
		std::swap(is_Sorted_, other.is_Sorted_);
		std::swap(maxsize_, other.maxsize_);

	}
	void QuickSort(T*, size_t);
public:
	Array(size_t N = 0): size_(0), maxsize_(N), data_(new T[N]), is_Sorted_(true) {}
	~Array() { delete[] data_; }
	Array(const Array&);
	Array(Array&&);
	size_t size()const {return size_;}
	size_t capacity()const {return maxsize_;}
	Array& operator=(const Array&);
	Array& operator=(Array&&);
	void push_back(const T&);
	const T& operator[](size_t index){
		if (index>=size_){
			throw "Out of limits";
		}
		return data_[index];
	}
	void sort() { QuickSort(data_, size_); is_Sorted_=true; }

	class iterator {
		T* current;
	public:
		iterator(T *p=nullptr) : current(p) {}
		T& operator*() {return *current;}
		const T& operator*() const {return *current;}
		bool operator!=(const iterator& other) const {return current!=other.current;}
		bool operator==(const iterator& other) const {return current==other.current;}
		iterator& operator++() { ++current; return *this;}  // ++pos
		iterator operator++(int) {  // pos++
			T* tmp=current;
			++current;
			return iterator(tmp);
		}
	};
	iterator begin() const {return iterator(data_);}
	iterator end() const {return iterator(data_+size_);}


	class reverse_iterator {
		T* current;
	public:
		reverse_iterator(T *p=nullptr) : current(p) {}
		T& operator*() {return *current;}
		const T& operator*() const {return *current;}
		bool operator!=(const reverse_iterator& other) const {return current!=other.current;}
		bool operator==(const reverse_iterator& other) const {return current==other.current;}
		reverse_iterator& operator++() { --current; return *this;}  // ++pos
		reverse_iterator operator++(int) {  // pos++
			T* tmp=current;
			--current;
			return reverse_iterator(tmp);
		}
	};
	reverse_iterator rbegin() const {return reverse_iterator(data_+size_-1);}
	reverse_iterator rend() const {return reverse_iterator(data_-1);}

	iterator find(const T&) const;
};

template <typename T>
Array<T>::Array(const Array<T>& other){
	maxsize_ = other.size_;
	size_ = other.size_;
	is_Sorted_ = other.is_Sorted_;
	data_ = new T[size_];
	for(size_t i=0; i<size_; ++i){
		data_[i] = other.data_[i];
	}
}

template <typename T>
Array<T>::Array(Array<T>&& other){
	size_ = 0;
	maxsize_ = 0;
	is_Sorted_ = true;
	data_ = nullptr;
	swap(other);
}

template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& other){
	if (this != &other){
		/*delete[] data_;
		data_ = new T[other.size_];
		maxsize_ = other.size_;
		size_ = other.size_;
		for(size_t i=0; i<size_; ++i){
			data_[i] = other.data_[i];
		}
		*/
		Array<T> tmp(other);
		swap(tmp);
	}
	return *this;
}

template <typename T>
Array<T>& Array<T>::operator=(Array<T>&& other){
	if (this != &other){
		swap(other);
	}
	return *this;
}

template <typename T>
void Array<T>::push_back(const T& X){
	if (size_+1 > maxsize_){
		if (maxsize_<20){
			++maxsize_;
		} else {
			//maxsize_ += 100;
			//maxsize_ = (unsigned int)(maxsize_ * 1.1);
			maxsize_ *= 2;
		}
		T* tmp = new T[maxsize_];
		for(size_t i=0; i<size_; ++i){
			tmp[i] = std::move(data_[i]);
		}
		delete[] data_;
		data_ = tmp;
	}
	data_[size_] = X;
	++size_;
	is_Sorted_ = false;
}

template <typename T>
void Array<T>::QuickSort(T* M, size_t n){
	if (n<2) return;
	size_t i = 0, j = n-1;
	T pivot = M[rand()%n];
	while(i<j){
		while(M[i]<pivot) ++i;
		while(pivot<M[j]) --j;
		if (i<j){
			std::swap(M[i], M[j]);
			++i; --j;
		} else if (i==j){
			++i; 
			if (j) --j;
			else break;
		}
	}
	
	if (j < n-j){
		if (j>0) QuickSort(M, j+1);
		if (i<n-1) QuickSort(M+i, n-i);
	} else {
		if (i<n-1) QuickSort(M+i, n-i);
		if (j>0) QuickSort(M, j+1);
	}
}

template <typename T>
typename Array<T>::iterator Array<T>::find(const T& X) const {
	if (is_Sorted_){
		if (size_==0) return end();
		size_t left=0, right =size_-1;
		size_t p;
		while(left<right){
			p = left + (right-left)/2;
			if (data_[p] < X)
				left = p+1;
			else if (data_[p]==X)
				return iterator(data_+p);
			else if (p==0) break;
			else right = p-1;
		}
		if (data_[left]==X) return iterator(data_+left);
	}else {
		for(size_t i=0; i<size_; ++i){
			if (data_[i] == X)
				return iterator(data_+i);
		}
	}
	return end();
}
