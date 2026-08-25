#include <ncurses.h>
#include "track.h"
#include "car.h"
#include "game.h"
#include <locale.h>
#include <time.h>
#include "timer.h"

int main(void)
{
    int key;

    setlocale(LC_ALL, "");

    initscr();
    keypad(stdscr, TRUE);

    nodelay(stdscr, TRUE);
    timeout(100);

    init_car();
    init_game();

    double last_move = get_time_ms();
    double race_start = 0;
    
    while(1)
    {
        double current_time = get_time_ms();
        double elapsed_time = current_time - last_move;
        double race_time = 0;

        if (race_started == 1)
        {
            race_time = current_time - race_start;
        }

        // clear(); // temporário

        draw_track();
        draw_car();
        draw_game();

        mvprintw(13, 0, "Tempo: %.2f ms", race_time / 1000.0);
        mvprintw(14, 0, "Delay: %d ms", get_speed_delay());

        key = getch();

        // Iniciar corrida
        if (race_started == 0 && key == '\n')
        {
            start_race();

            race_started = 1;
            race_start = get_time_ms();
            last_move = race_start;
        }

        // Acelerar e travar
        if (key == 'q' || key == 'Q')
        {
            change_speed(1);
        }
        else if (key == 'e' || key == 'E')
        {
            change_speed(-1);
        }
        else if (key == '+')
        {
            change_speed(1);
        }
        else if (key == '-')
        {
            change_speed(-1);
        }

        // Comando de saída
        if (key == 27) // Esc
        {
            break;
        }

        if (key != ERR)
        {
            change_direction(key);
        }
        
        if (race_started == 1 && elapsed_time >= get_speed_delay())
        {
            move_car();
            update_lap();
            last_move = current_time;            
        }

        if (race_finished == 1)
        {
            draw_game();
            getch();
            break;
        }
        refresh();
    } // Fim do WHILE
    
    endwin();
    return 0;
}
