#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "types.h"


Game game_init();
void game_loop(Game* game);
void game_reset(Game* game);
void game_clear(SDL_Renderer* renderer, SDL_Window* window);
int delay_calcular(Game* game);
void load_scoreboard(Scoreboard* scoreboard);
void save_scoreboard(const Scoreboard* scoreboard);
void update_scoreboard(Scoreboard* scoreboard, int score);

void gameover_loop(Game* game);

#endif
