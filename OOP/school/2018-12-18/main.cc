#include <iostream>

#include "turtle.hh"




using namespace std;
int main() {

    PSTurtle turtle(1000.0, 800.0, cout);
    turtle.setup();
    return 0;
}