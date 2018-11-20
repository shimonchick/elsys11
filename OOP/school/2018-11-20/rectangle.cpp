#include "rectangle.h"
#include <iostream>
using namespace std;

void Rectangle::print() const{
    cout << "Rectangle(";
    ul_.print();
    br_.print();
    cout << ")" << endl;
}
