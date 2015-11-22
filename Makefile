ifndef test
test=core
endif

prog := prog
prog_objs := core.o hashtab.o ciphers.o signatures.o md5.o poker.o test_$(test).o

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
