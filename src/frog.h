#ifndef FROG_H
#define FROG_H

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "../common.h"
#include "bullet.h"

#define FROG_PAIR 3

#define FROG_JUMP 3
#define FROG_SIDE_JUMP 5

typedef enum {UP, DOWN, LEFT, RIGHT} Direction;

typedef struct {
    Entity pos;
    int speed;
    Direction dir;
} Frog;

void f_init(int x, int y);

int f_move(int pipeout);

void f_shoot(int pipeout);

void f_loop(int pipeout, int pipein);

#endif