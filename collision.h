#ifndef COLLISION_H
#define COLLISION_H

#include <stdbool.h>
#include "common.h"
#include "src/plants.h"
#include "src/crocodile.h"

bool is_colliding(Hitbox hb1, Hitbox hb2);

int check_river_collisions(Entity crocs[MAX_CROC_NUM], Entity frog);

int is_frog_in_den(Entity frog, Entity dens[DENS_NUM]);

#endif