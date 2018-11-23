#ifndef OPERATION_H_
#define OPERATION_H_
#include <string>

class Calculator;

class Operation{
    private:
        std::string name_;
        Calculator& calc_;
    public:
        Operation(const std::string& name, Calculator& calc) : name_(name), calc_(calc){}
        virtual void execute() = 0;
        std::string get_name() const{
            return name_;
        }


};

#endif
