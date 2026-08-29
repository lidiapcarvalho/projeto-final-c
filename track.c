#include <ncurses.h>
#include "track.h"

char track[9][14] =
{
    // "#" = pista | "=" = linha de meta | espaço = fora da pista
    "  ###########",
    "  #         #",
    "  #         #",
    "  #         #",
    "###     #####",
    "#       #    ",
    "#       #    ",
    "#       #    ",
    "###===###    "
};

char checkpoints[9][14] =
{
    "     2       ",
    "             ",
    "             ",
    "             ",
    "          3  ",
    "             ",
    "1            ",
    "             ",
    "             "
};


void draw_track(void)
{
    // Matriz da pista
    attron(COLOR_PAIR(2));

    for (int i = 0; i < 9; i++)
    {
        mvprintw(TRACK_START_ROW + i, 0, "%s", track[i]);
    }

    attroff(COLOR_PAIR(2));    
}



