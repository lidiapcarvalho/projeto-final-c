#ifndef CAR_H
#define CAR_H

extern int car_row;
extern int car_col;
extern int speed;
extern int direction;

void init_car(void);
void change_speed(int value);
void draw_car(void);
void move_car(void);
int get_speed_delay(void);
void change_direction(int key);

#endif
