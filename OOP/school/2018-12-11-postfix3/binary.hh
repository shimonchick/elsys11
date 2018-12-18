#ifndef BINARY_HH__
#define BINARY_HH__

#include "operation.hh"

class BinaryOperation : public Operation{

	
public:
	BinaryOperation(const std::string& name, Calculator& calc, double* num = NULL)
		: Operation(name, calc), number(num) {}

	void execute();

protected:
	double* number;
	virtual double eval(double v1, double v2) = 0;
	

};


#endif
