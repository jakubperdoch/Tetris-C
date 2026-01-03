#include <stdio.h>
#include <SDL.h>
#include <time.h>
#include "game.h"


int main(void)
{
    srand(time(NULL));
    int running = 1;


    Game game = game_init();
    game_loop(&game);
    game_clear(game.renderer, game.window);

    return 0;
}
