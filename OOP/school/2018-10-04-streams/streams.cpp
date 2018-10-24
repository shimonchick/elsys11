#include <iostream>
#include <sstream>

using namespace std;

int main(){
    ostringstream out;
    string st = "Prasi sucks";

    out << st;

    cout << out.str() << endl;    

    string str = "3.14 42";
    istringstream in(str);

    double pi;
    in >> pi;

    if(in.good()){
        cout << "All good";
    }
    else{
        cout << "could not pass";
    }


    string str1;
    in>> str1;
    while(!in.eof()){
        cout << "parsed string =" << str1 << endl;
        in >> str1;
    }
    cout << pi << endl;


    return 0;

}
