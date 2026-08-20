#include <ncurses.h>

int main(void)
{
    initscr();
    printw("Ncurses funciona!");
    refresh();
    getch();
    endwin();

    return 0;
}
