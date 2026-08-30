#include <ncurses.h>
#include "menu.h"

int menu(void)
{
    int opcao;

    clear();

    mvprintw(2, 10, "CORRIDA!");
    mvprintw(4, 10, "1. Iniciar Corrida");
    mvprintw(5, 10, "2. Histórico");
    mvprintw(6, 10, "3. Sair");
    mvprintw(7, 10, "Escolha uma opção: ");
    
    refresh();
    
    opcao = getch();
    
    return opcao;
}

void show_instructions(void)
{
    clear();

    mvprintw(3, 10, "INSTRUÇÕES");

    mvprintw(6, 10, "↑  Mover para cima");
    mvprintw(7, 10, "↓  Mover para baixo");
    mvprintw(8, 10, "←  Mover para a esquerda");
    mvprintw(9, 10, "→  Mover para a direita");

    mvprintw(11, 10, "Q / +  Aumentar velocidade");
    mvprintw(12, 10, "E / -  Diminuir velocidade");

    mvprintw(14, 10, "ESC  Interromper a corrida");

    mvprintw(17, 10, "Complete 3 voltas no menor tempo possível.");

    mvprintw(20, 10, "Prima ENTER para começar.");

    refresh();
}
