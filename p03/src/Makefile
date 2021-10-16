
CC=g++
CXXFLAGS=-std=c++11 -g

OBJS= Simbol.o Chain.o Alfabet.o Language.o main.o
all: ${OBJS}
	$(CC) $(CXXFLAGS) -o chains ${OBJS}

clean:
	rm -rf *.o chains
