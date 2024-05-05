#ifndef LOGIC_H
#define LOGIC_H

#include <unistd.h>
#include <stdbool.h>
#include "render.h"
#include "frog.h"
#include "plants.h"
#include "crocodile.h"
#include "map.h"
#include "../collision.h"
#include "../common.h"

bool is_entity_in_water(int x, int y);

bool is_entity_on_land(int x, int y);

int restore_river(pid_t f_pid, pid_t c_pid[MAX_CROC_NUM], Entity crocodiles[MAX_CROC_NUM], int pipe_fds[2], int pipe_2_fds[2], int active_crocs);

int logic(pid_t f_pid, pid_t p_pid[MIN_PLANT_NUM], pid_t c_pid[MAX_CROC_NUM], int pipein, int pipe_fds[2], int pipe_2_fds[2]);

#endif