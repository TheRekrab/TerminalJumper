CC=gcc
CFLAGS=-g -Wall -lcurses
FINALFLAGS=-s -Wall -DNDEBUG -lcurses
BIN=game

all: $(BIN)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f a.out $(BIN)

run: $(BIN)
	@./$(BIN); rm $(BIN)

final: $(BIN).c
	$(CC) $(FINALFLAGS) $< -o $@
