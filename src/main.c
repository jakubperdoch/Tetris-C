#include <stdio.h>
#include <SDL.h>
#include <time.h>
#include "game.h"
#include "menu.h"

int main(void)
{
    srand(time(NULL));

    Game game = game_init();

    while (game.running)
    {
        switch (game.current_screen)
        {
        case SCREEN_MENU:
            menu_loop(&game);
            break;
        case SCREEN_SETTINGS:
            break;
        case SCREEN_GAME:
            game_loop(&game);
            break;
        case SCREEN_GAME_OVER:
            // gameover_loop(&game);
            break;
        default:
            menu_loop(&game);
            break;
        }
    }

    game_clear(game.renderer, game.window);
    return 0;
}
