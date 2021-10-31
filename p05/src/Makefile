
CC=g++
CXXFLAGS=-std=c++11 -g

OBJS= Dfa.o Symbol.o Chain.o Alphabet.o Language.o main.o State.o
all: ${OBJS}
	$(CC) $(CXXFLAGS) -o dna_sequencer ${OBJS}

clean:
	rm -rf *.o dna_sequencer
