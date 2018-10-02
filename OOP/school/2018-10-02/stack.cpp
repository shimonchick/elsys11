#include <iostream>
using namespace std;

#define STACK_SIZE 10

template<typename T>
class Stack{
    T data[STACK_SIZE];
    int top;
public:
    Stack(){
        this->top = 0;
    }
    bool empty(){
        return this->top == 0;
    }
    bool full(){
        return this->top == STACK_SIZE;
    }

};

int main(){

    Stack<int> ist;
    Stack<double> dst;

    cout << "ist.empty()" << ist.empty() << endl;
    cout << "dst.empty()" << dst.empty() << endl;

    return 0;
}
