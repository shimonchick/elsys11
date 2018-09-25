template<class T>
class Stack{
public:

    Stack();
    T pop();
    void push(T);
    bool isEmpty();
    bool isFull();
    int size();
    
    int top;
private:
    T* data;
    int capacity;
};