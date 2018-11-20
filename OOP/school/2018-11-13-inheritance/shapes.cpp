#include <iostream>
#include <cmath>
#include <vector>

using namespace std;
class RectangleException{};
class TriangleException{};


class Point{
    private:
        double x_, y_;
    public:
        Point(double x = 0.0, double y=0.0) : x_(x), y_(y) {}
        double get_x() const{
            return x_;
        }
        double get_y() const{
            return y_;
        }
        bool is_upper(const Point& other) const{
            return y_ < other.y_;
        }
        bool is_lefter(const Point& other) const{
            return x_ < other.x_;
        }
        void draw() const{
            cout << "x: " << x_ << " y: " << y_;
        }
};


class Shape{
    public:
        virtual double perimeter() const = 0;
        virtual void draw() const = 0;

};
class Circle : public Shape{
    double radius_;
    Point center_;
    public:
        Circle(double radius, const Point& center) : radius_(radius), center_(center){}
        double perimeter() const{
            return 2 * M_PIl * radius_;
        }
        void draw() const{
            cout << "radius: " << radius_ << " x: " << center_.get_x() << " y: " << center_.get_y(); 
        }
};

class Rectangle : public Shape{
    private:
        Point ul_, br_;
    public:
        Rectangle(const Point& ul, const Point& br) : ul_(ul), br_(br) {
            if(!ul.is_upper(br) || !ul.is_lefter(br)){
                throw RectangleException();
            }
        }
        
        double get_width() const{
            return ul_.get_x() - br_.get_x();
        }
        double get_height() const{
            return br_.get_y() - ul_.get_y();
        }
        double perimeter() const{
            return 2 * get_width() + 2 * get_height();
        }
        void draw() const{
            cout << "ul: ";
            ul_.draw();
            cout << " br: ";
            br_.draw();
        }
};
class Triangle : public Shape{
    private:
        Point a_, b_, c_;
    public:
        Triangle(const Point& a, const Point& b, const Point& c) : a_(a), b_(b), c_(c){
            if(a_.get_x() == b_.get_x() && b_.get_x() == c.get_x()){
                throw TriangleException();
            }

            if(a_.get_y() == b_.get_y() && b_.get_y() == c_.get_y()){
                throw TriangleException();
            }

        }
        double A() const{
            return sqrt(pow(abs(c_.get_y() - b_.get_y()), 2) + pow(abs(c_.get_x() - b_.get_x()), 2));
        }
        
        double B() const{
            return sqrt(pow(abs(a_.get_y() - c_.get_y()), 2) + pow(abs(a_.get_x() - c_.get_x()), 2));
        }

        double C() const{
            return sqrt(pow(abs(a_.get_y() - b_.get_y()), 2) + pow(abs(a_.get_x() - b_.get_x()), 2));
        }
        double perimeter() const{
          return A() + B() + C();  
        }
        void draw() const{
            cout << "A: ";
            a_.draw();
            cout << " B: ";
            b_.draw();
            cout << " C: ";
            c_.draw();
        }

};
int main(){
    Circle c1(3.0, Point(0, 0));
    cout << c1.perimeter() << endl;
    vector<Shape*> shapes;
    
    shapes.push_back(&c1);
    shapes.push_back(new Rectangle(Point(1.0), Point(3.0, 4.0)));
    shapes.push_back(new Triangle(Point(3.2), Point(5.1), Point(8.3)));
    for(vector<Shape*>::iterator it = shapes.begin(); it != shapes.end(); it++){
       cout << (*it)->perimeter() << endl;
    }

}
