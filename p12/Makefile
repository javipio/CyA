# project name (generate executable with this name)
PROGNAME   = matrices

CC       = g++
# compiling flags here
CFLAGS   = -std=c++11 -Wall

LINKER   = g++
# linking flags here
LFLAGS   = -Wall

# change these to proper directories where each file should be
SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin

SRC_FILES  := $(patsubst $(SRCDIR)/%.cc, $(BINDIR)/%.o, $(wildcard $(SRCDIR)/*.cc))

$(PROGNAME): $(SRC_FILES)
	@mkdir -p $(BINDIR)
	@echo $(SRC_FILES)
	@$(LINKER) $(SRC_FILES) $(LFLAGS) -o $(BINDIR)/$@
	@echo "Linking complete!"

$(BINDIR)/%.o: $(SRCDIR)/%.cc
	@echo $< $@
	@$(CC) -g -c $< -o $@

clean:
	rm -rf $(BINDIR)/*
