CC = g++
CFLAGS = -Wall -g -O0 -c
LFLAGS = -Wall

all: $(addprefix bin/,TokenizerTest)

bin/TokenizerTest: $(addprefix bin/,TokenizerTest.o Tokenizer.o)
	$(CC) $(LFLAGS) -o $@ $^

bin/TokenizerTest.o: $(addprefix src/,TokenizerTest.cpp Tokenizer.h)
	$(CC) $(CFLAGS) -o $@ $<

bin/Tokenizer.o: $(addprefix src/,Tokenizer.cpp Tokenizer.h debug.h)
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean

clean:
	rm -f bin/*
	