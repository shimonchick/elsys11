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
		return this->top == -1;
	}
	
	bool isFull(){
		return this->top == STACK_SIZE;
	}

	void push(int val){
		if(!isFull()){
			this->data[this->top++] = val;
		} else{
			cerr << "Error: Stack is full";
			//this->data = new int[2 * this->top];
		}
	}

	int pop(){
		if(!isEmpty()){
			int result = this->data[this->top];
			this->top--;
			return result;
		} else{
			cerr << "Error: Stack is empty";
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


	return 0;
}

