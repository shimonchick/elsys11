all: png-info.o read.o
	gcc png-info.o read.o -o png-info
png-info.o: png-info.c
	gcc -c png-info.c
read.o: read.c
	gcc -c read.c

clean:
	rm *.o
	rm *.out
