#pragma once

template <typename T>
class Array{
	T* data_;
	size_t size_;
	size_t maxsize_;
	void swap(Array<T> &other){
		std::swap(size_, other.size_);
		std::swap(maxsize_, other.maxsize_);
		std::swap(data_, other.data_);
	}
public:
	Array(size_t N = 0): size_(N), maxsize_(N), data_(new T[N]) {}
	~Array() { delete[] data_; }
	Array(const Array&);
	Array(Array&& other): size_(0), maxsize_(0), data_(nullptr){
		swap(other);
	}
	Array& operator=(const Array& other) {
		if (this!=&other){
			Array<T> tmp(other);
			swap(tmp);
		}
		return *this;
	}
	Array& operator=(Array&& other){
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
};

template <typename T>
Array<T>::Array(const Array<T>& other){
	maxsize_ = other.size_;
	size_ = other.size_;
	data_ = new T[maxsize_];
	for(size_t i = 0; i < size_; ++i){
		data_[i] = other.data_[i];
	}
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
}