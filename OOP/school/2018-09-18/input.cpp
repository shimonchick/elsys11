#include<iostream>
using namespace std;
int main(){
	int value;
	while(true){
		cin >> value;
		if(!cin){
			cout<<"bad input"<< endl;
			break;
		}else{
			cout << value << endl;
		}

	}
	return 0;
}
