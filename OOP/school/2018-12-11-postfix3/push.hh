#ifndef PUSH_HH_
#define PUSH_HH_

#include "operation.hh"

class Push: public Operation {
private:
    double value;
public:
	Push(Calculator& calc, double val)
	: Operation("push", calc), value(val)
	{}
	
	void execute();

};

#endif