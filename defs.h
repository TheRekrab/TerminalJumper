#ifndef DEFS_H
#define DEFS_H

#define MARGIN 3
#define TEXT_MARGIN (MARGIN + 1)
#define FPS 2
#define MAX_OB_HEIGHT 4
#define JUMPLOG strcat(strdup(getenv("HOME")), "/.jumplog")
typedef struct {
	int x;
	int height;
}Obstacle;



#endif
