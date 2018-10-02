#include <iostream>
#include <exception>
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
    T pop(){
        if(empty()){
            throw exception();
        }
        return this->data[--this->top];
        
    }
    void push(T val){
        if(full()){
            throw exception();
        }
        this->data[this->top++] = val;

    }

};

int main(){

    Stack<int> ist;
    Stack<double> dst;

    cout << "ist.empty()" << ist.empty() << endl;
    cout << "dst.empty()" << dst.empty() << endl;

    return 0;
}
