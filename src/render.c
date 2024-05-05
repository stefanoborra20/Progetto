#include "render.h"

void r_render(Entity frog, Entity plants[3], Entity crocodiles[32], Entity bullets[4], int life, int time, int score) {
    render_info(life, time, score);
    m_render();

    render_plants(plants);
    render_crocodiles(crocodiles);
    render_frog(frog);
    render_bullets(bullets);
}

void render_frog(Entity frog) {
    for (int i = 0; i < frog.sprite_len; i++) {
        attron(COLOR_PAIR(frog.sprite[i].color_pair));
        mvaddch(frog.sprite[i].y, frog.sprite[i].x, frog.sprite[i].pixel);
        attroff(COLOR_PAIR(frog.sprite[i].color_pair));
    }
}

void render_plants(Entity plants[3]) {
    for (int i = 0; i < 3; i++) {
        if (plants[i].to_display == true) {
            for (int j = 0; j < plants[i].sprite_len; j++) {
                attron(COLOR_PAIR(plants[i].sprite[j].color_pair));
                mvaddch(plants[i].sprite[j].y, plants[i].sprite[j].x, plants[i].sprite[j].pixel);
                attroff(COLOR_PAIR(plants[i].sprite[j].color_pair));
            }
        }
    }
}

void render_crocodiles(Entity crocodiles[32]) {
    for (int i = 0; i < 32; i++) {
        if (crocodiles[i].to_display == true) {
            for (int j = 0; j < crocodiles[i].sprite_len; j++) {
                attron(COLOR_PAIR(crocodiles[i].sprite[j].color_pair));
                mvaddch(crocodiles[i].sprite[j].y, crocodiles[i].sprite[j].x, crocodiles[i].sprite[j].pixel);
                attroff(COLOR_PAIR(crocodiles[i].sprite[j].color_pair));
            }
        }
    }
}

void render_bullets(Entity bullets[4]) {
    for (int i = 0; i < 4; i++) {
        if (bullets[i].to_display == true) {
            attron(COLOR_PAIR(bullets[i].sprite[0].color_pair));
            mvaddch(bullets[i].sprite[0].y, bullets[i].sprite[0].x, bullets[i].sprite[0].pixel);
            attroff(COLOR_PAIR(bullets[i].sprite[0].color_pair));
        }
    }
}

void render_info(int life, int time, int score) {
    mvprintw(0, MAP_WIDTH + 1, "Life: %d", life);
    mvprintw(1, MAP_WIDTH + 1, "Time: %d", time);
    mvprintw(2, MAP_WIDTH + 1, "Score: %d", score);
}