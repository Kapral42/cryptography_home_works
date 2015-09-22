prog := prog
prog_objs := functions.o hashtab.o main.o 

CXX := gcc
CXXFLAGS := -g -std=c11 -Wall -O0
LDFLAGS := -lm

.PHONY: all clean

all: $(prog)

$(prog): $(prog_objs)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -rf *.o $(prog)

run: all
	./prog
