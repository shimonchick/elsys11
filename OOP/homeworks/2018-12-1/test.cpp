#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    int n;
    cin >> n;
    int a[n];
    for(int i = 0; i < n; i++) a[i] = i;
    for(int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl;
    return 0;
}
