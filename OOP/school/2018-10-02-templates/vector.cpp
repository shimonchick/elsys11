#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<int> v1;
    cout << "v1.size" << v1.size() << endl;
    cout << "v2.empty" << v1.empty() << endl;
    cout << "v1.size" << v1.size() << "v1.capacity" << v1.capacity() << endl;

    v1.push_back(10);
    v1.push_back(5);
    v1.push_back(437);
    cout << "v1.size" << v1.size() << "v1.capacity" << v1.capacity() << endl;
    
    v1.push_back(437);
    v1.push_back(437);
    cout << "v1.size" << v1.size() << "v1.capacity" << v1.capacity() << endl;
    v1.push_back(437);
    v1.push_back(437);
    v1.push_back(437);
    v1.push_back(437);
    v1.push_back(437);
    cout << "v1.size" << v1.size() << "v1.capacity" << v1.capacity() << endl;
    v1.pop_back();
    v1.pop_back();
    v1.pop_back();
    
    cout << "v1.size" << v1.size() << "v1.capacity" << v1.capacity() << endl;
    // v1.at(i) == v[i] , except it checks for index out of range
    int sum = 0;
    for(vector<int>::iterator it = v1.begin(); it!=v1.end();it++){
        cout << "*it=" << *it <<endl;
        sum += *it;

    }
    cout << sum << endl;
    vector<int> v2(10, 42);
    vector<int> v3(v1.begin(), v1.end());

    return 0;
}
