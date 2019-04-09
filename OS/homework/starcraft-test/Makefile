all: miner.o command_center.o marine.o main.o mineral.o error_handling.o helper.o
	gcc miner.o mineral.o marine.o main.o error_handling.o command_center.o helper.o -pthread -o starcraft3	
miner.o: miner.c miner.h
	gcc -c -g miner.c -pthread

mineral.o: mineral.c mineral.h
	gcc -c -g mineral.c -pthread

marine.o: marine.c marine.h
	gcc -c -g marine.c -pthread

main.o: main.c
	gcc -c -g main.c -pthread

error_handling.o: error_handling.c error_handling.h
	gcc -c -g error_handling.c -pthread

command_center.o: command_center.c command_center.o
	gcc -c -g command_center.c -pthread

helper.o: helper.c helper.h
	gcc -c -g helper.c -pthread

clean:
	rm -f *.o
	rm -f starcraft3
