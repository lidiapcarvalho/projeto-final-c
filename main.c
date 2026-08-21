#include <ncurses.h>
#include "track.h"
#include "car.h"

int main(void)
{
    int key;

    initscr(); // Inicializa o ncurses
    keypad(stdscr, TRUE);
    // Permite ao ncurses reconhecer corretamente as teclas especiais, como as setas

    init_car();

    while(1)
    {
        clear();
        // Limpa o ecrã antes de desenharmos novamente
        
        draw_track();
        draw_car();

        key = getch();
        // Faz o programa esperar por uma tecla.
        // Sem isto, o programa poderia desenhar a pista e terminar imediatamente

        move_car(key);
    }
    
    endwin();
    // Sai do modo ncurses e devolve o terminal ao estado normal
    return 0;
}
