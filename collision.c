#include "collision.h"

bool is_colliding(Hitbox hb1, Hitbox hb2) {
    if (hb1.x < hb2.x + hb2.width &&
        hb1.x + hb1.width > hb2.x &&
        hb1.y < hb2.y + hb2.height &&
        hb1.y + hb1.height > hb2.y)
            return true;
    return false;
}

int check_river_collisions(Entity crocs[MAX_CROC_NUM], Entity frog) {
    for (int i = 0; i < MAX_CROC_NUM; i++) {
        if (crocs[i].to_display == true) {
            if (is_colliding(frog.hb, crocs[i].hb))
                return i;
        }
    }

    return -1;
}

int is_frog_in_den(Entity frog, Entity dens[DENS_NUM]) {
    for (int i = 0; i < DENS_NUM; i++) { // is frog in den
        if (dens[i].to_display == true)
            if (is_colliding(dens[i].hb, frog.hb))
                return i;
    }

    return -1;
}