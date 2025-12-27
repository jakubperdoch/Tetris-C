#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <SDL.h>
#include "shapes.h"

typedef struct
{
    bool occupied;
    SDL_Color color;
} Board_Cell;

typedef struct
{
    Board_Cell cells[20][10];
} Board;

typedef struct
{
    ShapeType type;
    int x;
    int y;
    int rotation;
    SDL_Color color;
} Shape;

#endif
