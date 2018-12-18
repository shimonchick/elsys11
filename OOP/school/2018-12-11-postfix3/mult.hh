#ifndef MULT_HH_
#define MULT_HH_

#include "binary.hh"

class Mult: public BinaryOperation {
public:
	Mult(Calculator& calc)
	: BinaryOperation("*", calc)
	{}
protected:
	double eval(double a, double b);
};


#endif