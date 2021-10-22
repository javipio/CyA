
CC=g++
CXXFLAGS=-std=c++11 -g

OBJS= CppParser.o Occurence.o main.o
all: ${OBJS}
	$(CC) $(CXXFLAGS) -o CppParser ${OBJS}

clean:
	rm -rf *.o CppParser
