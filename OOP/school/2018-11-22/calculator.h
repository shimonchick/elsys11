#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include <vector>
#include <list>
#include <iostream>

class Operation;

class Calculator{
        
        std::vector<double> values_;
        std::list<Operation*> operations_;
        void push(double value);
        double pop();
    public:
        void run(std::istream& in, std::ostream& out);
        void add_operation(Operation* op);
        Operation* get_operation(const std::string&) const;
};

#endif
