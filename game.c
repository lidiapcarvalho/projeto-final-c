#include <ncurses.h>
#include "game.h"
#include "car.h"
#include "track.h"

int lap;
int crossed_finish;
int previous_col;

int checkpoint;

void init_game(void)
{
    lap = 0;
    crossed_finish = 1;
    checkpoint = 0;
}

void update_lap(void)
{
    // Checkpoint 1
    if (car_row == 0 && car_col == 5)
    {
        checkpoint = 1;
    }
    // Checkpoint 2
    if (car_row == 0 && car_col == 5)
    {
        checkpoint = 2;
    }

    if (track[car_row][car_col] == '=')
    {
        if (checkpoint == 2 && crossed_finish == 0)
        {
            lap++;
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
    mvprintw(11, 0, "Volta: %d/3", lap);
}
