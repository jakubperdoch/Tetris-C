#include <stdio.h>
#include <SDL.h>
#include <time.h>
#include "board.h"
#include "render.h"
#include "constants.h"
#include "input.h"

int score = 0;

int main(void)
{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    srand(time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO))
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    if (init_font() != 0)
    {
        printf("Failed to initialize fonts!\n");
        return 1;
    }

    Uint32 last_fall = SDL_GetTicks();
    window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    }

    int running = 1;
    SDL_Event event;

    Board board;
    board_init(&board);

    Shape shape = generate_random_shape();

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                handle_input(&shape, &board, &event);
            }
        }

        Uint32 now = SDL_GetTicks();
        if (now - last_fall >= FALL_DELAY)
        {
            shape.y++;
            if (check_for_collision(&shape, &board))
            {
                shape.y--;
                lock_in_shape(&shape, &board);
                shape = generate_random_shape();

                if (check_for_collision(&shape, &board))
                {
                    running = 0;
                }
            }
            last_fall = now;
        }

        SDL_SetRenderDrawColor(renderer, 20, 20, 30, 255);
        SDL_RenderClear(renderer);
        board_render(&board, renderer);
        render_ui(renderer, score);
        render_shape(renderer, shape);
        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(Font_secondary);
    TTF_CloseFont(Font_primary);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
