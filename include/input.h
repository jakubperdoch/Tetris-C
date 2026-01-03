#ifndef INPUT_H
#define INPUT_H

#include "types.h"
#include "render.h"

void handle_input(Shape* shape, Board* board, const SDL_Event* event, Game* game);
void handle_menu_input(SDL_Event* event, GameScreen* screen);

#endif

