#ifndef MINUS_HH_
#define MINUS_HH_

#include "binary.hh"

class Minus: public BinaryOperation {
public:
	Minus(Calculator& calc)
	: BinaryOperation("-", calc)
	{}
protected:
	double eval(double a, double b);
};


#endif