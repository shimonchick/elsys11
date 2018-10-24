all: bmp-info.o read.o
	gcc bmp-info.o read.o -o bmp-info
bmp-info.o: bmp-info.c
	gcc -c bmp-info.c
read.o: read.c
	gcc -c read.c

clean:
	rm *.o
	rm *.out
