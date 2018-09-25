#include "stack.h"

template <class T>
Stack<T>::Stack(){
    this->data = new T[2];
   this->capacity = 2;
}

template <class T>
void Stack<T>::push(T value){
    if(this->top == this->capacity){
        this->data = new T[this->capacity * 2];
        this->capacity ++;
    }
    this->data[this->top++] = value;
}

template <class T>
bool Stack<T>::isEmpty(){
    return this->top == 0;

template <class T>
T Stack<T>::pop(){
    if(!isEmpty()) return this->data[--this->top];
}
template<class T>
int Stack<T>::size(){
    return this->capacity;
}