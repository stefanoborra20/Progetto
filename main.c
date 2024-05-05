#include "main.h"

int pipe_fds[2];
int pipe_2_fds[2];

int main() {
    pid_t frog_pid, plants_pid[MIN_PLANT_NUM], crocodiles_pid[MAX_CROC_NUM];
    
    win_setup();

    game_stats menu_selection = menu();

    if (menu_selection == QUIT) goto end;

    if (pipe(pipe_fds) == -1) goto end;
    if (pipe(pipe_2_fds) == -1) goto end;

    if (m_load() == -1) goto end;

    if (init_process(&frog_pid, plants_pid, crocodiles_pid) == -1)
        goto end;
    
    int res = logic(frog_pid, plants_pid, crocodiles_pid, pipe_fds[0], pipe_fds, pipe_2_fds);

    kill(frog_pid, 0);
    waitpid(frog_pid, NULL, WNOHANG);
    for (int i = 0; i < MIN_PLANT_NUM; i++) {
        kill(plants_pid[i], 0);
        waitpid(plants_pid[i], NULL, WNOHANG);
    }
    for (int i = 0; i < MAX_CROC_NUM; i++) {
        kill(crocodiles_pid[i], 0);
        waitpid(crocodiles_pid[i], NULL, WNOHANG);
    }
    
    game_over(res);

end:
    endwin();
    return 0;
}

int init_process(pid_t *f, pid_t p[MIN_PLANT_NUM], pid_t c[MAX_CROC_NUM]) {
    *f = fork();
    if (*f == 0) {
        close(pipe_fds[0]);
        close(pipe_2_fds[1]);
        f_loop(pipe_fds[1], pipe_2_fds[0]);
    }
    else if (*f < 0)
        return -1;
    
    for (int i = 0; i < MIN_PLANT_NUM; i++) {
        p[i] = fork();

        if (p[i] == 0) {
            close(pipe_fds[0]);
            p_loop(pipe_fds[1], i); // use index as ID
        }
        else if (p[i] < 0)
            return -1;
    }

    return 0;
}

void win_setup() {
    initscr();
    noecho();
    nodelay(stdscr, true);
    cbreak();
    curs_set(false);
    keypad(stdscr, true);

    start_color();

    init_color(COLOR_BROWN, 244, 164, 96);
    init_color(COLOR_BRIGHT_GREEN, 170, 255, 0);

    init_pair(LAND_PAIR, COLOR_BLACK, COLOR_BROWN);
    init_pair(WATER_PAIR, COLOR_WHITE, COLOR_BLUE);
    init_pair(FROG_PAIR, COLOR_BLACK, COLOR_GREEN);
    init_pair(FLOWER_PAIR, COLOR_BLACK, COLOR_YELLOW);
    init_pair(FLOWER_CENTER, COLOR_BLACK, COLOR_RED);
    init_pair(PLANT_PAIR, COLOR_WHITE, COLOR_GREEN);
    init_pair(CROCODILE_PAIR, COLOR_BLACK, COLOR_BRIGHT_GREEN);
    init_pair(CROCODILE_EYE_BLACK, COLOR_WHITE, COLOR_BLACK);
    init_pair(CROCODILE_EYE_WHITE, COLOR_BLACK, COLOR_WHITE);
    init_pair(CROCODILE_EYE_RED, COLOR_BLACK, COLOR_RED);

    srand(time(NULL));
}

int menu() {
    char title[11][100] = {
        " _____",                               
        "|  ___| __ ___   __ _  __ _  ___ _ __  __   _____",
        "| |_ | '__/ _ \\ / _` |/ _` |/ _ \\ '__| \\ \\ / / __|  ",
        "|  _|| | | (_) | (_| | (_| |  __/ |     \\ V /\\__ \\ ",
        "|_|  |_|  \\___/ \\__, |\\__,| \\___|_|      \\_/ |___/ ",
        "                |___/ |___/                       ",
        " ____  _             _       ",
        "|  _ \\| | __ _ _ __ | |_ ___ ",
        "| |_) | |/ _` | '_ \\| __/ __|",
        "|  __/| | (_| | | | | |_\\__ \\ ",
        "|_|   |_|\\__,_|_| |_|\\__|___/"
    };

    int y = 2;
    for (int i = 0; i < 11; i++) {
        mvaddstr(y, (COLS/2) - 25, title[i]);
        y++;
    }
    char *menu[2] = {"New Game", "Quit"};

    int input;
    int highlighted = 0;

    bkgd(COLOR_PAIR(0));

    mvprintw(LINES-2, 2, "Use SPACE BAR to select the option.");

    box(stdscr, '*', '*');

    while (true) {
        int i;
        for (i = 0; i < 2; i++) {
            if (i == highlighted) attron(A_REVERSE);
            mvprintw(LINES/2 + i, COLS/2 - 8, "%s", menu[i]);
            attroff(A_REVERSE);
        }
        
        input = getch();
        
        switch (input) {
            case KEY_UP:
                highlighted--;
                if (highlighted == -1) highlighted = 0;
                break;

            case KEY_DOWN:
                highlighted++;
                if (highlighted == 2) highlighted = 1;
                break;
            
            case ' ':
                if (highlighted == 0) return START_NEW_GAME;
                return QUIT;

            default:
                break;
        }
    }
}

void game_over(int score) {
    CLEAR_SCR

    char end_title[6][100] = {
        " _____                         ____",                 
        "/ ____|                       / __ \\",                
        "| |  __  __ _ _ __ ___   ___  | | | |_   _____ _ __", 
        "| | |_ |/ _` | '_ ` _ \\ / _ \\ | | | \\ \\ / / _ \\ '__|",
        "| |__| | (_| | | | | | |  __/ | |_| |\\ V /  __/ |",
        " \\_____|\\__,_|_| |_| |_|\\___| \\____/  \\_/ \\___|_|"
    };


    bkgd(COLOR_PAIR(0));

    while(getch() != ' ') {
        int y = 2;
        for (int i = 0; i < 6; i++) {
            mvaddstr(y, (COLS/2) - 25, end_title[i]);
            y++;
        }

        mvprintw(LINES-2, 2, "Use SPACE BAR to exit.");
        box(stdscr, '*', '*');

        mvprintw(LINES/2, COLS/2 - 10, "Your score is: %d", score);
    }
}