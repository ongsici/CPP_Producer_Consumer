CXX = g++
CXXFLAGS = -std=c++20 -Wall -g
TARGET = main

${TARGET}: main.o buffer.o
	${CXX} ${CXXFLAGS} main.o buffer.o -o ${TARGET}

main.o: main.cpp buffer.h
	${CXX} ${CXXFLAGS} -c main.cpp

buffer.o: buffer.cpp buffer.h
	${CXX} ${CXXFLAGS} -c buffer.cpp

clean: 
	rm -f *.o ${TARGET}