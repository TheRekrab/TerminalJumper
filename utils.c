#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
	
	mvaddstr(TEXT_MARGIN - 1, win_x / 2 - 11, ">> TERMINAL JUMPER! <<");
	mvaddstr(win_y - TEXT_MARGIN + 1, win_x / 2 - 13, ">> Use SPACE/UP to jump <<");
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

void game_over(int final_score, int win_y, int win_x) {
	// Clear the input buffer
	while(getch() != ERR);
	erase();
	print_edges(win_y, win_x);
	display_score(final_score);
	mvaddstr(win_y / 2, win_x / 2 - 5, "GAME OVER!");	
	mvaddstr(win_y / 2 + 1, win_x / 2 - 11, "Press any key to exit!");
	refresh();
	while(getch() == ERR);
	erase();
	refresh();
	beep();
	endwin();
	printf("GAME OVER!\nFinal Score:\t%d\n", final_score);
	exit(EXIT_SUCCESS);
}

void help(void) {
	puts("TERMINAL JUMPER:   A fun terminal hopping game.\n\nInstructions:\nUse SPACE/w/UP to jump (your preference). You should try to avoid obstacles, which look like '*'s. Each time you jump over an obstacle, you gain one point. Once you finally hit an obstacle, you will die, and be shown an end screen. If at any point you really need to fall, then press DOWN/s to quickly abort your jump and move down.\n\nHappy jumping!");
}
