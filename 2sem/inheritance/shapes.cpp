#include <iostream>

class Shape{
	unsigned int ID;
	static unsigned int lastID;
protected:
	unsigned int id() const {return ID;}
public:
	Shape() { ID = ++lastID; }
	virtual void show() const = 0;
	virtual void hide() const = 0;
	virtual ~Shape() {
		std::cout << "- delete shape " << ID <<std::endl;
	}
};

unsigned int Shape::lastID = 0;
// -----------------------------------------------------------
class Point : virtual public Shape{
protected:
	int x0, y0;
public:
	Point(int x, int y) : x0(x), y0(y) {
		std::cout << "+ create point. ";
		show();
	}
	void show() const {
		std::cout << "Show point . " << id()
				  << " (" << x0 << ", "<<y0<<")\n";
	}
    void hide() const {
		std::cout << "Hide point . " << id()
				  << " (" << x0 << ", "<<y0<<")\n";
	}
	void move(int dx, int dy) {
		x0 += dx;
		y0 += dy;
	}
	~Point() { hide(); }
};
// -----------------------------------------------------------
class Circle : virtual public Point {
	int R;
public:
	Circle(int x, int y, int r) : Point(x, y), R(r) {
		std::cout << "+ create circle. ";
		show();
	}
	void show() const {
		std::cout << "Show circle O " << id()
				  << " ("<< x0 <<", " << y0 << ", " << R << ")\n";
	}
    void hide() const {
        std::cout << "Hide circle O " << id()
                  << " ("<< x0 <<", " << y0 << ", " << R << ")\n";
    }
	~Circle() { hide(); }
};

// -----------------------------------------------------------
class Rectangle : virtual public Point {
    int w, h;
public:
    Rectangle(int x, int y, int width, int height) : Point(x, y), w(width), h(height) {
        std::cout << "+ create rectangle. ";
        show();
    }
    void show() const {
		if (w==h){
            std::cout << "Show square [] ";
		} else {
			std::cout << "Show rectangle [__] ";
		}
	    std::cout << id()
                  << " ("<< x0 - w/2 <<", " << y0 - h/2
				  << ", " << x0 + w/2 << ", "<< y0 + h/2 << ")\n";
    }
    void hide() const {
        if (w==h){
            std::cout << "Hide square [] ";
        } else {
            std::cout << "Hide rectangle [__] ";
        }
        std::cout << id()
                  << " ("<< x0 - w/2 <<", " << y0 - h/2
                  << ", " << x0 + w/2 << ", "<< y0 + h/2 << ")\n";
    }
    ~Rectangle() { hide(); }
};
// -----------------------------------------------------------
class Square : public Rectangle{
public:
	Square(int x, int y, int a) : Rectangle(x, y, a, a) {}
};
// -----------------------------------------------------------
class CircleInSquare : public Circle, public Square{
public:
	CircleInSquare(int x, int y, int r) : Circle(x,y,r), Square(x,y,2*r) {}
	void show() const { Circle::show(); Square::show(); }
	void hide() const { Square::hide(); Circle::hide(); }
};
// -----------------------------------------------------------

Shape* factory(){
	int x = rand()%80 + 10;
	int y = rand()%80 + 10;
	switch( rand()%5 ){
		case 1: return new Circle(x, y, rand()%10 + 1);
		case 2: return new Rectangle(x, y, 2*(rand()%7) + 12, 2*(rand()%5) + 2);
		case 3: return new Square(x, y, 2*(rand()%10) + 2);
		case 4: return new CircleInSquare(x, y, rand()%10 + 1);
	}
	return new Point(x, y);
}
// -----------------------------------------------------------

int main(){
	const int N = 10;
	Shape* World[N];

	std::cout << "================== Create World ================\n";
	for(int i = 0; i < N; ++i){
		World[i] = factory();
	}

	std::cout << "================== Show World ==================\n";
	for(int i = 0; i < N; ++i){
		World[i]->show();
	}

    std::cout << "================== Move objects ================\n";
    for(int i = 0; i < N; ++i){
        (dynamic_cast<Point*>(World[i]))->move(100, 100);
    }

    std::cout << "================== Show World ==================\n";
    for(int i = 0; i < N; ++i){
        World[i]->show();
    }

	std::cout << "================== Delete objects ===============\n";
	for(int i=0; i < N; ++i){
		delete World[i];
	}
	return 0;
}
