#ifndef DIVIDE_HH_
#define DIVIDE_HH_

#include "binary.hh"

class Divide: public BinaryOperation {
public:
	Divide(Calculator& calc)
	: BinaryOperation("/", calc)
	{}
protected:
	double eval(double a, double b);
};


#endif