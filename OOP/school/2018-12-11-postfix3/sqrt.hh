#ifndef SQRT_HH__
#define SQRT_HH__

#include "unary.hh"
#include <cmath>

class Sqrt: public UnaryOperation {
public:
	Sqrt(Calculator& calc)
	: UnaryOperation("sqrt", calc)
	{}
protected:

	double eval(double val);
};

#endif