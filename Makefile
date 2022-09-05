CC=gcc
CFLAGS=-g -Wall -lcurses
BIN=game
UTILS=utils
HDRS=defs.h
PROJ_NAME=jump

all: $(BIN).o $(UTILS).o $(HDRS)
	$(CC) $(CFLAGS) $(BIN).o $(UTILS).o -o $(BIN)

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f a.out $(BIN) *.o

run: all
		@./$(BIN); rm $(BIN) *.o

production: $(BIN).o $(UTILS).o $(HDRS)
	$(CC) -s -DNDEBUG -lcurses $(BIN).o $(UTILS).o -o $(BIN)
	rm $(BIN).o $(UTILS).o

install: production
	sudo cp $(BIN) /usr/local/bin/$(PROJ_NAME)
	rm $(BIN)
