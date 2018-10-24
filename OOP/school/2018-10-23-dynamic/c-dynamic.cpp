#include <iostream>
#include <cstdlib>
using namespace std;

class Foo{

    int bar_;
    public:
    Foo() : bar_(42){
        cout << "Foo() called..." << endl;
    }

    Foo(int bar) : bar_(bar){
        cout << "Foo(int) called" << endl;
    }

    ~Foo(){
        cout << "~Foo() called" << endl;
        free(this);
    }
    int get_bar() const{
        return bar_;
    }
    

};

int main(){
    Foo f1;
    cout << "f1.bar_ =" << f1.get_bar() << endl;

    Foo* fptr = (Foo*)malloc(sizeof(Foo));
    cout << "fptr->bar_" << fptr->get_bar()<< endl;

    Foo* p1 = new Foo;
    Foo* p2 = new Foo(43);
    Foo* p3 = new Foo[3];
    
    delete p1;
    cout << p1->get_bar() << endl;
    delete p2;

    delete [] p3;
    

    free(fptr);
}
