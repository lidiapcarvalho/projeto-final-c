#include <ncurses.h>
#include "car.h"
#include "track.h"

int car_row;
int car_col;

void init_car()
{
    car_row = 8;
    car_col = 2;
}

void draw_car()
{
    mvprintw(car_row, car_col, "@");
}

void move_car(int key)
{
    int new_row = car_row;
    int new_col =  car_col;

    if (key == KEY_UP)
    {
        new_row--;
    }
    else if (key == KEY_DOWN)
    {
        new_row++;
    }
    else if (key == KEY_LEFT)
    {
        new_col--;
    }
    else if (key == KEY_RIGHT)
    {
        new_col++;
    }

    if (new_row >= 0 && new_row < 9 &&
        new_col >= 0 && new_col < 14)
    {
        if (track[new_row][new_col] == '#' ||
            track[new_row][new_col] == '=')
        {
            car_row = new_row;
            car_col = new_col;
        }
    }
    

}
