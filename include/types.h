
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

typedef enum
{
    PIECE_I, PIECE_O, PIECE_T,
    PIECE_S, PIECE_Z, PIECE_J, PIECE_L,
    PIECE_COUNT
} PieceType;

typedef struct
{
    PieceType type;
    int x;
    int y;
    int rotation;
} Shape;

