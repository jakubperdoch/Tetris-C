#include "menu.h"
#include "render.h"
#include "constants.h"
#include "board.h"

void menu_loop(Game* game)
{
    SDL_Event event;
    int selected = 0;
    const char* options[] = {"Play", "Settings", "Quit"};
    int option_count = 3;

    load_scoreboard(&game->scoreboard);
    while (game->running && game->current_screen == SCREEN_MENU)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                game->running = 0;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    selected = (selected - 1 + option_count) % option_count;
                    break;
                case SDLK_DOWN:
                    selected = (selected + 1) % option_count;
                    break;
                case SDLK_RETURN:
                    if (selected == 0)
                    {
                        game->current_screen = SCREEN_GAME;
                    }
                    else if (selected == 1)
                    {
                        game->current_screen = SCREEN_SETTINGS;
                    }
                    else if (selected == 2)
                    {
                        game->running = 0;
                    }
                    break;
                case SDLK_ESCAPE:
                    game->running = 0;
                    break;
                }
            }
        }

        SDL_SetRenderDrawColor(game->renderer, 20, 20, 30, 255);
        SDL_RenderClear(game->renderer);
        background_render(game->renderer);

        SDL_Color white = {255, 255, 255, 255};
        SDL_Color gray = {100, 100, 100, 255};
        SDL_Color gold = {255, 215, 0, 255};
        SDL_Color silver = {192, 192, 192, 255};
        SDL_Color bronze = {205, 127, 50, 255};

        render_text(game->renderer, Font_primary, "TetriC", SCREEN_WIDTH / 4, 150, white);

        for (int i = 0; i < option_count; i++)
        {
            SDL_Color color = (i == selected) ? white : gray;
            char text[32];
            sprintf(text, "%s %s", (i == selected) ? "> " : " ", options[i]);
            render_text(game->renderer, Font_secondary, text, SCREEN_WIDTH / 4, 220 + i * 50, color);
        }

        if (game->scoreboard.count > 0 && game->scoreboard.scores[0] > 0)
        {
            for (int i = 0; i < game->scoreboard.count; i++)
            {
                if (game->scoreboard.scores[i] > 0)
                {
                    SDL_Color color = (i == 0) ? gold : (i == 1) ? silver : bronze;
                    char text[32];
                    sprintf(text, "%s %d %d", "Top", i+1, game->scoreboard.scores[i]);
                    render_text(game->renderer, Font_secondary, text, SCREEN_WIDTH - SCREEN_OFFSET_X, 150 + i * 50,
                                color);
                }
            }
        }
        else
        {
            render_text(game->renderer, Font_secondary, "No scores yet!", SCREEN_WIDTH - SCREEN_OFFSET_X, 150, white);
        }

        SDL_RenderPresent(game->renderer);
    }
}

