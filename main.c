#include <ncurses.h>
#include "track.h"
#include "car.h"
#include "game.h"
#include <locale.h>
#include <time.h>

int main(void)
{
    int key;

    setlocale(LC_ALL, "");

    initscr(); // Inicializa o ncurses
    keypad(stdscr, TRUE);

    nodelay(stdscr, TRUE);
    timeout(100);

    init_car();
    init_game();

    clock_t last_move = clock();
    
    while(1)
    {
        clock_t current_time = clock();
        double elapsed_time = (double)(current_time - last_move) / CLOCKS_PER_SEC * 1000;

        // clear(); // temporário

        draw_track();
        draw_car();
        draw_game();

        mvprintw(13, 0, "Tempo: %.2f ms", elapsed_time);
        mvprintw(14, 0, "Delay: %d ms", get_speed_delay());

        key = getch();

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
        
        if (elapsed_time >= get_speed_delay())
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
