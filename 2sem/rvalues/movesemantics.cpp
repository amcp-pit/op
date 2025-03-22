#include <iostream>
#include <chrono>


template <class T>
class MyArray
{
private:
	T* array_;
	int length_;
public:
	MyArray(int length) : array_(new T[length]), length_(length)
	{
	}

	~MyArray()
	{
		delete[] array_;
	}

#if 1
	// Конструктор копирования
	MyArray(const MyArray& arr)	: length_(arr.length_)
	{
		array_ = new T[length_];
		for (int i = 0; i < length_; ++i)
			array_[i] = arr.array_[i];
	}

	// Оператор присваивания копированием
	MyArray& operator=(const MyArray& arr)
	{
		if (&arr != this) {
			delete[] array_;

			length_ = arr.length_;
			array_ = new T[length_];

			for (int i = 0; i < length_; ++i)
				array_[i] = arr.array_[i];
		}
		return *this;
	}
#else
	// Конструктор копирования
	MyArray(const MyArray& arr) = delete;

	// Оператор присваивания копированием
	MyArray& operator=(const MyArray& arr) = delete;

	// Конструктор перемещения
	MyArray(MyArray&& arr) noexcept : length_(arr.length_), array_(arr.array_)
	{
		arr.length_ = 0;
		arr.array_ = nullptr;
	}

	// Оператор присваивания перемещением
	MyArray& operator=(MyArray&& arr) noexcept
	{
		if (&arr != this) {
			delete[] array_;

			length_ = arr.length_;
			array_ = arr.array_;

			arr.length_ = 0;
			arr.array_ = nullptr;
		}
		return *this;
	}
#endif

	int getLength() const { return length_; }
	T& operator[](int index) { return array_[index]; }
	const T& operator[](int index) const { return array_[index]; }

};

class Timer
{
private:
	// Используем псевдонимы типов для удобного доступа к вложенным типам
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<clock_t> begin_;
public:
	Timer() : begin_(clock_t::now())	{	}
	void reset() { begin_ = clock_t::now();	}
	double elapsed() const{ return std::chrono::duration_cast<second_t>(clock_t::now() - begin_).count(); }
};

// Возвращаем копию arr со значениями, умноженными на 2
MyArray<int> cloneArrayAndDouble(const MyArray<int>& arr) {
	MyArray<int> dbl(arr.getLength());
	for (int i = 0; i < arr.getLength(); ++i)
		dbl[i] = arr[i] * 2;

	return dbl;
}

int main() {
	Timer t;

	MyArray<int> arr(50'000'000);

	for (int i = 0; i < arr.getLength(); i++)
		arr[i] = i;

	arr = cloneArrayAndDouble(arr);

	std::cout << t.elapsed() << std::endl;
}
