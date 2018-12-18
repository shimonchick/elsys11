#ifndef DROP_HH_
#define DROP_HH_

#include "operation.hh"

class Drop: public Operation {
public:
	Drop(Calculator& calc)
	: Operation("drop", calc)
	{}
	
	void execute();

};

#endif