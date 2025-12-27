#include <stdio.h>
#include <SDL.h>
#include <time.h>
#include "board.h"
#include "render.h"
#include "constants.h"


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

    Shape shape = {
        .type = PIECE_L,
        .y = 0,
        .x = rand() % (BOARD_WIDTH - 3),
        .rotation = 0,
        .color = {255, 255, 255, 255}
    };

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
        }

        SDL_SetRenderDrawColor(renderer, 20, 20, 30, 255);
        SDL_RenderClear(renderer);
        board_render(&board, renderer);
        render_shape(renderer, shape);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
