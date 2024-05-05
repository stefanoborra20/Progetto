#ifndef BULLET_H
#define BULLET_H

#include <unistd.h>
#include <stdlib.h>
#include "../common.h"
#include "map.h"

#define PLANT_0_BULLET 0
#define PLANT_1_BULLET 1
#define PLANT_2_BULLET 2
#define FROG_BULLET 3

#define BULLET_SPEED 1

#define SHOOT_UP 1
#define SHOOT_DOWN 2

void shoot(int x, int y, int direction, int id, int pipeout);

#endif