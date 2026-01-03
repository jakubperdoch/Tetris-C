#include "input.h"
#include "types.h"
#include "board.h"
#include "SDL.h"


void handle_input(Shape* shape, Board* board, const SDL_Event* event, GameScreen* screen)
{
    switch (event->key.keysym.sym)
    {
    case SDLK_LEFT:
        shape->x--;
        if (check_for_collision(shape, board))
            shape->x++;
        break;
    case SDLK_RIGHT:
        shape->x++;
        if (check_for_collision(shape, board))
            shape->x--;
        break;
    case SDLK_DOWN:
        shape->y++;
        if (check_for_collision(shape, board))
            shape->y--;
        break;
    case SDLK_SPACE:
        while (!check_for_collision(shape, board))
        {
            shape->y++;
        }
        shape->y--;
        break;
    case SDLK_z:
        shape->rotation = (shape->rotation + 3) % 4;
        if (check_for_collision(shape, board))
            shape->rotation = (shape->rotation + 1) % 4;
        break;
    case SDLK_x:
        shape->rotation = (shape->rotation + 1) % 4;
        if (check_for_collision(shape, board))
            shape->rotation = (shape->rotation + 3) % 4;
        break;
    case SDLK_ESCAPE:
        *screen = SCREEN_MENU;
        break;
    }
}

void handle_menu_input(SDL_Event* event, GameScreen* screen)
{
    if (event->type == SDL_KEYDOWN)
    {
        if (event->key.keysym.sym == SDLK_RETURN)
            *screen = SCREEN_GAME;
        else if (event->key.keysym.sym == SDLK_s)
            *screen = SCREEN_SETTINGS;
    }
}






