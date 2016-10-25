#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

void minimax(Grid& grid, Color color_player)
{
    int AI_Play;
    /* initialize random seed: */
    srand (time(NULL));

    /* generate secret number between 0 and grid size: */
    AI_Play = rand() % grid.size() + 0;
    play(grid, AI_Play, color_player)
}


