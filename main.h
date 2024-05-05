#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdbool.h>
#include "common.h"

#include "src/frog.h"
#include "src/map.h"
#include "src/plants.h"
#include "src/crocodile.h"
#include "src/logic.h"

typedef enum {START_NEW_GAME, QUIT} game_stats;

void win_setup();

int menu();

void game_over(int score);

int init_process(pid_t *f, pid_t p[MIN_PLANT_NUM], pid_t c[MAX_CROC_NUM]);

#endif