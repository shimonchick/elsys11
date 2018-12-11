all: postfix

calculator.o: operation.hh calculator.hh calculator.cc

unary.o: unary.hh unary.cc

binary.o: binary.hh binary.cc

negate.o: negate.hh negate.cc

stack_operations.o: stack_operations.cc stack_operations.hh


postfix.o: postfix.cc calculator.hh



postfix: postfix.o calculator.o unary.o negate.o binary.o stack_operations.o
	g++ -o postfix postfix.o calculator.o unary.o negate.o binary.o stack_operations.o

clean:
	rm -fr *.o
	rm -fr postfix

