all: ls.o error_handling.o
	gcc -o ls ls.o error_handling.o

ls.o: ls.c
	gcc -c ls.c
error_handling.o: error_handling.c error_handling.h
	gcc -c error_handling.c error_handling.h
clean:
	rm a.out
	rm ls
	rm *.o
