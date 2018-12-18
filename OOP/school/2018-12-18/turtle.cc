#include "turtle.hh"
#include <cmath>

using namespace std;

Point Point::polar(double angle, double distance){
    return Point(cos(angle) * distance, sin(angle) * distance);
}

Point Point::cartesian(double x, double y){
    return Point(x, y);
}

ostream& operator<<(ostream& out, const Point& p){
    out << p.get_x() << " " <<  p.get_y();
    return out;
}

void PSTurtle::setup(){
    out_ << "newpath" << endl;
    
}
PSTurtle::~PSTurtle(){
    
    out_ << "stroke" << endl;

}
