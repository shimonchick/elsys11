#include <iostream>
using namespace std;

class Point{
    private:
        double x_;
        double y_;

    public:
        Point(double x, double y){
            x_ = x;
            y_ = y;
        }
        int get_x() const{
            return x_;
        }
        int get_y() const{
            return y_;
        }
        Point& set_x(double x){
            x_ = x;
            return *this;
        }
        Point& set_y(double y){
            y_ = y;
            return *this;
        }

};

int main(){

    const Point origin(0, 0);
    //origin.set_x(2);
    origin.get_x();

    Point point(3, 5);

    point.set_x(11).set_y(11);
    cout << point.get_x() << " , " << point.get_y();
    //Point& point2 = point.set_x(4);
    //point2.set_x(6);
    //cout<< point2.get_x() << endl;
    //cout << point.get_x() << " , " << point.get_y();
    return 0;
}
