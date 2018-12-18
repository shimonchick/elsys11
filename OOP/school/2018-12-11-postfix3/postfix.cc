#include "calculator.hh"
#include <iostream>
#include "unary.hh"
#include "negate.hh"
#include "binary.hh"
#include "swap.hh"
#include "dup.hh"
#include "composite.hh"
#include "minus.hh"
#include "plus.hh"
#include "mult.hh"
#include "sqrt.hh"
#include "drop.hh"
#include "rot3.hh"
#include "push.hh"


int main() {
	Calculator calc;
	calc.add_operation(new Negate(calc));
	calc.add_operation(new Plus(calc));
	calc.add_operation(new Mult(calc));
	calc.add_operation(new Sqrt(calc));
	calc.add_operation(new Dup(calc));
	calc.add_operation(new Swap(calc));
	calc.add_operation(new Minus(calc));
	calc.add_operation(new Drop(calc));
	calc.add_operation(new Rot3(calc));
	
	Composite* squared = new Composite("squared", calc);
	squared->add_operation(new Dup(calc));
	squared->add_operation(new Mult(calc));
	
	calc.add_operation(squared);

	Composite* cube = new Composite("cube", calc);
	cube->add_operation(new Dup(calc));
	cube->add_operation(new Dup(calc));
	cube->add_operation(new Mult(calc));
	cube->add_operation(new Mult(calc));
	

	Composite* hypo = new Composite("hypo", calc);
	hypo->add_operation(new Dup(calc));
	hypo->add_operation(new Mult(calc));
	hypo->add_operation(new Swap(calc));
	hypo->add_operation(new Dup(calc));
	hypo->add_operation(new Mult(calc));
	hypo->add_operation(new Plus(calc));
	hypo->add_operation(new Sqrt(calc));
	
	calc.add_operation(hypo);
	
	
	
	calc.run(std::cin, std::cout);
	return 0;
}
