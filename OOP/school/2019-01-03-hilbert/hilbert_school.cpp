//
// Created by misho on 03/01/19.
//

#include <iostream>
using namespace std;
#include "turtle.hh"



class Hilbert{
    private:
        Turtle& turtle_;
        double step_;
    public:
        Hilbert(Turtle& turtle, double step = 20) : turtle_(turtle), step_(step)
        {}
        void draw_a(int order);
        void draw_b(int order);
        void draw_c(int order);
        void draw_d(int order);

};


void Hilbert::draw_a(int order) {
    if(order == 0){
        return;
    }
    draw_d(order - 1);
    turtle_.set_heading(180).forward(step_);
    draw_a(order - 1);
    turtle_.set_heading(-90).forward(step_);
    draw_a(order -1);
    turtle_.set_heading(0).forward(step_);
    draw_b(order - 1);
}
void Hilbert::draw_b(int order) {
    if(order == 0){
        return;
    }
}

void Hilbert::draw_c(int order) {
    if(order == 0){
        return;
    }
}


void Hilbert::draw_d(int order) {
    if(order == 0){
        return;
    }
}

