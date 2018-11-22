all: rpc.o calculator.o
	g++ rpc.o calculator.o
	

rpc.o: rpc.cpp 
	g++ -c rpc.cpp

calculator.o: calculator.cpp calculator.h
	g++ -c calculator.cpp

clean:
	rm -fr *.o
	rm -fr postfix
