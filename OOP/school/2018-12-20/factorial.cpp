
using namespace std;
// every stack frame bytes are allocated on the stack
int factorial_base(int n){
    if(n == 0) return 1;
    return n * factorial_base(n -1);
}
//the previous stack frame is cleared by the compiler (tail call optimization)
int factorial(int n, int result = 1){
    if(n == 0)
        return result;
    return factorial(n - 1, result * n);
}
//iterative approach
int factorial_iterative(int n){
    int result = 1;
    for(int i = 2; i <= n; i++){
        result *= i;
    }
    return result;
}
//resursive fibonaci O(2^^n)
int fibonacci(int n, vector<int>& temp){
    if(temp[n] == -1){
        temp[n] = fibonacci(n - 1, temp) + fibonacci(n - 2, temp);
    }
    return temp[n];
}
int fib(int n){
    vector<int> temp(n, -1);
    temp[0] = 0;
    temp[1] = 1;
    fibonacci(n, temp);
}

int fibonacci_iterative(int n){
    int a = 0, b = 1;
    if(n == 0) return a;
    if(n == 1) return b;
    for(int i = 2; i <= n; i++){
        a = b;
        b = a + b;
    }
    return a;
}


int main(){
    factorial(5);

    return 0;
}
