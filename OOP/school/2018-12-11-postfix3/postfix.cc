#include "calculator.hh"
#include <iostream>
#include "negate.hh"
#include "binary.hh"
#include "stack_operations.hh"

int main() {
	Calculator calc;
	calc.add_operation(new Negate(calc));
	calc.add_operation(new Plus(calc));
	calc.add_operation(new Mul(calc));
	calc.add_operation(new Dup(calc));
	calc.add_operation(new Swap(calc));
	calc.run(std::cin, std::cout);
	return 0;
}
