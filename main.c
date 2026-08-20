#include <ncurses.h>
#include "track.h"
#include "car.h"

int main(void)
{
    initscr(); // Inicializa o ncurses

    init_car();
    draw_track();
    draw_car();

    getch(); 
    // Faz o programa esperar por uma tecla.
    // Sem isto, o programa poderia desenhar a pista e terminar imediatamente
    endwin();
    // Sai do modo ncurses e devolve o terminal ao estado normal
    return 0;
}
