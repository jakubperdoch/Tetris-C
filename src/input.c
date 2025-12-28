#include "input.h"
#include "types.h"
#include "board.h"
#include "SDL.h"


void handle_input(Shape* shape, Board* board, const SDL_Event* event)
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
        // hard drop
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
        break;
    }
}





