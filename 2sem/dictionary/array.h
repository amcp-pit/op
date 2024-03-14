#pragma once

template <typename T>
class Array{
	T* data_;
	size_t size_;
	size_t maxsize_;
	void swap(Array& other){
		std::swap(data_, other.data_);
		std::swap(size_, other.size_);
		std::swap(maxsize_, other.maxsize_);
	}
public:
	Array(size_t N = 0): size_(0), maxsize_(N), data_(new T[N]){}
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
};

template <typename T>
Array<T>::Array(const Array<T>& other){
	maxsize_ = other.size_;
	size_ = other.size_;
	data_ = new T[size_];
	for(size_t i=0; i<size_; ++i){
		data_[i] = other.data_[i];
	}
}

template <typename T>
Array<T>::Array(Array<T>&& other){
	size_ = 0;
	maxsize_ = 0;
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
}
