#include "logic.h"

bool is_entity_in_water(int x, int y) {
    return WATER_BOUNDARIES(y);
}

bool is_entity_on_land(int x, int y) {
    return LAND_BOUNDARIES(y);
}

void set_bullets_bkg(Entity *bullet) { // set bullet background
    for (int i = 0; i < bullet->sprite_len; i++) {
        if (is_entity_on_land(bullet->sprite[i].x, bullet->sprite[i].y) == true) bullet->sprite[i].color_pair = LAND_PAIR;
        else if (is_entity_in_water(bullet->sprite[i].x, bullet->sprite[i].y) == true) bullet->sprite[i].color_pair = WATER_PAIR;
    }
}

int restore_river(pid_t f_pid, pid_t c_pid[MAX_CROC_NUM], Entity crocodiles[MAX_CROC_NUM], int pipe_fds[2], int pipe_2_fds[2], int active_crocs) {
    for (int i = 0; i <= active_crocs; i++) { // reset crocs position
        kill(c_pid[i], SIGKILL);
        waitpid(c_pid[i], NULL, WNOHANG);
    }
    
    for (int i = 0; i < MAX_CROC_NUM; i++)
        crocodiles[i].to_display = false;

    return init_river(c_pid, pipe_fds, pipe_2_fds, f_pid);
}

int logic(pid_t f_pid, pid_t p_pid[MIN_PLANT_NUM], pid_t c_pid[MAX_CROC_NUM], int pipein, int pipe_fds[2], int pipe_2_fds[2]) {
    // game variables
    int life = 3;
    int score = 0;
    int active_crocs;
    bool is_f_immune = false; // if frog gets hit
    bool is_f_on_crocodile = false; // is frog on a crocodile
    int timer = 120;
    int immunity_timestamp;
    time_t current_time = time(NULL);

    Entity pos;
    Entity frog;
    Entity plants[MIN_PLANT_NUM] = {{.to_display = false}, {.to_display = false}, {.to_display = false}};
    Entity crocodiles[32] = {
        {.to_display = false}, {.to_display = false}, {.to_display = false}, {.to_display = false},
        {.to_display = false}, {.to_display = false}, {.to_display = false}, {.to_display = false},
        {.to_display = false}, {.to_display = false}, {.to_display = false}, {.to_display = false},
        {.to_display = false}, {.to_display = false}, {.to_display = false}, {.to_display = false}
    };
    Entity bullets[4] = {{.to_display = false}, {.to_display = false}, {.to_display = false}, {.to_display = false}};
    Entity dens[DENS_NUM];

    m_init_dens(dens);
    active_crocs = init_river(c_pid, pipe_fds, pipe_2_fds, f_pid);

    do {
        CLEAR_SCR

        if (read(pipein, &pos, sizeof(pos)) != -1) {

            if (pos.id == FROG_ID) frog = pos;
            else if (pos.id == PLANT_ID) plants[pos.u_id] = pos;
            else if (pos.id == CROCODILE_ID) crocodiles[pos.u_id] = pos;
            else if (pos.id == BULLET_ID) {
                set_bullets_bkg(&pos); // set right background
                bullets[pos.u_id] = pos;

                if (bullets[FROG_BULLET].to_display == false)
                    kill(f_pid, RESET_FROG_BULLET);
            }

            //tick
            if (time(NULL) - current_time >= 1) { // se e' passato un secondo
                timer--;
                current_time = time(NULL);

                if (current_time - immunity_timestamp >= IMMUNITY_SECONDS)
                    is_f_immune = false;
            }

            // infos
            mvprintw(5, MAP_WIDTH + 1, "p1 x:%d y:%d", plants[0].sprite[0].x, plants[0].sprite[0].y);
            mvprintw(6, MAP_WIDTH + 1, "p2 x:%d y:%d", plants[1].sprite[0].x, plants[1].sprite[0].y);
            mvprintw(7, MAP_WIDTH + 1, "p3 x:%d y:%d", plants[2].sprite[0].x, plants[2].sprite[0].y);

            int y = 9;
            for (int i = 0; i < 32; i++) {
                if (crocodiles[i].to_display == true)
                    mvprintw(y++, MAP_WIDTH + 1, "C%d x:%d y:%d", i, crocodiles[i].sprite[0].x, crocodiles[i].sprite[0].y);
            }

            mvprintw(35, MAP_WIDTH + 1, "Frog in water: %s", !is_entity_on_land(frog.hb.x, frog.hb.y) == true ? "yes" : "no");
            mvprintw(36, MAP_WIDTH + 1, "Frog on crocodile: %s", is_f_on_crocodile == true ? "yes" : "no");
            mvprintw(37, MAP_WIDTH + 1, "Frog is immune: %s", is_f_immune == true ? "yes" : "no");

            // render
            r_render(frog, plants, crocodiles, bullets, life, timer, score);
            REFRESH_SCR;

            // collisions
            if (pos.id == BULLET_ID && pos.to_display == true) { // bullet-frog collision
                if (is_colliding(pos.hb, frog.hb)) {
                    if (is_f_immune == false) {
                        life--;
                        is_f_immune = true;
                        immunity_timestamp = time(NULL);
                        kill(f_pid, RESET_FROG_POS); // reset frog position
                        active_crocs = restore_river(f_pid, c_pid, crocodiles, pipe_fds, pipe_2_fds, active_crocs);
                    }
                }

                // check frog bullet
                if (pos.u_id == FROG_BULLET && pos.to_display == true) { // plants-bullet collision
                    for (int i = 0; i < MIN_PLANT_NUM; i++) {
                        if (is_colliding(pos.hb, plants[i].hb)) {
                            kill(p_pid[i], DECREMENT_PLANT_LIFE); // decrement plant life
                            score += 100;
                        }
                    }
                }
            }
            
            if (!is_entity_on_land(frog.hb.x, frog.hb.y)) {
                 is_f_on_crocodile = false;

                // crocs-frog collision
                int croc_index = check_river_collisions(crocodiles, frog);
                if (croc_index != -1) {
                    kill(c_pid[croc_index], SEND_X_TO_FROG);
                    is_f_on_crocodile = true;
                }

                if (!is_f_on_crocodile) {
                    if (!is_f_immune) {
                        life--;
                        is_f_immune = true;
                        immunity_timestamp = time(NULL);
                    }
                        kill(f_pid, RESET_FROG_POS);
                        is_f_on_crocodile = false;
                        active_crocs = restore_river(f_pid, c_pid, crocodiles, pipe_fds, pipe_2_fds, active_crocs);
                    
                }
            }

            int den_index = is_frog_in_den(frog, dens);
            if (den_index != -1) {
                m_close_dan(den_index);
                dens[den_index].to_display = false;
                kill(f_pid, RESET_FROG_POS);
                active_crocs = restore_river(f_pid, c_pid, crocodiles, pipe_fds, pipe_2_fds, active_crocs);
                score += 400;
            }

            // win/lose conditions
            if (are_all_dens_closed(dens))
                return score;

            if (timer <= 0 || life <= 0)
                return score;
        }

    } while (1);
}