#include <iostream>

class Shape {
	unsigned int ID;
	static unsigned int counter;
	static unsigned int lastID;
protected:
	unsigned int id() const { return ID; }
public:
	Shape() { ID = ++lastID; ++counter; }
	virtual void show() const = 0;
	virtual void hide() const = 0;
	static unsigned int count() { return counter; }
	virtual ~Shape() {
		--counter;
		std::cout << "- delete shape" << std::endl;
	}
};

unsigned int Shape::counter = 0;
unsigned int Shape::lastID = 0;

void info() {
	std::cout << "------------- Total shapes: " << Shape::count() << std::endl;
}

class Point : public Shape {
protected:
	int x0, y0;
public:
	Point(int x, int y) : x0(x), y0(y) {
		std::cout << "+ create point. ";
		show();
	}
	virtual void show() const {
		std::cout << "Show point . #" << id() << " (" << x0 << ", " << y0 << ")\n";
	}
    virtual void hide() const {
        std::cout << "Hide point . #" << id() << "(" << x0 << ", " << y0 << ")\n";
    }
	virtual ~Point() { hide(); }
};

class Circle : public Point {
	int R;
public:
	Circle(int x, int y, int r) : Point(x, y), R(r) {
		std::cout << "+ create circle O ";
		show();
	}
    void show() const {
        std::cout << "Show circle O #" << id() << " (" << x0 << ", " << y0 << ", " << R << ")\n";
    }
    void hide() const {
        std::cout << "Hide circle O #" << id() << " (" << x0 << ", " << y0 << ", " << R << ")\n";
    }
	~Circle() { hide(); }
};

Shape* factory() {
	int x = rand()%80 + 10;
	int y = rand()%80 + 10;
	switch(rand()%2){
	case 1: return new Circle(x, y, 1 + rand()%10);
	}
	return new Point(x, y);
}

int main() {
/*
	Point A(5, 7);
	A.show();
	Circle C(2, 6, 3);
	C.show();
*/
	info();

	const int N = 10;
	Shape* World[N];

	std::cout << "================= Create World =================\n";
	for(int i = 0; i < N; ++i) {
		World[i] = factory();
	}

	info();

	std::cout << "=================  Show World  =================\n";
	for(int i = 0; i < N; ++i) {
		World[i] -> show();
	}

	info();

//    std::cout << "================= Move objects  =================\n";

	std::cout << "================= Delete objects =================\n";
    for(int i = 0; i < N; ++i) {
        delete World[i];
    }

	info();

	return 0;
}
