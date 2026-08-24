#include <ncurses.h>
#include "car.h"
#include "track.h"

int car_row;
int car_col;
int speed;
int direction;

void init_car()
{
    car_row = 8;
    car_col = 2;

    speed = 1;

    direction = KEY_UP;
}

void change_speed(int value)
{
    speed += value;

    if (speed < 1)
    {
        speed = 1;
    }
    else if (speed > 3)
    {
        speed = 3;
    }
}

void draw_car()
{
    mvprintw(car_row, car_col, "@");

    mvprintw(12, 0, "Velocidade: %d00 km/h", speed);
}

void move_car(int key)
{
    int new_row = car_row;
    int new_col =  car_col;

    // Direção do carro (já com possível adaptação para multiplayer)
    if (key == KEY_UP || key == 'w' || key == 'W')
    // 'w' -> um carácter - char
    // "w" -> uma string - char*
    {
        new_row--;
    }
    else if (key == KEY_DOWN || key == 's' || key == 'S')
    {
        new_row++;
    }
    else if (key == KEY_LEFT || key == 'a' || key == 'A')
    {
        new_col--;
    }
    else if (key == KEY_RIGHT || key == 'd' || key == 'D')
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

int get_speed_delay(void)
{
    if (speed ==1)
    {
        return 300;
    }
    else if (speed == 2)
    {
        return 200;
    }
    else
    {
        return 100;
    }
}
