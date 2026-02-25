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

class Point : virtual public Shape {
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
	void move(int dx, int dy) {
		x0 += dx;
		y0 += dy;
	}
	virtual ~Point() { hide(); }
};

class Circle : virtual public Point {
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

class Rectangle : virtual public Point {
	int width_, height_;
public:
	Rectangle(int x, int y, int width, int height) : Point(x, y), height_(height), width_(width) {
		std::cout << "+ create rectangle. ";
		show();
	}
	void show() const {
		if (width_ == height_) {
			std::cout << "Show square [] ";
		} else {
			std::cout << "Show rectangle [___] ";
		}
		std::cout << "#" << id() << " ("
				  << x0-width_/2 << ", " << y0-height_/2 << ", "
				  << x0+width_/2 << ", " << y0+height_/2 << ")\n";
	}
	void hide() const {
        if (width_ == height_) {
            std::cout << "Hide square [] ";
        } else {
            std::cout << "Hide rectangle [___] ";
        }

        std::cout << "#" << id() << " ("
                  << x0-width_/2 << ", " << y0-height_/2 << ", "
                  << x0+width_/2 << ", " << y0+height_/2 << ")\n";
	}
	~Rectangle() { hide(); }
};

class Square : public Rectangle {
public:
	Square(int x, int y, int a) : Point(x, y), Rectangle(x, y, a, a) {}
};

class CircleInSquare : public Circle, public Square {
public:
	CircleInSquare(int x, int y, int r) : Point(x, y), Circle(x, y, r), Square(x, y, 2*r) {}
	void show() const { Circle::show(); Square::show(); }
	void hide() const { Square::hide(); Circle::hide(); }
};

Shape* factory() {
	int x = rand()%80 + 10;
	int y = rand()%80 + 10;
	switch(rand()%5){
	case 1: return new Circle(x, y, 1 + rand()%10);
	case 2: return new Rectangle(x, y, 2*(12+rand()%10), 2*(2+rand()%5));
	case 3: return new Square(x, y, 2*(2+rand()%10));
	case 4: return new CircleInSquare(x, y, 1+rand()%10);
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

    std::cout << "================= Move objects  =================\n";
    for(int i = 0; i < N; ++i) {
		(dynamic_cast<Point*>(World[i]))->move(10, 10);
	}

    std::cout << "=================  Show World  =================\n";
    for(int i = 0; i < N; ++i) {
        World[i] -> show();
    }

    info();

	std::cout << "================= Delete objects =================\n";
    for(int i = 0; i < N; ++i) {
        delete World[i];
    }

	info();
	std::cout << "sizeof(int) = " << sizeof(int) <<std::endl;
    std::cout << "sizeof(int*) = " << sizeof(int*) <<std::endl;
	std::cout << "sizeof(Point) = " << sizeof(Point) << std::endl;
    std::cout << "sizeof(Circle) = " << sizeof(Circle) << std::endl;
    std::cout << "sizeof(Rectangle) = " << sizeof(Rectangle) << std::endl;
    std::cout << "sizeof(Square) = " << sizeof(Square) << std::endl;
    std::cout << "sizeof(CircleInSquare) = " << sizeof(CircleInSquare) << std::endl;


	return 0;
}
