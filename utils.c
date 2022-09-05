#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <unistd.h>
#include <curses.h>
#include "defs.h"

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
}

void fps_delay(void) {
	double milliseconds_to_sleep = 1000 / FPS;
	usleep(milliseconds_to_sleep * 100);
}

void display_score(int score) {
	mvprintw(MARGIN - 1, MARGIN, "SCORE: %d", score);
}

bool jump(short key_pressed) {
	switch (key_pressed) {
		case ' ':
			return true;
			break;
		case 'w':
			return true;
			break;
		case 'W':
			return true;
			break;
		case KEY_UP:
			return true;
			break;
		default:
			return false;
	}
}

void display_obstacle(Obstacle obstacle, int floor, int max_x) {
	for (int i = 0; i < obstacle.height; i++) {
		if (obstacle.x > max_x) continue;
		mvaddch(floor - i, obstacle.x, '*');
	}
}
