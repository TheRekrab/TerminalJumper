CC=gcc
CFLAGS=-g -Wall -lcurses
BIN=game
UTILS=utils
HDRS=defs.h

all: $(BIN).o $(UTILS).o $(HDRS)
	$(CC) $(CFLAGS) $(BIN).o $(UTILS).o -o $(BIN)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f a.out $(BIN) *.o

run: all
		@./$(BIN); rm $(BIN) *.o
