all: turtle



turtle.o: turtle.cc turtle.hh
	gcc -c turtle.cc turtle.hh

main.o: main.cc turtle.hh
	gcc -c main.cc turtle.hh

turtle: turtle.o main.o
	g++ turtle.o main.o
