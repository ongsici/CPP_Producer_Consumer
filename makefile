main: main.o buffer.o
	g++ -g main.o buffer.o -o main

main.o: main.cpp buffer.h
	g++ -g -Wall -c main.cpp

buffer.o: buffer.cpp buffer.h
	g++ -g -Wall -c buffer.cpp

clean: 
	rm -f *.o main