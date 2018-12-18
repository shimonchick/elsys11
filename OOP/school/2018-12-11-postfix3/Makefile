all: postfix

calculator.o: calculator.cc operation.hh calculator.hh composite.hh push.hh

unary.o: unary.cc unary.hh operation.hh

negate.o: negate.cc negate.hh operation.hh
sqrt.o: sqrt.cc sqrt.hh operation.hh

binary.o: binary.cc binary.hh operation.hh

minus.o: minus.cc minus.hh operation.hh
plus.o: plus.cc plus.hh operation.hh
mult.o: mult.cc mult.hh operation.hh
divide.o: divide.cc divide.hh operation.hh

swap.o: swap.cc swap.hh operation.hh
dup.o: dup.cc dup.hh operation.hh
drop.o: drop.cc drop.hh operation.hh
rot3.o: rot3.cc rot3.hh operation.hh
push.o: push.cc push.hh operation.hh


postfix.o: postfix.cc calculator.hh binary.hh unary.hh operation.hh composite.hh negate.hh plus.hh minus.hh mult.hh divide.hh swap.hh dup.hh drop.hh rot3.hh push.hh

postfix: postfix.o calculator.o unary.o negate.o binary.o minus.o plus.o mult.o divide.o sqrt.o swap.o dup.o drop.o rot3.o push.o
	g++ -o postfix postfix.o calculator.o unary.o negate.o binary.o minus.o plus.o mult.o divide.o sqrt.o swap.o dup.o drop.o rot3.o push.o

clean:
	rm -fr *.o
	rm -fr postfix

