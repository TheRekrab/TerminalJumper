#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <unistd.h>
#include <curses.h>


#define FPS 10
#define MARGIN 5

void cleanup(int foo) {
	endwin();
	puts("Exiting...");
	exit(EXIT_SUCCESS);
}

void print_edges(int win_y, int win_x) {
	for (int y = MARGIN; y <= win_y - MARGIN; y ++) {
		if (y == MARGIN || y == win_y - MARGIN) {
			for (int x = MARGIN; x <= win_x - MARGIN; x++) {
				mvaddch(y, x, '-');
			}
		} else {
			mvaddch(y, MARGIN, '|');
			mvaddch(y, win_x - MARGIN, '|');
		}
	}
	// Add the corners:
	mvaddch(MARGIN, MARGIN, '+');
	mvaddch(MARGIN, win_x - MARGIN, '+');
	mvaddch(win_y - MARGIN, MARGIN, '+');
	mvaddch(win_y - MARGIN, win_x - MARGIN, '+');
	refresh();
}

void fps_delay(void) {
	double time_to_sleep = (FPS / 60) * 1000;
	usleep((int)time_to_sleep);
}


