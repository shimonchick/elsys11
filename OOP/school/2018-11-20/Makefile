all : draw

main.o: main.cpp rectangle.h shape.h point.h
	g++ -c main.cpp -o main.o
point.o : point.cpp point.h
	g++ -c point.cpp -o point.o

rectangle.o: rectangle.cpp rectangle.h shape.h point.h
	g++ -c rectangle.cpp -o rectangle.o

draw: main.o rectangle.o point.o
	g++ -o draw main.o rectangle.o point.o

clean:
	rm -f *.o
	rm -f a.out
	rm -f draw
