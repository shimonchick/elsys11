#include "calculator.h"
#include "operation.h"
#include <iostream>
#include <sstream>
using namespace std;
class CalculatorException{};

Operation* Calculator::get_operation(const string& name) const{
    for(list<Operation*>::const_iterator it = operations_.begin(); it != operations_.end(); it++){
        if(*it)->get_name() == name){
            return *it;
        }
    }
}

double Calculator::pop(){
    double result = values_.back();
    values_.pop_back();
    return result;
}
void Calculator::push(double value){
    values_.push_back(value);
}

void Calculator::run(istream& in, ostream& out){
    while(!in.eof()){
        out << "()=" << values_.size() << "): ";
        string token;
        getline(in, token);
        
        istringstream iss(token);
        double value;
        iss >> value;
        if(!iss.fail() && iss.eof()){
            push(value);
        }else{
            Operation* operation = get_operation(token);
            double result = operation->execute();
            out << result << endl;
        }
    }
}
