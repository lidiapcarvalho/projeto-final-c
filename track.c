#include <ncurses.h>
#include "track.h"

char track[9][14] =
{
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

void draw_track(void)
{
    // Matriz da pista
    for (int i = 0; i < 9; i++)
    {
        mvprintw(TRACK_START_ROW + i, 0, "%s", track[i]);
    }
    // Percorrer matriz

    // Desenhar cada carácter da pista
    
}



