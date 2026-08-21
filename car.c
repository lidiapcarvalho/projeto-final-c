#include <ncurses.h>
#include "car.h"

int car_row;
int car_col;

void init_car()
{
    car_row = 8;
    car_col = 2;
    // 7 e 5, ainda são temporários
}

void draw_car()
{
    mvprintw(car_row, car_col, "@");
}

void move_car(int key)
{
    if (key == KEY_UP)
    {
        car_row--;
    }
    else if (key == KEY_DOWN)
    {
        car_row++;
    }
    else if (key == KEY_LEFT)
    {
        car_col--;
    }
    else if (key == KEY_RIGHT)
    {
        car_col++;
    }
}
