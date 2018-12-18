#ifndef DUP_HH_
#define DUP_HH_

#include "operation.hh"

class Dup: public Operation {
public:
	Dup(Calculator& calc)
	: Operation("dup", calc)
	{}
	
	void execute();

};

#endif