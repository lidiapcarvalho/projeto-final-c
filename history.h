#ifndef HISTORY_H
#define HISTORY_H

#define MAX_RACES 10

extern double race_times[MAX_RACES];
extern int race_count;

void save_race_time(double race_time);
void draw_history(void);
void draw_history_recursive(int indice);

#endif
