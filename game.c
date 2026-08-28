#include <ncurses.h>
#include "game.h"
#include "car.h"
#include "track.h"

int lap;
int crossed_finish;
int previous_col;

int checkpoint;

int race_started = 0;
int race_finished;

void init_game(void)
{
    lap = 0;
    crossed_finish = 1;
    checkpoint = 0;
    race_finished = 0;
    race_started = 0;
}

void start_race(void)
{
    clear();

    mvprintw(0, 10, "PREPARE-SE!");

    // Cincos luzes apagadas
    attron(COLOR_PAIR(2) | A_BOLD);
    // A_BOLD -> torna a apresentação mais intensa
    mvprintw(1, 10, "[●] [●] [●] [●] [●]");
    attroff(COLOR_PAIR(2) | A_BOLD);

    refresh();
    napms(1000);

    // Acende as luzes uma a uma
    for (int i = 0; i < 5; i++)
    {
        attron(COLOR_PAIR(1) | A_BOLD);
        mvprintw(1, 10 + (i * 4), "[●]");
        attroff(COLOR_PAIR(1) | A_BOLD);

        refresh();
        napms(1000);
    }

    // Apaga as luzes
    mvprintw(0, 10, "                     ");
    mvprintw(1, 10, "                     ");

    refresh();
    napms(500);
}

void update_lap(void)
{
    // Checkpoint 1 - (6,0)
    if (checkpoints[car_row][car_col] == '1')
    {
        checkpoint = 1;
    }
    // Checkpoint 2 - (0,5)
    if (checkpoints[car_row][car_col] == '2' && checkpoint == 1)
    {
        checkpoint = 2;
    }
    // Checkpoint 3 - (4,10)
    if (checkpoints[car_row][car_col] == '3' && checkpoint == 2)
    {
        checkpoint = 3;
    }

    if (track[car_row][car_col] == '=')
    {
        if (checkpoint == 3 && crossed_finish == 0)
        {
            lap++;

            if (lap == 3)
            {
                race_finished = 1;
            }

            crossed_finish = 1;
            checkpoint = 0;
        }
        else
        {
            crossed_finish = 0;
        }
    }
}

void draw_game(void)
{
    if (race_finished == 1)
    {
        mvprintw(12, 0, "Corrida Terminada! 🏁");
    }
    else
    {
        mvprintw(12, 0, "Volta: %d/3", lap);
    }
}

// Ecrã de resultados - fim de corrida
void draw_results(double race_time)
{
    clear();
    mvprintw(3, 10, "CORRIDA TERMINADA!");
    mvprintw(5, 10, "Voltas: %d/3", lap);
    mvprintw(6, 10, "Tempo total: %.2f s", race_time / 1000.0);

    refresh();
}
