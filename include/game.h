#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "types.h"


Game game_init();
void game_loop(Game* game);
void game_clear(SDL_Renderer* renderer, SDL_Window* window);
int delay_calcular(int lines_cleared);

#endif
