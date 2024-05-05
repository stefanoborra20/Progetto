#include "plants.h"

Entity p;
int ticks;
int life;

void generate_plant_coordinates() {
    p.sprite[0].x = RAND(1, PLANT_SPAWN_MAXX);
    p.sprite[0].y = RAND(1, PLANT_SPAWN_MAXY);
    p.sprite[0].pixel = ' ';
    p.sprite[0].color_pair = FLOWER_PAIR;

    p.sprite[1].x = p.sprite[0].x + 1;
    p.sprite[1].y = p.sprite[0].y - 1;
    p.sprite[1].pixel = ' ';
    p.sprite[1].color_pair = FLOWER_PAIR;

    p.sprite[2].x = p.sprite[0].x + 1;
    p.sprite[2].y = p.sprite[0].y;
    p.sprite[2].pixel = ' ';
    p.sprite[2].color_pair = FLOWER_CENTER;

    p.sprite[3].x = p.sprite[0].x + 2;
    p.sprite[3].y = p.sprite[0].y;
    p.sprite[3].pixel = ' ';
    p.sprite[3].color_pair = FLOWER_PAIR;

    p.sprite[4].x = p.sprite[0].x + 1;
    p.sprite[4].y = p.sprite[0].y + 1;
    p.sprite[4].pixel = ' ';
    p.sprite[4].color_pair = FLOWER_PAIR;

    p.sprite[5].x = p.sprite[0].x + 2;
    p.sprite[5].y = p.sprite[0].y + 1;
    p.sprite[5].pixel = ' ';
    p.sprite[5].color_pair = PLANT_PAIR;

    p.sprite[6].x = p.sprite[0].x + 2;
    p.sprite[6].y = p.sprite[0].y + 2;
    p.sprite[6].pixel = ' ';
    p.sprite[6].color_pair = PLANT_PAIR;

    // hitbox
    p.hb.y = p.sprite[0].y - 1; p.hb.x = p.sprite[0].x;
    p.hb.width = 3; p.hb.height = 4;
}

void p_init(int id) {
    generate_plant_coordinates();
    p.id = PLANT_ID;
    p.u_id = id;

    p.sprite_len = 7;

    p.to_display = true;
    life = 1;
}

void p_loop(int pipeout, int id) {
    signal(SIGUSR1, p_decrement_life);

    srand(time(NULL) + getpid());

    p_init(id);

    do {
        write(pipeout, &p, sizeof(p));

        if (ticks++ == 100) {
            p_shoot(p.sprite[0].x, p.sprite[0].y + 1, p.u_id, pipeout);
            ticks = 0;
        }

        usleep(PLANT_DELAY);

        if (life <= 0) {
            p.to_display = false;
            p_init(id);
        }

    } while (1);
}

void p_shoot(int x, int y, int id, int pipeout) {
    pid_t bullet_pid;

    bullet_pid = fork();

    if (bullet_pid == 0)
        shoot(x, y, SHOOT_DOWN, id, pipeout);
}

void p_decrement_life() {
    life--;
}