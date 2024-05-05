#ifndef MAP_H
#define MAP_H

#include "../common.h"

#define MAP_WIDTH 120
#define MAP_HEIGHT 42

#define MAP_01_PATH "/home/stefano/Desktop/Progetto/maps/map_01.txt"

#define LAND_MAXY 9

#define LAND_BOUNDARIES(y) y >= 9 && y <= 32 ? false : true // this macro is FALSE if the given Y is not on LAND
#define WATER_BOUNDARIES(y) !LAND_BOUNDARIES(y)

#define LAND_PAIR 1
#define WATER_PAIR 2

#define LAND_SPRITE ' '
#define HARD_LAND_SPRITE '.'
#define WATER_SPRITE ' '
#define WAVE_SPRITE '~'

#define DENS_NUM 5

#define DEN_1_X 5
#define DEN_2_X 28
#define DEN_3_X 47
#define DEN_4_X 75
#define DEN_5_X 105

static char map[MAP_HEIGHT][MAP_WIDTH];

int m_load();

void m_render();

void m_init_dens(Entity dens[DENS_NUM]);

void m_close_dan(int dan_id);

void close_dan_1();
void close_dan_2();
void close_dan_3();
void close_dan_4();
void close_dan_5();

bool are_all_dens_closed(Entity dens[DENS_NUM]);

#endif