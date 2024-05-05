#include "bullet.h"

Entity bullet;

void shoot(int x, int y, int direction, int id, int pipeout) {
    bullet.sprite[0].x = x; bullet.sprite[0].y = y;
    bullet.sprite->pixel = 'o';

    bullet.sprite_len = 1;
    bullet.id = BULLET_ID;
    bullet.u_id = id;
    bullet.to_display = true;

    // hitbox
    bullet.hb.x = x; bullet.hb.y = y;
    bullet.hb.width = 1; bullet.hb.height = 1;

    while (bullet.sprite[0].y > -1) { // oppure fino a quando non colpisce qualcosa
    
        if (direction == SHOOT_UP) bullet.sprite[0].y -= BULLET_SPEED;
        else                       bullet.sprite[0].y += BULLET_SPEED;

        // update hitbox
        bullet.hb.y = bullet.sprite[0].y;

        write(pipeout, &bullet, sizeof(bullet));

        usleep(BULLET_DELAY);

        if (bullet.sprite[0].y == -1 || bullet.sprite[0].y > MAP_HEIGHT - 1) {
            bullet.to_display = false;
            write(pipeout, &bullet, sizeof(bullet));
            exit(1);
        }
    }
}