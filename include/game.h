#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "types.h"

typedef struct
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    Board board;
    int running;
    int lines_cleared;
    int score;
} Game;

Game game_init();
void game_loop(Game* game);
void game_clear(SDL_Renderer* renderer, SDL_Window* window);
int delay_calcular(int lines_cleared);

#endif
