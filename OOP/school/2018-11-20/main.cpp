#include "point.h"
#include "rectangle.h"
#include <iostream>

//extern int a;

int main(){
    //int a = 1;
    //int a;
    Point p1(1,2);
    Point p2(2, 4);

    p1.print();
    p2.print();
    
    Rectangle r1(Point(1,1), Point(3.4));
    r1.print();
    return 0;
}
