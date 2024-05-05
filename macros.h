#ifndef MACROS_H
#define MACROS_H

#include <ncurses.h>

// ncurses
#define CLEAR_SCR wclear(stdscr);
#define REFRESH_SCR wrefresh(stdscr);

#define COLOR_BROWN 20
#define COLOR_BRIGHT_GREEN 21

// delays
#define PLANT_DELAY 100000
#define CROCODILE_DELAY_1 100000
#define CROCODILE_DELAY_2 75000
#define CROCODILE_DELAY_3 120000
#define BULLET_DELAY 100000

// logic macros
#define IMMUNITY_SECONDS 5
#define RESET_FROG_BULLET SIGUSR1
#define RESET_FROG_POS SIGUSR2
#define BULLET_CHANGE_VISIBILITY SIGUSR1

#define SEND_X_TO_FROG SIGUSR1
#define RESET_CROC_POS SIGUSR2

#define DECREMENT_PLANT_LIFE SIGUSR1

#endif