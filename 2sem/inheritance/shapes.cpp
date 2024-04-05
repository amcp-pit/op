#include <iostream>

class Shape{
	unsigned int ID;
	static unsigned int lastID;
	static int counter;
protected:
	unsigned int id() const {return ID;}
public:
	Shape(){++counter; ID = ++lastID;}
	static int count() {return counter;}
	virtual void show() const = 0; // pure virtual
	virtual void hide() const = 0; // pure virtual
	virtual ~Shape(){
		--counter;
		std::cout<<"- delete shape"<<std::endl;
	}
};

int Shape::counter = 0;
unsigned int Shape::lastID = 0;

class Point : virtual public Shape{
protected:
	int x0, y0; 
public:
	Point(int x, int y) : x0(x), y0(y){
		std::cout << "+ create point. ";
		show();
	}
	virtual void show() const {std::cout<< "Show point . "<<id()<<" (" << x0 <<", "<<y0<<")\n";}
	virtual void hide() const {std::cout<< "Hide point . "<<id()<<" (" << x0 <<", "<<y0<<")\n";}
	void move(int dx, int dy) { x0+=dx; y0+=dy; }
	virtual ~Point() { hide(); }
};

class Circle : virtual public Point {
	int R;
	static int counter;
public:
	Circle(int x, int y, int r) : Point(x, y), R(r) {
		++counter;
		std::cout << "+ create circle. ";
		show();
	}
	static int count() {return counter;}
	virtual void show() const {std::cout<< "Show circle O "<<id()<<" (" << x0 <<", "<<y0<<", "<<R<<")\n";}
	virtual void hide() const {std::cout<< "Hide circle O "<<id()<<" (" << x0 <<", "<<y0<<", "<<R<<")\n";}
	virtual ~Circle() { hide(); --counter;}
};
int Circle::counter = 0;

class Rectangle : virtual public Point {
	int w, h;
public:
	Rectangle(int x, int y, int width, int height) : Point(x, y), w(width), h(height) {
		std::cout << "+ create rectangle. ";
		show();
	}
	virtual void show() const {
		if (w==h){
			std::cout << "Show square [] ";
		} else {
			std::cout << "Show rectangle [____] ";
		}
		std::cout<< id() << " (" << x0-w/2 <<", "<<y0-h/2<<", "<<x0+w/2<<", "<<y0+h/2<<")\n";
	}
	virtual void hide() const {
		if (w==h){
			std::cout << "Hide square [] ";
		} else {
			std::cout << "Hide rectangle [____] ";
		}
		std::cout<< id()<< " (" << x0-w/2 <<", "<<y0-h/2<<", "<<x0+w/2<<", "<<y0+h/2<<")\n";
	}
	virtual ~Rectangle() { hide(); }
};

class Square : public Rectangle {
public:
	Square(int x, int y, int a) : Point(x,y), Rectangle(x, y, a, a) {}
};

class CircleInSquare : public Circle, public Square {
public:
	CircleInSquare(int x, int y, int r) : Point(x,y), Circle(x,y,r), Square(x,y,2*r){}
	void show() const {Circle::show(); Square::show();}
	void hide() const {Circle::hide(); Square::hide();}
};

Shape* factory(){
	int x = rand()%80+10;
	int y = rand()%80+10;
	switch(rand()%5){
	case 0: return new Circle(x, y, rand()%10+1);
	case 1: return new Rectangle(x, y, 2*(rand()%7)+12, 2*(rand()%5)+2);
	case 2: return new Square(x, y, rand()%10+2);
	case 3: return new CircleInSquare(x, y, rand()%10+1);
	}
	return new Point (x, y);
}

void info(){
	std::cout << "----------- Total shapes: " << Shape::count() << std::endl;
	std::cout << "----------- Total circles: " << Circle::count() << std::endl;
}

int main(){
	const int N=10;
	Shape* world[N];
	std::cout<< "================ Create world ==================\n";
	for(int i=0; i<N; ++i) 
		world[i] = factory();
	info();
	std::cout<< "\n================ Show world ====================\n";
	for(int i=0; i<N; ++i) 
		world[i]->show();

	std::cout<< "\n================ Move objects ====================\n";
	for(int i=0; i<N; ++i) 
		(dynamic_cast<Point*>(world[i]))->move(100, 100);

	std::cout<< "\n================ Show world ====================\n";
	for(int i=0; i<N; ++i) 
		world[i]->show();

	std::cout<< "\n================ Delete world ==================\n";
	for(int i=0; i<N; ++i) 
		delete world[i];
	info();
	return 0;
}