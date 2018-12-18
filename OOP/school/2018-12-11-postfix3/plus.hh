#ifndef PLUS_HH_
#define PLUS_HH_

#include "binary.hh"

class Plus: public BinaryOperation {
public:
	Plus(Calculator& calc)
	: BinaryOperation("+", calc)
	{}
protected:
	double eval(double a, double b);
};


#endif