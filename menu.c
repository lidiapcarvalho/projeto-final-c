#include <ncurses.h>
#include "menu.h"

int menu(void)
{
    int opcao;

    clear();

    mvprintw(2, 10, "CORRIDA!");
    mvprintw(4, 10, "1. Iniciar Corrida");
    mvprintw(5, 10, "2. Sair");
    mvprintw(7, 10, "Escolha uma opção: ");
    
    refresh();
    
    opcao = getch();
    
    return opcao;
}
