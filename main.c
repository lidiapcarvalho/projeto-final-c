#include <ncurses.h>
#include "track.h"
#include "car.h"
#include "game.h"
#include <locale.h>
#include <time.h>
// Ferramentas relacionadas com tempo

int main(void)
{
    int key;

    setlocale(LC_ALL, "");
    // Diz ao C, para usar as definições de idioma/codificação que o sistema operativo está a usar
    // setlocale() -> configura o locale do programa
    // LC_ALL -> aplica a configuração a todas as categorias do locale
    // "" -> pede ao programa para usar o locale definido pelo ambiente/sistema operativo

    initscr(); // Inicializa o ncurses
    keypad(stdscr, TRUE);
    // Permite ao ncurses reconhecer corretamente as teclas especiais, como as setas
    nodelay(stdscr, TRUE);
    timeout(100);

    init_car();
    init_game();

    clock_t last_move = clock();
    // clock_t -> tipo de dado usado para guardar um valor produzido por clock()
    // clock() -> devolve um valor que representa tempo de CPU utilizado pelo programa desde que começou
    
    while(1)
    {
        clock_t current_time = clock();
        double elapsed_time = (double)(current_time - last_move) / CLOCKS_PER_SEC * 1000;

        // clear(); // temporário
        // Limpa o ecrã antes de desenharmos novamente
        draw_track();
        draw_car();
        draw_game();

        mvprintw(13, 0, "Tempo: %.2f ms", elapsed_time);
        mvprintw(14, 0, "Delay: %d ms", get_speed_delay());

        key = getch();
        // Faz o programa esperar por uma tecla.
        // Sem isto, o programa poderia desenhar a pista e terminar imediatamente

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
        // ERR -> constante do ncurses que significa, neste contexto, "não foi recebida nenhuma tecla"
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
    // Sai do modo ncurses e devolve o terminal ao estado normal
    return 0;
}
