#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <unistd.h>
#include <curses.h>
#include <time.h>
#include <signal.h>
#include "defs.h"

// Function prototypes:
void cleanup(int);
void print_edges(int, int);
void fps_delay(void);
void display_score(int);
bool jump(short);
void display_obstacle(Obstacle, int, int);

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
	// setup win_y and win_x
	int win_y, win_x;
	getmaxyx(stdscr, win_y, win_x);
	win_y --;
	win_x --;

	
	// create obstacles:
	Obstacle obs[OBSTACLE_COUNT];
	for (int i = 0; i < OBSTACLE_COUNT; i++) {
		int x = rand() % (win_x - 2 * TEXT_MARGIN) + TEXT_MARGIN;
		x += win_x;
		obs[i].x = x;
		obs[i].height = rand() % MAX_OB_HEIGHT + 1;
	}

	// Create boolean is_jumping variable
	bool is_jumping = false;
	int character_x = win_x / 2 - 10;

	// Start our loop:
	while (true) {
		erase();
		print_edges(win_y, win_x);
		display_score(score);

		// Is the user touching an obstacle?
		for (int i = 0; i < OBSTACLE_COUNT; i++) {
			if (obs[i].x == character_x) {
				if (y > obs[i].height) {
					// If this is true, then the character is safe.
					score ++;
				} else {
					// Uh, oh!
					// TODO: create a better game over screen
					endwin();
					exit(EXIT_SUCCESS);
				}
			}
		}
		
		// Move each obstacle one over:
		for (int i = 0; i < OBSTACLE_COUNT; i++) obs[i].x--;
		
		// Loop the obstacles if they go over the edge
		for (int i = 0; i < OBSTACLE_COUNT; i++) {
			if (obs[i].x == TEXT_MARGIN) {
				obs[i].x = win_x - TEXT_MARGIN;
				obs[i].height = rand() % MAX_OB_HEIGHT + 1;
			}
		}

		// Display obstacles:
		for (int i = 0; i < OBSTACLE_COUNT; i++) display_obstacle(obs[i], win_y - TEXT_MARGIN, win_x - TEXT_MARGIN);
		

		// see if character moved:
		short key_pressed = getch();
		if (jump(key_pressed) && y == 0) {
			is_jumping = true;
		} else if (key_pressed == KEY_DOWN || key_pressed == 's' || key_pressed == 'S') {
			is_jumping = false;
		}

		if (is_jumping) {
			y += 2;
			if (y > MAX_OB_HEIGHT + 4) is_jumping = false;
		}

		// Should the character fall?
		if (y != 0) {
			y --;
		}
		
		// Display character
		int full_y = win_y - TEXT_MARGIN - y;
		mvaddch(full_y, character_x, '#');

		refresh();
		fps_delay();

	}

	endwin();

	return EXIT_SUCCESS;
}
