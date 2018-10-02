#include<iostream>
#include<string>
using namespace std;

#define STACK_SIZE 10
#define STRING_SIZE 10

class Exception{
	string error_message;
public:
	Exception(string msg){
		error_message = msg;
	}
	string GetMessage(){
		return error_message;
	}
};
class Stack{

public:

	Stack(){
		this->top = 0;

	}

	bool isEmpty(){
		return this->top == 0;
	}
	
	bool isFull(){
		throw Exception("test");
		return this->top == STACK_SIZE;
	}

	int push(int val){
		if(!isFull()){
			//cout << "working";
			this->data[this->top++] = val;
		} else{
			//cerr << "Error: Stack is full";
			throw Exception("Stack is full");
			//this->data = new int[2 * this->top];
		}
	}

	int pop(){
		if(!isEmpty()){
			return this->data[--this->top];
		} else{
			//cerr << "Error: Stack is empty";
			throw Exception("Stack is empty");
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

	try{
		for(int i = 0;i < 11; i++){
			st.push(i);
		}
	} catch(Exception e){
		cout << e.GetMessage() << endl;
	}
	try{
		for(int i = 0; i < 11; i++){
			st.pop();
		}
	}	catch(Exception e){
		cout << e.GetMessage() << endl;
	}

	return 0;
}

