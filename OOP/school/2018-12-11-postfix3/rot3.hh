#ifndef ROT3_HH_
#define ROT3_HH_

#include "operation.hh"

class Rot3: public Operation {
public:
	Rot3(Calculator& calc)
	: Operation("rot3", calc)
	{}
	
	void execute();

};

#endif