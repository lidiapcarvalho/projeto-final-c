#ifndef GAME_H
#define GAME_H

extern int race_started;
extern int race_finished;

void start_race(void);
void init_game(void);
void update_lap(void);
void draw_game(void);
void draw_results(double race_time);

#endif
