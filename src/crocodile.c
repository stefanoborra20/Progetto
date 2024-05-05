#include "crocodile.h"

Entity c;
bool is_croc_bad;
int lane;
int dir;
int c_speed;
int sx;

bool is_f_over_me = false;
pid_t f_pid;

int g_pipeout;
int send_x_pipe;

int init_river(pid_t c_pids[MAX_CROC_NUM], int pipeout1[2], int pipeout2[2], pid_t f) {
    int count = -1;
    for (int i = 0; i < LANE_NUM; i++) {
        int c_num = RAND(1, 3);
        int start_x = 0;
        int dir = RAND(1, 2);
        int speed = RAND(1, 3);

        for (int j = 0; j < c_num; j++){
            count++;
            c_pids[count] = fork();

            int distance = RAND(1, (MAP_WIDTH / 3));
            if (j != 0)
                start_x += 10 + distance;

            if (c_pids[count] == 0) {
                close(pipeout1[0]);
                close(pipeout2[0]);
                c_loop(pipeout1[1], pipeout2[1], i, start_x, dir, speed, count, f);
            }
            else if (c_pids[i] < 0)
                return -1;
        }
    }

    return count; // ritorna il numero di coccodrilli attivi
}

void c_init() {
    int x = sx;
    int y;
    switch (lane) {
        case CROCODILE_LANE_1: y = C_LANE1_Y; break;
        case CROCODILE_LANE_2: y = C_LANE2_Y; break;
        case CROCODILE_LANE_3: y = C_LANE3_Y; break;
        case CROCODILE_LANE_4: y = C_LANE4_Y; break;
        case CROCODILE_LANE_5: y = C_LANE5_Y; break;
        case CROCODILE_LANE_6: y = C_LANE6_Y; break;
        case CROCODILE_LANE_7: y = C_LANE7_Y; break;
        case CROCODILE_LANE_8: y = C_LANE8_Y; break;
    }

    c.id = CROCODILE_ID;
    //init sprite
    c.sprite[0].x = x;
    c.sprite[0].y = y;
    c.sprite[0].pixel = ' ';
    c.sprite[0].color_pair = CROCODILE_PAIR;

    c.sprite[1].x = x + 1;
    c.sprite[1].y = y;
    c.sprite[1].pixel = ' ';
    c.sprite[1].color_pair = CROCODILE_PAIR;

    c.sprite[2].x = x + 2;
    c.sprite[2].y = y;
    c.sprite[2].pixel = ' ';
    c.sprite[2].color_pair = is_croc_bad == true ? CROCODILE_EYE_RED : CROCODILE_EYE_BLACK;

    c.sprite[3].x = x + 3;
    c.sprite[3].y = y;
    c.sprite[3].pixel = ' ';
    c.sprite[3].color_pair = CROCODILE_EYE_WHITE;

    c.sprite[4].x = x + 4;
    c.sprite[4].y = y;
    c.sprite[4].pixel = ' ';
    c.sprite[4].color_pair = CROCODILE_PAIR;

    c.sprite[5].x = x + 5;
    c.sprite[5].y = y;
    c.sprite[5].pixel = ' ';
    c.sprite[5].color_pair = CROCODILE_PAIR;

    c.sprite[6].x = x + 6;
    c.sprite[6].y = y;
    c.sprite[6].pixel = ' ';
    c.sprite[6].color_pair = CROCODILE_PAIR;

    c.sprite[7].x = x + 7;
    c.sprite[7].y = y;
    c.sprite[7].pixel = ' ';
    c.sprite[7].color_pair = CROCODILE_PAIR;

    c.sprite[8].x = x + 2;
    c.sprite[8].y = y + 1;
    c.sprite[8].pixel = ' ';
    c.sprite[8].color_pair = CROCODILE_PAIR;

    c.sprite[9].x = x + 3;
    c.sprite[9].y = y + 1;
    c.sprite[9].pixel = ' ';
    c.sprite[9].color_pair = CROCODILE_PAIR;

    c.sprite[10].x = x + 4;
    c.sprite[10].y = y + 1;
    c.sprite[10].pixel = ' ';
    c.sprite[10].color_pair = CROCODILE_PAIR;

    c.sprite[11].x = x + 5;
    c.sprite[11].y = y + 1;
    c.sprite[11].pixel = ' ';
    c.sprite[11].color_pair = CROCODILE_PAIR;

    c.sprite[12].x = x + 6;
    c.sprite[12].y = y + 1;
    c.sprite[12].pixel = ' ';
    c.sprite[12].color_pair = CROCODILE_PAIR;

    c.sprite[13].x = x + 7;
    c.sprite[13].y = y + 1;
    c.sprite[13].pixel = ' ';
    c.sprite[13].color_pair = CROCODILE_PAIR;

    c.sprite[14].x = x + 8;
    c.sprite[14].y = y + 1;
    c.sprite[14].pixel = ' ';
    c.sprite[14].color_pair = CROCODILE_PAIR;

    c.sprite[15].x = x;
    c.sprite[15].y = y + 2;
    c.sprite[15].pixel = ' ';
    c.sprite[15].color_pair = CROCODILE_PAIR;

    c.sprite[16].x = x + 1;
    c.sprite[16].y = y + 2;
    c.sprite[16].pixel = ' ';
    c.sprite[16].color_pair = CROCODILE_PAIR;

    c.sprite[17].x = x + 2;
    c.sprite[17].y = y + 2;
    c.sprite[17].pixel = ' ';
    c.sprite[17].color_pair = CROCODILE_PAIR;

    c.sprite[18].x = x + 3;
    c.sprite[18].y = y + 2;
    c.sprite[18].pixel = ' ';
    c.sprite[18].color_pair = CROCODILE_PAIR;

    c.sprite[19].x = x + 4;
    c.sprite[19].y = y + 2;
    c.sprite[19].pixel = ' ';
    c.sprite[19].color_pair = CROCODILE_PAIR;

    c.sprite[20].x = x + 5;
    c.sprite[20].y = y + 2;
    c.sprite[20].pixel = ' ';
    c.sprite[20].color_pair = CROCODILE_PAIR;

    c.sprite[21].x = x + 6;
    c.sprite[21].y = y + 2;
    c.sprite[21].pixel = ' ';
    c.sprite[21].color_pair = CROCODILE_PAIR;

    c.sprite[22].x = x + 7;
    c.sprite[22].y = y + 2;
    c.sprite[22].pixel = ' ';
    c.sprite[22].color_pair = CROCODILE_PAIR;

    c.sprite[23].x = x + 8;
    c.sprite[23].y = y + 2;
    c.sprite[23].pixel = ' ';
    c.sprite[23].color_pair = CROCODILE_PAIR;

    c.sprite[24].x = x + 9;
    c.sprite[24].y = y + 2;
    c.sprite[24].pixel = ' ';
    c.sprite[24].color_pair = CROCODILE_PAIR;

    c.sprite_len = 25;

    c.to_display = true;

    c.hb.x = x;
    c.hb.y = y;
    c.hb.width = 10;
    c.hb.height = 3;
}

void c_loop(int pipeout, int pipeout2, int lane_num, int start_x, int direction, int speed, int unique, pid_t frog_pid) {
    signal(SIGUSR1, frog_is_over);

    srand(time(NULL) + getpid());

    g_pipeout = pipeout;
    send_x_pipe = pipeout2;
    f_pid = frog_pid;

    is_croc_bad = RAND(1, 2) == 1 ? true : false;
    lane = lane_num;
    sx = start_x;
    dir = direction;
    c.u_id = unique;
    switch(speed) { case 1: c_speed = CROCODILE_DELAY_1; break;
                    case 2: c_speed = CROCODILE_DELAY_2; break; 
                    case 3: c_speed = CROCODILE_DELAY_3; break; };
    c_init();

    do {
        c_move();
    } while (1);
    
}

void c_move() {
    for (int i = 0; i < c.sprite_len; i++) {
        if (c.sprite[i].x == 0 && dir == LEFT)
            c.sprite[i].x = MAP_WIDTH - 1;
        else if (c.sprite[i].x == MAP_WIDTH - 1 && dir == RIGHT)
            c.sprite[i].x = 0;
        else
            c.sprite[i].x += dir == LEFT ? -1 : 1;
    }

    c.hb.x = c.sprite[0].x; c.hb.y = c.sprite[0].y;

    if (is_croc_bad) {
        if (RAND(1, 100) <= 2) // 2% di possibilita' che il coccodrillo si immerga
            c.to_display = false;
    }

    usleep(c_speed);

    write(g_pipeout, &c, sizeof(c));

    if (is_croc_bad && c.to_display == false)
        c.to_display = true;
}

void frog_is_over() {
    if ((dir == LEFT && c.hb.x > 0) ||
        (dir == RIGHT && c.hb.x + c.hb.width <= MAP_WIDTH)) {
            write(send_x_pipe, &c.sprite[1].x, sizeof(int));
            kill(f_pid, SIGURG);
    }

    c_move();
}