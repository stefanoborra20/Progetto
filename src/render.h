#ifndef RENDER_H
#define RENDER_H

#include "map.h"

void r_render(Entity frog, Entity plants[3], Entity crocodiles[32], Entity bullets[4], int life, int time, int score);

void render_frog(Entity frog);

void render_plants(Entity plants[3]);

void render_crocodiles(Entity crocodiles[32]);

void render_bullets(Entity bullets[4]);

void render_info(int life, int time, int score);

#endif