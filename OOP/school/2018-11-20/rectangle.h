#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "point.h"
#include "shape.h"


class Rectangle : public Shape{
    Point ul_;
    Point br_;
    public:
        Rectangle(const Point& ul, const Point& br): ul_(ul), br_(br){}
        const Point& get_ul() const{
            return ul_;
        }
        const Point& get_br() const{
            return br_;
        }
        void print() const;
};

#endif
