#pragma once

template <typename T>
class Array{
	T* data_;
	size_t size_;
	size_t maxsize_;
	bool isSorted;
	void swap(Array<T> &other) noexcept {
		std::swap(size_, other.size_);
		std::swap(maxsize_, other.maxsize_);
		std::swap(data_, other.data_);
		std::swap(isSorted, other.isSorted);
	}
	void QuickSort_(T*, size_t);
public:
	Array(size_t N = 0): size_(N), maxsize_(N), data_(new T[N]), isSorted(false) {}
	~Array() { delete[] data_; }
	Array(const Array&);
	Array(Array&& other) noexcept : size_(0), maxsize_(0), data_(nullptr){ swap(other); }
	Array& operator=(const Array& other) {
		if (this!=&other){
			Array<T> tmp(other);
			swap(tmp);
		}
		return *this;
	}
	Array& operator=(Array&& other) noexcept {
		if (this!=&other){
			swap(other);
		}
		return *this;
	}
	size_t size() const { return size_; }
	size_t capacity() const { return maxsize_; }
	void push_back(const T&);
	const T& operator[] (size_t index) const {
		if (index >= size_){
			throw "Out of bounds";
		}
		return data_[index];
	}

	class iterator {
		T* current;
	public:
		iterator(T *p=nullptr) : current(p) {}
		T& operator*() { return *current; }
		const T& operator*() const { return *current; }
		bool operator==(const iterator& other) const {
			return current == other.current;
		}
        bool operator!=(const iterator& other) const {
            return current != other.current;
        }
		iterator& operator++() { ++current; return *this; } // ++pos
		iterator operator++(int) { // pos++
			T* tmp = current;
			++current;
			return iterator(tmp);
		}
	};
	iterator begin() const { return iterator(data_); }
	iterator end() const { return iterator(data_ + size_); }

	class reverse_iterator{
        T* current;
    public:
        reverse_iterator(T *p=nullptr) : current(p) {}
        T& operator*() { return *current; }
        const T& operator*() const { return *current; }
        bool operator==(const reverse_iterator& other) const {
            return current == other.current;
        }
        bool operator!=(const reverse_iterator& other) const {
            return current != other.current;
        }
        reverse_iterator& operator++() { --current; return *this; } // ++pos
        reverse_iterator operator++(int) { // pos++
            T* tmp = current;
            --current;
            return reverse_iterator(tmp);
        }
	};
	reverse_iterator rbegin() const { return reverse_iterator(data_ + size_ - 1); }
	reverse_iterator rend() const { return reverse_iterator(data_ - 1); }

	iterator find(const T& x)const;
	void sort() { QuickSort_(data_, size_); isSorted = true; }
};

template <typename T>
Array<T>::Array(const Array<T>& other){
	maxsize_ = other.size_;
	size_ = other.size_;
	data_ = new T[maxsize_];
	for(size_t i = 0; i < size_; ++i){
		data_[i] = other.data_[i];
	}
	isSorted = other.isSorted;
}
/*
template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& other){
	if (this != &other){
		delete[] data_;
	    maxsize_ = other.size_;
		size_ = other.size_;
    	data_ = new T[maxsize_];
    	for(size_t i = 0; i < size_; ++i){
        	data_[i] = other.data_[i];
    	}
	}
	return *this;
}
*/
template <typename T>
void Array<T>::push_back(const T& X){
	if (size_+1 > maxsize_){
		//maxsize_ = (maxsize_<20) ? maxsize_+1 : static_cast<size_t>(maxsize_*1.1);
		// maxsize_ += 100;
		maxsize_ = (maxsize_ < 2) ? 2 : 2 * maxsize_;
		T* tmp = new T[maxsize_];
        for(size_t i = 0; i < size_; ++i){
            tmp[i] = std::move(data_[i]);
        }
		delete[] data_;
		data_ = tmp;
	}
	data_[size_] = X;
	++size_;
	isSorted = false;
}

template <typename T>
typename Array<T>::iterator Array<T>::find(const T& x)const{
	if (isSorted){
		if (size_==0) return end();
		size_t left=0, right = size_-1;
		size_t p;
		while(left<right){
			p = left + (right-left)/2;
			if (data_[p] < x)
				left = p+1;
			else if (data_[p] == x)
				return iterator(data_ + p);
			else if (p == 0) break;
			else right = p - 1;
		}
		if (data_[left] == x) return iterator(data_+left);
	} else {
		for(size_t i=0; i<size_; ++i){
			if (data_[i] == x)
				return iterator(data_+i);
		}
	}
	return end();
}

template <typename T>
void Array<T>::QuickSort_(T* M, size_t n){
	if(n<2) return;
	size_t left=0, right=n-1;
	T pivot = M[rand()%n];
	while(left<right){
		while(M[left] < pivot) ++left;
		while(pivot < M[right]) --right;
		if (left < right){
			std::swap(M[left], M[right]);
			++left; --right;
		} else if (left==right){
			++left;
			if (right) --right;
			else break;
		}
	}
	if (right < n-right){
		if (right>0) QuickSort_(M, right+1);
		if (left < n-1) QuickSort_(M+left, n-left);
	} else {
       if (left < n-1) QuickSort_(M+left, n-left);
       if (right>0) QuickSort_(M, right+1);
	}
}

