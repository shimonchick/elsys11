#ifndef POINT_H_
#define POINT_H_
class Point{
    double x_;
    double y_;
    public:
        Point(double x = 0.0, double y = 0.0) : x_(x), y_(y){}
        double get_x() const{
            return x_;
        }
        double get_y() const{
            return y_;
        }
        void print() const; 
};

#endif
