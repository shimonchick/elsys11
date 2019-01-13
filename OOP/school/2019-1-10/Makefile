all: turtle.o queens.o
	g++ queens.o turtle.o


turtle.o: turtle.cc turtle.hh

queens.o: queens.cc turtle.hh


clean:
	rm -rf *.o
	rm -rf *.out
	