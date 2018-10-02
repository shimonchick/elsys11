#include<iostream>
#include "stack.h"

using namespace std;

int main(int argc, char const *argv[])
{
    Stack<int> st;
    st.push(0);
    st.push(5);
    st.push(10);
    st.push(654);
    cout << "size: " <<st.size() << "isFull?: " << st.isFull() << "is Empty?: " << st.isEmpty();
    return 0;
}
