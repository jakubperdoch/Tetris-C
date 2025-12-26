
#include <stdbool.h>
#include <SDL.h>

typedef struct
{
    bool occupied;
    SDL_Color color;
} Board_Cell;

typedef struct
{
    Board_Cell cells[20][10];
} Board;

