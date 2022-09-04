#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <unistd.h>
#include <curses.h>
#include <time.h>
#include <signal.h>

#define MARGIN 3
#define TEXT_MARGIN (MARGIN + 1)

// Function prototypes:
void cleanup(int);
void print_edges(int, int, const int);
void fps_delay(void);
void display_score(int, const int);
bool jump(short);
// The functions above are listed in utils.c, which is linked to this file, assuming that you used the Makefile!

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
	
	// Define score variables:
	int score = 0;
	// setup y variable
	int y = 0;
	// Start our loop:
	while (true) {
		erase();
		int win_y, win_x;
		getmaxyx(stdscr, win_y, win_x);
		win_y --;
		win_x --;
		print_edges(win_y, win_x, MARGIN);
		display_score(score, MARGIN);
		
		// see if character moved:
		short key_pressed = getch();
		if (jump(key_pressed) && win_y - TEXT_MARGIN - y - 2 > TEXT_MARGIN) {
			y += 2;
		}

		// Should the character fall?
		if (y != 0) {
			y --;
		}
		
		// Display character
		int x = win_x / 2 - 10;
		int full_y = win_y - TEXT_MARGIN - y;
		mvaddch(full_y, x, '#');
		refresh();
		fps_delay();

	}

	endwin();

	return EXIT_SUCCESS;
}
