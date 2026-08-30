#ifndef HISTORY_H
#define HISTORY_H

#define MAX_RACES 10

extern double race_times[MAX_RACES];
extern char race_dates[MAX_RACES][11];
extern char race_hours[MAX_RACES][6];
extern int race_count;
extern double melhor_tempo_historico;
extern double pior_tempo_atual;

void save_race_time(double race_time);
void draw_history(void);
void draw_history_recursive(int indice);
void load_history(void);

#endif
