#include <ncurses.h>
#include "history.h"

double race_times[MAX_RACES];
int race_count = 0;

void save_race_time(double race_time)
{
    if (race_count < MAX_RACES)
    {
        race_times[race_count] = race_time;
        race_count++;
    }
}

void draw_history(void)
{
    clear();
    
    mvprintw(2, 10, "HISTÓRICO DE CORRIDAS");

    draw_history_recursive(0);

    refresh();
}

void draw_history_recursive(int indice)
{
    if (indice >= race_count)
    {
        return;
    }    
    mvprintw(4 + indice, 10, "Corrida %d: %.2f s",
            indice + 1,
        race_times[indice] / 1000.0);

    draw_history_recursive(indice + 1);
}
