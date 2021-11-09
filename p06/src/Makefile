CC=g++
CXXFLAGS=-std=c++11 -g

OBJS=$(patsubst %.cc,%.o,$(wildcard *.cc))
all: ${OBJS}
	$(CC) $(CXXFLAGS) -o dna_sequencer ${OBJS}

clean:
	rm -rf *.o dna_sequencer
