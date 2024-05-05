#ifndef COMMON_H
#define COMMON_H

#include <ncurses.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include "macros.h"

#define RAND(x, y) x + rand() % (y-x + 1)

#define FROG_ID 0
#define PLANT_ID 1
#define BULLET_ID 2
#define CROCODILE_ID 3

#define MAX_SPRITE_PIXELS 25

typedef struct {
    int x, y, width, height;
} Hitbox;

typedef struct {
    int x, y;
	char pixel;
	int color_pair;
} Pixel;

typedef struct {
    int id;
    Pixel sprite[MAX_SPRITE_PIXELS];
    int sprite_len;
    Hitbox hb;

    bool to_display;
    int u_id; //unique id (if necessary)
} Entity;

#endif