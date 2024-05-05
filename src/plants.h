#ifndef PLANTS_H
#define PLANTS_H

#include <sys/types.h>
#include <sys/wait.h>
#include "bullet.h"
#include "map.h"
#include "../common.h"

#define PLANT_SPAWN_MAXX MAP_WIDTH - 4
#define PLANT_SPAWN_MAXY LAND_MAXY - 4 // -1 perche' per ora lo sprite della pianta e' alto 2

#define MIN_PLANT_NUM 3
#define FLOWER_PAIR 4
#define FLOWER_CENTER 5
#define PLANT_PAIR 6

void generate_plant_coordinates();

void p_init(int id);

void p_loop(int pipeout, int id);

void p_shoot(int x, int y, int id, int pipeout);

void p_decrement_life();

#endif