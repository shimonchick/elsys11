#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include <vector>
#include <iostream>
class Calculator{
        
        std::vector<double> values_;
    public:
        void push(double value);
        double pop();
        void run(std::istream& in, std::ostream& out);
}; 

#endif
