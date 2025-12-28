#include "input.h"
#include "types.h"
#include "SDL.h"


void handle_input(Shape* shape, const SDL_Event* event)
{
    switch (event->key.keysym.sym)
    {
    case SDLK_LEFT:
        shape->x--;
        break;
    case SDLK_RIGHT:
        shape->x++;
        break;
    case SDLK_DOWN:
        shape->y++;
        break;
    case SDLK_SPACE:
        // hard drop
        break;
    case SDLK_z:
        // rotate left
        break;
    case SDLK_x:
        // rotate right
        break;
    case SDLK_ESCAPE:
        break;
    }
}





