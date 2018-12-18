
#ifndef SWAP_HH_
#define SWAP_HH_

#include "operation.hh"

class Swap: public Operation {
public:
	Swap(Calculator& calc)
	: Operation("swap", calc)
	{}
	
	void execute();

};


#endif