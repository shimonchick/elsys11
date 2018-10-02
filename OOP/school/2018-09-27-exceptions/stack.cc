#include<iostream>
using namespace std;

#define STACK_SIZE 10
#define STRING_SIZE 10
class Stack{

public:

	Stack(){
		this->top = 0;

	}

	bool isEmpty(){
		return this->top == 0;
	}
	
	bool isFull(){
		return this->top == STACK_SIZE;
	}

	int push(int val){
		if(!isFull()){
			this->data[this->top++] = val;
		} else{
			cerr << "Error: Stack is full";
			return -1;
			//this->data = new int[2 * this->top];
		}
	}

	int pop(){
		if(!isEmpty()){
			return this->data[--this->top];
		} else{
			cerr << "Error: Stack is empty";
			return -1;
		}
		
	}
	void test(){
		cout << data;
	}
private:
	int data[STACK_SIZE];
	int top;
};

class BracketSolver{
public:
	bool isBalanced(char brackets[]){
		Stack stack;
		for(int i = 0; brackets[i] != '\0';i++){
			stack.push(brackets[i]);
			//cout << brackets[i] << endl;
		}
		
		int counter = 0;
		do{
			char element = (char)stack.pop();
			//cout << element << endl;
			if(element=='{' or element=='(') counter++;
			if(element=='}' or element==')') counter--;
		}while(!stack.isEmpty());

		if(counter==0) return 1;
		return 0;


	}		
};

int main(){
	char string[STRING_SIZE];
	cin >> string;
	BracketSolver solver;
	cout << "is balanced: " << solver.isBalanced(string) << endl;
	Stack st;

	
	for(int i = 0;i < 11; i++){
		if(st.push(i) == -1){
			cout << "failed"<<endl;
		}
		else{
			cout << "succeed" <<endl;
		}
	}
	for(int i = 0 ; i < 11 ; i++){
		if(st.pop() == -1){
			cout << "failed"<<endl;
		}else {
			cout << "succeed"<<endl;
		}

	}

	return 0;
}

