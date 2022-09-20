#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <curses.h>
#include <time.h>
#include <signal.h>
#include "defs.h"

// Function prototypes:
void cleanup(int);
void print_edges(int, int);
void fps_delay(void);
void display_score(int, int, int);
bool jump(short);
void display_obstacle(Obstacle, int, int);
void game_over(int, int, int);
void help(void);
int topscore(int);
// The functions above are listed in utils.c, which is linked to this file, assuming that you used the Makefile!

int main(int argc, char** argv) {
	int first = topscore(1), second = topscore(2), third = topscore(3);
	if (argc > 1) {
		if (strcmp(argv[1], "-h") * strcmp(argv[1], "--help") == 0) {
			help();
			return EXIT_SUCCESS;
		} else if (strcmp(argv[1], "top") == 0) {
			printf("TOP SCORES:\n1  :  %d\n2  :  %d\n3  :  %d\n", first, second, third);
			return EXIT_SUCCESS;
		}
	}
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

	const int OBSTACLE_COUNT = win_x / 30 + 2;

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

	// create our speed variable 
	double speed = 1.0;

	// Start our loop:
	while (true) {
		erase();
		print_edges(win_y, win_x);
		if (score > first) {
			third = second;
			second = first;
			first = score;
		}
		display_score(score, first, win_x);
		
		// Is the user touching an obstacle?
		for (int i = 0; i < OBSTACLE_COUNT; i++) {
			if (obs[i].x == character_x && y < obs[i].height) {
				// Uh, oh!
				for (int i = 0; i < OBSTACLE_COUNT; i++) display_obstacle(obs[i], win_y - TEXT_MARGIN, win_x - TEXT_MARGIN);
				mvaddch(win_y - TEXT_MARGIN - y, character_x, '#');
				game_over(score, win_y, win_x);
			} else if (character_x == obs[i].x) {
				// Otherwise, the score should increase!
				score ++;
			}
		}
		
		// Move each obstacle one over:
		for (int i = 0; i < OBSTACLE_COUNT; i++) obs[i].x-=(int)speed;
		
		// Loop the obstacles if they go over the edge
		for (int i = 0; i < OBSTACLE_COUNT; i++) {
			if (obs[i].x <= TEXT_MARGIN) {
				obs[i].x = win_x - TEXT_MARGIN + rand() % 30;
				obs[i].height = rand() % MAX_OB_HEIGHT + 1;
			}
		}

		// Display obstacles:
		for (int i = 0; i < OBSTACLE_COUNT; i++) display_obstacle(obs[i], win_y - TEXT_MARGIN, win_x - TEXT_MARGIN);
		

		// see if character moved:
		short key_pressed = getch();
		if (jump(key_pressed) && y == 0) {
			is_jumping = true;
			beep();

		} else if (key_pressed == KEY_DOWN || key_pressed == 's' || key_pressed == 'S') {
			is_jumping = false;
			if (y != 0) y--;
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

	// If someone is debugging this and accidentally goes here, then we should clean up after ourselves:
	endwin();

	return EXIT_SUCCESS;
}
