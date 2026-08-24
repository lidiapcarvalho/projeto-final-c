#include <ncurses.h>
#include "track.h"
#include "car.h"
#include "game.h"
#include <locale.h>

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
    timeout(100);

    init_car();
    init_game();

    while(1)
    {
        clear();
        // Limpa o ecrã antes de desenharmos novamente
        draw_track();
        draw_car();
        draw_game();

        timeout(get_speed_delay());

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
            move_car(key);
        }
        update_lap();

        if (race_finished == 1)
        {
            draw_game();
            getch();
            break;
        }
        refresh();
    }
    
    endwin();
    // Sai do modo ncurses e devolve o terminal ao estado normal
    return 0;
}
