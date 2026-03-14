#ifndef _MY_ARRAY_26_
#define _MY_ARRAY_26

template <typename T>
class Array {
	size_t size_;
	size_t maxsize_;
	T* data_;
	void swap(Array<T> & other) noexcept {
		std::swap(size_, other.size_);
		std::swap(maxsize_, other.maxsize_);
		std::swap(data_, other.data_);
	}
public:
	Array(size_t N = 0) : size_(0), maxsize_(N), data_(new T[N]) {}
	~Array() { delete[] data_; }

	Array(const Array& other) : size_(other.size_), maxsize_(other.maxsize_), data_(new T[maxsize_]) {
		for(size_t i = 0; i < size_; ++i) {
			data_[i] = other.data_[i];
		}
	}

    Array& operator= (const Array& other) {
		if (this != &other){
			Array<T> tmp(other);
			swap(tmp);
		}
		return *this;
	}

#ifndef NOMOVESEMANTICS
	Array(Array&& other) noexcept : size_(0), maxsize_(0), data_(nullptr) {
		swap(other);
        std::cout << "ms ctor array\n";
	}

    Array& operator= (Array&& other) {
		if (this != &other) {
			swap(other);
		}
		std::cout << "ms operator = array\n";
		return *this;
	}
#endif

	size_t size() const { return size_; }
	size_t capacity() const { return maxsize_; }

	void push_back(const T&);

	const T& operator[] (size_t index) const {
		if (index >= size_) {
			throw std::out_of_range("Out of array limits");
		}
		return data_[index];
	}

	size_t find(const T& x) const;
};


template <typename T>
void Array<T>::push_back(const T& X) {
	if (size_ + 1 > maxsize_) {
		//maxsize_ += 2;
		//maxsize_ = (maxsize_ < 20) ? maxsize_ + 1 : static_cast<size_t>(maxsize_ * 1.1);
		maxsize_ = (maxsize_ < 2) ? 2 : 2 * maxsize_;
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

template <typename T>
size_t Array<T>::find(const T& x) const {
	for(size_t i = 0; i < size_; ++i) {
		if (x == data_[i]) {
			return i;
		}
	}
	return -1;
}

#endif
