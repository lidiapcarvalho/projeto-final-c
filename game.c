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
}

void start_race(void)
{
    clear();

    mvprintw(0, 10, "PREPARE-SE!");

    attron(COLOR_PAIR(2) | A_BOLD);
    // A_BOLD -> torna a apresentação mais intensa
    mvprintw(1, 10, "[●] [●] [●] [●] [●]");
    attroff(COLOR_PAIR(2) | A_BOLD);

    refresh();
    napms(1000);

    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(1, 10, "[●]");
    attroff(COLOR_PAIR(1) | A_BOLD);

    refresh();
    napms(1000);

    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(1, 14, "[●]");
    attroff(COLOR_PAIR(1) | A_BOLD);

    refresh();
    napms(1000);

    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(1, 18, "[●]");
    attroff(COLOR_PAIR(1) | A_BOLD);

    refresh();
    napms(1000);
    
    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(1, 22, "[●]");
    attroff(COLOR_PAIR(1) | A_BOLD);

    refresh();
    napms(1000);

    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(1, 26, "[●]");
    attroff(COLOR_PAIR(1) | A_BOLD);
    
    refresh();
    napms(1000);

    attron(COLOR_PAIR(2));
    mvprintw(1, 10, "[●] [●] [●] [●] [●]");
    attroff(COLOR_PAIR(2));

    refresh();
    napms(500);
}

void update_lap(void)
{
    // Checkpoint 1 - (6,0)
    if (car_row == 6 && car_col == 0)
    {
        checkpoint = 1;
    }
    // Checkpoint 2 - (0,5)
    if (car_row == 0 && car_col == 5 && checkpoint == 1)
    {
        checkpoint = 2;
    }
    // Checkpoint 3 - (4,10)
    if (car_row == 4 && car_col == 10 && checkpoint == 2)
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
        mvprintw(14, 0, "Corrida Terminada! 🏁");
    }
    else
    {
        mvprintw(14, 0, "Volta: %d/3", lap);
    }
}
