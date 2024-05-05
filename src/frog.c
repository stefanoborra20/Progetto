#include "frog.h"

Frog f;
int is_f_shooting = false;
pid_t bullet_pid;

int pipeout;
int read_x_pipe;

void f_init(int x, int y) {
    f.pos.id = FROG_ID;

    if (f.pos.sprite == NULL) exit(1);

    f.pos.sprite[0].pixel = ' ';
	f.pos.sprite[0].x = x;
	f.pos.sprite[0].y = y;
    f.pos.sprite[0].color_pair = FROG_PAIR;

    f.pos.sprite[1].pixel = ' ';
	f.pos.sprite[1].x = x + 2;
	f.pos.sprite[1].y = y;
    f.pos.sprite[1].color_pair = FROG_PAIR;

    f.pos.sprite[2].pixel = ' ';
	f.pos.sprite[2].x = x + 4;
	f.pos.sprite[2].y = y;
    f.pos.sprite[2].color_pair = FROG_PAIR;

	f.pos.sprite[3].pixel = ' ';
	f.pos.sprite[3].x = x + 1;
	f.pos.sprite[3].y = y + 1;
    f.pos.sprite[3].color_pair = FROG_PAIR;

    f.pos.sprite[4].pixel = ' ';
	f.pos.sprite[4].x = x + 2;
	f.pos.sprite[4].y = y + 1;
    f.pos.sprite[4].color_pair = FROG_PAIR;

    f.pos.sprite[5].pixel = ' ';
	f.pos.sprite[5].x = x + 3;
	f.pos.sprite[5].y = y + 1;
    f.pos.sprite[5].color_pair = FROG_PAIR;

    f.pos.sprite[6].pixel = ' ';
	f.pos.sprite[6].x = x;
	f.pos.sprite[6].y = y + 2;
    f.pos.sprite[6].color_pair = FROG_PAIR;

    f.pos.sprite[7].pixel = ' ';
	f.pos.sprite[7].x = x + 4;
	f.pos.sprite[7].y = y + 2;
    f.pos.sprite[7].color_pair = FROG_PAIR;

    f.pos.sprite_len = 8;

    // hitbox
    f.pos.hb.x = x;
    f.pos.hb.y = y;
    f.pos.hb.width = 5;
    f.pos.hb.height = 3;
}

void f_init_pos(int x, int y) {
	f.pos.sprite[0].x = x;
	f.pos.sprite[0].y = y;

	f.pos.sprite[1].x = x + 2;
	f.pos.sprite[1].y = y;

	f.pos.sprite[2].x = x + 4;
	f.pos.sprite[2].y = y;

	f.pos.sprite[3].x = x + 1;
	f.pos.sprite[3].y = y + 1;

	f.pos.sprite[4].x = x + 2;
	f.pos.sprite[4].y = y + 1;

	f.pos.sprite[5].x = x + 3;
	f.pos.sprite[5].y = y + 1;

	f.pos.sprite[6].x = x;
	f.pos.sprite[6].y = y + 2;

	f.pos.sprite[7].x = x + 4;
	f.pos.sprite[7].y = y + 2;

    // hitbox
    f.pos.hb.x = x;
    f.pos.hb.y = y;
}

int f_move(int pipeout) {
    int key = getch();

    if (key == ' ')
        f_shoot(pipeout);

    for (int i = 0; i < f.pos.sprite_len; i++) {
        switch(key) {
            case KEY_UP:
                f.dir = UP;
                if (f.pos.hb.y > 0)
                    f.pos.sprite[i].y-= FROG_JUMP;

                break;

            case KEY_DOWN:
                f.dir = DOWN;
                if (f.pos.hb.y + f.pos.hb.height < MAP_HEIGHT)
                    f.pos.sprite[i].y += FROG_JUMP;

                break;

            case KEY_LEFT:
                f.dir = LEFT;
                if (f.pos.hb.x > 0)
                    f.pos.sprite[i].x -= FROG_SIDE_JUMP;

                break;

            case KEY_RIGHT:
                f.dir = RIGHT;
                if (f.pos.hb.x + f.pos.hb.width < MAP_WIDTH)
                    f.pos.sprite[i].x += FROG_SIDE_JUMP;

                break;

            default:
                break;
        }
    }

    // update hitbox
    f.pos.hb.x = f.pos.sprite[0].x; f.pos.hb.y = f.pos.sprite[0].y;
}

void f_shoot(int pipeout) {
    if (is_f_shooting == false) {
        is_f_shooting = true;

        bullet_pid = fork();

        if (bullet_pid == 0)
            shoot(f.pos.sprite[1].x, f.pos.sprite[1].y - 1, SHOOT_UP, FROG_BULLET, pipeout);
    }
}

void f_reset_pos() {
    f_init_pos(MAP_WIDTH / 2, MAP_HEIGHT - FROG_JUMP);
}

void f_reset_bullet() { // resetta la variabile is_f_shooting -> false
    is_f_shooting = false;
}

void read_x_coordinate() {
    int x;
    read(read_x_pipe, &x, sizeof(int));
    f_init_pos(x, f.pos.sprite[0].y);
    write(pipeout, &f.pos, sizeof(f.pos));
}

void f_loop(int pipe, int pipein) {
    signal(SIGUSR1, f_reset_bullet);
    signal(SIGUSR2, f_reset_pos);
    signal(SIGURG, read_x_coordinate);

    pipeout = pipe;
    read_x_pipe = pipein;

    f_init(MAP_WIDTH / 2, MAP_HEIGHT - FROG_JUMP);

    while (1) {
        f_move(pipeout);
        write(pipeout, &f.pos, sizeof(f.pos));

        usleep(15000);
    }
}