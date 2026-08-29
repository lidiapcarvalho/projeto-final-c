#include <ncurses.h>
#include "track.h"
#include "car.h"
#include "game.h"
#include <locale.h>
#include <time.h>
#include "timer.h"
#include "menu.h"
#include "history.h"

int main(void)
{
    int key;

    setlocale(LC_ALL, "");

    initscr();
    start_color(); // sistema de cores

    init_pair(1, COLOR_RED, COLOR_BLACK);
    // par de cor nº 1, texto vermelho, fundo preto
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);


    // Menu
    int programa_ativo = 1;

    load_history();

    while (programa_ativo)
    {
        flushinp();
        // limpa todas as teclas que estejam pendentes no buffer de entrada, para evitar que a tecla ENTER da corrida anterior seja lida como opção do menu

        nodelay(stdscr, FALSE);
        timeout(-1);

        int opcao = menu();

        if (opcao == '3')
        {
            programa_ativo = 0;
            break;
        }

        if (opcao == '2')
        {
            draw_history();
            getch();
            continue;
        }

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

            if (race_started == 1)
            {
                draw_track();
                draw_car();
                draw_game();

                mvprintw(14, 0, "Tempo: %.2f s", race_time / 1000.0);
            }

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
                save_race_time(race_time);
                draw_results(race_time);
                napms(2000);
                break;
            }
            refresh();
        } // Fim do WHILE - corrida
    } // Fim do WHILE - programa

    endwin();
    return 0;
}

