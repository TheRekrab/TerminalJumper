#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <unistd.h>
#include <curses.h>
#include <time.h>
#include <signal.h>

// Function prototypes:
void cleanup(int);
void print_edges(int, int);
void fps_delay(void);
// The functions above are listed in utils.c, which is linked to this file, assuming that you used the Makefile

int main(int argc, char** argv) {
	// Setup a CTRL-C handler to leave the program:
	signal(SIGINT, cleanup);

	// Seed rand() by the current time
	srand(time(NULL));

	// Start & setup curses
	WINDOW* stdscr = initscr();
	nodelay(stdscr, true);
	keypad(stdscr, true);
	cbreak();
	noecho();
	curs_set(0);
	
	// Start our loop:
	while (true) {
		fps_delay();
		erase();
		int win_y, win_x;
		getmaxyx(stdscr, win_y, win_x);
		print_edges(win_y, win_x);
	}

	endwin();

	return EXIT_SUCCESS;
}
