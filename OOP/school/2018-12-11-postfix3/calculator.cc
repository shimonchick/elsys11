#include "calculator.hh"
#include "operation.hh"
#include "composite.hh"
#include "push.hh"
#include <iostream>
#include <sstream>
#include <exception>
#include <list>

using namespace std;

void Calculator::push(double value) {
	values_.push_back(value);
}

double Calculator::pop() {
	double result = values_.back();
	values_.pop_back();
	return result;
}

void Calculator::add_operation(Operation* op) {
	operations_.push_back(op);
}

Operation* Calculator::get_operation(const string& name) const {
	for (list<Operation*>::const_iterator it = operations_.begin(); it != operations_.end(); it++) {
		if ((*it) -> get_name() == name) {
			return *it;
		}
	}
	throw exception();
}

void Calculator::run(istream& in, ostream& out) {
	while (!in.eof()) {
		out << "--------> ";
		string token;
		getline(in, token);
		istringstream iss(token);
		double value;
		iss >> value;
		if (!iss.fail() && iss.eof()) {
			push(value);
		} else if(token[0] == '/'){

			string name = token.substr(1);

			Composite* composite_operation = new Composite(name, *this);
			
			
			string subcommand;
			getline(in, subcommand);
			while(subcommand != "end"){
				int number = 0;
				int i = 0;
				for(; token[i] >= '0'  && token[i] <= '9'; i++){
					number = number * 10 + (token[i] - '9'); 
				}
				if(i != 0){
					composite_operation->add_operation(new Push(*this, number));
				}
				subcommand = subcommand.substr(i);
				Operation* operation = get_operation(subcommand);
				composite_operation->add_operation(operation);
				getline(in, subcommand);
			}
			add_operation(composite_operation);
		}else {
			Operation* op = get_operation(token);
			op -> execute();
			double result = values_.back();
			out << result << endl;
		}
		
	}
}

Calculator::~Calculator(){
	for(list<Operation*>::iterator it = operations_.begin(); it != operations_.end(); it++){
		delete *it;
	}
}

