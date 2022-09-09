#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <curses.h>
#include <sys/stat.h>
#include <string.h>
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

void display_score(int score, int top, int width) {
	mvprintw(MARGIN - 1, MARGIN, "SCORE: %d", score);
	mvprintw(MARGIN - 1, width - MARGIN - MARGIN - 10, "TOP SCORE:  %d", top);
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
	mvaddstr(win_y / 2, win_x / 2 - 5, "GAME OVER!");	
	mvaddstr(win_y / 2 + 1, win_x / 2 - 11, "Press any key to exit!");
	refresh();
	while(getch() == ERR);
	beep();
	endwin();
	printf("GAME OVER!\nFinal Score:\t%d\n", final_score);
	// Get user name
	FILE* fp = fopen(JUMPLOG, "a");
	if (fp == NULL) {
		printf("There was an error opening %s:\n", JUMPLOG);
		perror("fopen");
	}
	fprintf(fp, "%d\n",final_score);
	fclose(fp);
	exit(EXIT_SUCCESS);
}

void help(void) {
	puts("TERMINAL JUMPER:   A fun terminal hopping game.\n\nInstructions:\nUse SPACE/w/UP to jump (your preference). You should try to avoid obstacles, which look like '*'s. Each time you jump over an obstacle, you gain one point. Once you finally hit an obstacle, you will die, and be shown an end screen. If at any point you really need to fall, then press DOWN/s to quickly abort your jump and move down.\n\nHappy jumping!");
}

int topscore(int place) {
	struct stat sb;
	int result = stat(JUMPLOG, &sb);
	if (result == -1) {
		return 0;
	}
	int size = sb.st_size;
	FILE* fp = fopen(JUMPLOG, "r");
	if (fp == NULL) {
		return 0;
	}
	char scores[size];
	
	int top = 0;
	int second = 0;
	int third = 0;

	while(fgets(scores, size, fp)) {
		int new_score = atoi(scores);
		if (top < new_score) {
			third = second;
			second = top;
			top = new_score;
		} else if (second < new_score) {
			third = second;
			second = new_score;
		} else if (third < new_score) {
			third = new_score;
		}
	} 
	fclose(fp);
	switch(place) {
		case 1:
			return top;
			break;
		case 2:
			return second;
			break;
		case 3:
			return 3;
			break;
		default:
			return 0;
	}

}
