#ifndef CROCODILE_H
#define CROCODILE_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "map.h"
#include "../common.h"

#define CROCODILE_PAIR 7
#define CROCODILE_EYE_BLACK 8
#define CROCODILE_EYE_WHITE 9
#define CROCODILE_EYE_RED 10
#define MAX_CROC_NUM 32

#define LANE_NUM 8
#define CROCODILE_LANE_1 0
#define CROCODILE_LANE_2 1
#define CROCODILE_LANE_3 2
#define CROCODILE_LANE_4 3
#define CROCODILE_LANE_5 4
#define CROCODILE_LANE_6 5
#define CROCODILE_LANE_7 6
#define CROCODILE_LANE_8 7

#define C_LANE1_Y 9
#define C_LANE2_Y 12
#define C_LANE3_Y 15
#define C_LANE4_Y 18
#define C_LANE5_Y 21
#define C_LANE6_Y 24
#define C_LANE7_Y 27
#define C_LANE8_Y 30

#define LEFT 1
#define RIGHT 2

int init_river(pid_t c_pids[MAX_CROC_NUM], int pipeout1[2], int pipeout2[2], pid_t f);

void c_init();

void c_loop(int pipeout, int pipeout2, int lane_num, int start_x, int direction, int speed, int unique, pid_t f_pid);

void c_move();

void frog_is_over();

#endif