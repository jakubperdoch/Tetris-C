#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <SDL.h>

// ENUMS
typedef enum
{
    PIECE_I, PIECE_O, PIECE_T,
    PIECE_S, PIECE_Z, PIECE_J, PIECE_L,
    PIECE_COUNT
} ShapeType;

static const SDL_Color SHAPE_COLORS[7] = {
    {0, 255, 255, 255},
    {255, 255, 0, 255},
    {128, 0, 128, 255},
    {0, 255, 0, 255},
    {255, 0, 0, 255},
    {0, 0, 255, 255},
    {255, 165, 0, 255}
};

typedef enum
{
    SCREEN_MENU,
    SCREEN_GAME,
    SCREEN_SETTINGS,
    SCREEN_GAME_OVER
} GameScreen;

// TYPES
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

typedef struct
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    GameScreen current_screen;
    Board board;
    int running;
    int lines_cleared;
    int score;
} Game;

#endif
