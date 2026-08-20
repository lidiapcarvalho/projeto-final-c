#include <ncurses.h>
#include "car.h"

int car_row;
int car_col;

void init_car()
{
    car_row = 7;
    car_col = 5;
    // 7 e 5, ainda são temporários
}

void draw_car()
{
    mvprintw(car_row, car_col, "@");
}

