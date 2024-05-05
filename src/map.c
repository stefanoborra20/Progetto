#include "map.h"

int m_load() {
    FILE *map_file = fopen(MAP_01_PATH, "r");

    if (map_file == NULL) return -1;

    for (int i = 0; i < MAP_HEIGHT; i++) {
        fread(map[i], sizeof(char), MAP_WIDTH + 1, map_file);
    }

    fclose(map_file);

    return 0;
}

void m_render() {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            // check element type
            switch(map[i][j]) {
                case 'L': // Land
                    attron(COLOR_PAIR(LAND_PAIR));
                    mvaddch(i, j, LAND_SPRITE);
                    attroff(COLOR_PAIR(LAND_PAIR));
                    break;

                case 'H': // Hard Land
                    attron(COLOR_PAIR(LAND_PAIR));
                    mvaddch(i, j, HARD_LAND_SPRITE);
                    attroff(COLOR_PAIR(LAND_PAIR));
                    break;

                case 'W': // Water
                    attron(COLOR_PAIR(WATER_PAIR));
                    mvaddch(i, j, WATER_SPRITE);
                    attroff(COLOR_PAIR(WATER_PAIR));
                    break;

                case 'R': // Wave
                    attron(COLOR_PAIR(WATER_PAIR));
                    mvaddch(i, j, WAVE_SPRITE);
                    attroff(COLOR_PAIR(WATER_PAIR));
                    break;

                default:
                    mvaddch(i, j, '.');
                    break;
            }
        }
    }
}

void m_init_dens(Entity dens[DENS_NUM]) {
    dens[0].hb.x = DEN_1_X;
    dens[0].hb.y = 0;
    dens[0].hb.width = 7;
    dens[0].hb.height = 1;
    dens[0].to_display = true;

    dens[1].hb.x = DEN_2_X;
    dens[1].hb.y = 0;
    dens[1].hb.width = 7;
    dens[1].hb.height = 1;
    dens[1].to_display = true;

    dens[2].hb.x = DEN_3_X;
    dens[2].hb.y = 0;
    dens[2].hb.width = 7;
    dens[2].hb.height = 1;
    dens[2].to_display = true;

    dens[3].hb.x = DEN_4_X;
    dens[3].hb.y = 0;
    dens[3].hb.width = 7;
    dens[3].hb.height = 1;
    dens[3].to_display = true;

    dens[4].hb.x = DEN_5_X;
    dens[4].hb.y = 0;
    dens[4].hb.width = 7;
    dens[4].hb.height = 1;
    dens[4].to_display = true;
}

void m_close_dan(int dan_id) {
    switch(dan_id) {
        case 0: close_dan_1();
            break;
        case 1: close_dan_2();
            break;
        case 2: close_dan_3();
            break;
        case 3: close_dan_4();
            break;
        case 4: close_dan_5();
            break;
    }
}

void close_dan_1() {
    map[0][DEN_1_X] = 'L';
    map[0][DEN_1_X + 1] = 'L';
    map[0][DEN_1_X + 2] = 'L';
    map[0][DEN_1_X + 3] = 'L';
    map[0][DEN_1_X + 4] = 'L';
    map[0][DEN_1_X + 5] = 'L';
    map[0][DEN_1_X + 6] = 'L';
    map[0][DEN_1_X + 7] = 'L';
}

void close_dan_2() {
    map[0][DEN_2_X] = 'L';
    map[0][DEN_2_X + 1] = 'L';
    map[0][DEN_2_X + 2] = 'L';
    map[0][DEN_2_X + 3] = 'L';
    map[0][DEN_2_X + 4] = 'L';
    map[0][DEN_2_X + 5] = 'L';
    map[0][DEN_2_X + 6] = 'L';
    map[0][DEN_2_X + 7] = 'L';
}

void close_dan_3() {
    map[0][DEN_3_X] = 'L';
    map[0][DEN_3_X + 1] = 'L';
    map[0][DEN_3_X + 2] = 'L';
    map[0][DEN_3_X + 3] = 'L';
    map[0][DEN_3_X + 4] = 'L';
    map[0][DEN_3_X + 5] = 'L';
    map[0][DEN_3_X + 6] = 'L';
    map[0][DEN_3_X + 7] = 'L';
}

void close_dan_4() {
    map[0][DEN_4_X] = 'L';
    map[0][DEN_4_X + 1] = 'L';
    map[0][DEN_4_X + 2] = 'L';
    map[0][DEN_4_X + 3] = 'L';
    map[0][DEN_4_X + 4] = 'L';
    map[0][DEN_4_X + 5] = 'L';
    map[0][DEN_4_X + 6] = 'L';
    map[0][DEN_4_X + 7] = 'L';
}

void close_dan_5() {
    map[0][DEN_5_X] = 'L';
    map[0][DEN_5_X + 1] = 'L';
    map[0][DEN_5_X + 2] = 'L';
    map[0][DEN_5_X + 3] = 'L';
    map[0][DEN_5_X + 4] = 'L';
    map[0][DEN_5_X + 5] = 'L';
    map[0][DEN_5_X + 6] = 'L';
    map[0][DEN_5_X + 7] = 'L';
}

bool are_all_dens_closed(Entity dens[DENS_NUM]) {
    for (int i = 0; i < DENS_NUM; i++) {
        if (dens[i].to_display == true)
            return false;
    }

    return true;
}