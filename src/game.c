#include "game.h"
#include "constants.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "audio.h"
#include "render.h"
#include "board.h"
#include "input.h"
#include "shapes.h"

Game game_init()
{
    Game game = {};
    game.running = 1;

    if (SDL_Init(SDL_INIT_VIDEO))
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }

    if (init_font() != 0)
    {
        printf("Failed to initialize fonts!\n");
    }

    if (init_audio() != 0)
    {
        printf("Failed to initialize audio!\n");
    }

    game.window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                   SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!game.window)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }

    game.renderer = SDL_CreateRenderer(game.window, -1, SDL_RENDERER_ACCELERATED);
    if (!game.renderer)
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    }

    board_init(&game.board);

    return game;
}

void game_loop(Game* game)
{
    SDL_Event event;
    Shape shape = generate_random_shape(PIECE_COUNT);
    Shape next_shape = generate_random_shape(shape.type);

    Uint32 last_fall = SDL_GetTicks();

    while (game->running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                game->running = 0;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                handle_input(&shape, &game->board, &event);
            }
        }

        Uint32 now = SDL_GetTicks();
        if (now - last_fall >= delay_calcular(game->lines_cleared))
        {
            shape.y++;
            if (check_for_collision(&shape, &game->board))
            {
                shape.y--;
                lock_in_shape(&shape, &game->board);

                const int cleared = clear_lines(&game->board);
                if (cleared > 0) play_line_clear();
                game->lines_cleared += cleared;
                game->score += cleared * 100;

                shape = next_shape;
                next_shape = generate_random_shape(shape.type);

                if (check_for_collision(&shape, &game->board))
                {
                    play_gameover();
                    SDL_Delay(2000);
                    game->running = 0;
                }
            }
            last_fall = now;
        }

        SDL_SetRenderDrawColor(game->renderer, 20, 20, 30, 255);
        SDL_RenderClear(game->renderer);
        background_render(game->renderer);
        board_render(&game->board, game->renderer);
        render_ui(game->renderer, game->score, game->lines_cleared);
        render_shape(game->renderer, shape);
        render_next_shape(game->renderer, next_shape);
        SDL_RenderPresent(game->renderer);
    }
}

void game_clear(SDL_Renderer* renderer, SDL_Window* window)
{
    TTF_CloseFont(Font_secondary);
    TTF_CloseFont(Font_primary);
    TTF_Quit();
    cleanup_audio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int delay_calcular(int lines_cleared)
{
    int delay = FALL_DELAY - (lines_cleared / 5) * FALL_SPEED_MULTIPLIER;
    return delay > MIN_DELAY ? delay : MIN_DELAY;
}
