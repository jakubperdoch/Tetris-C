#ifndef SHAPES_H
#define SHAPES_H

typedef enum
{
    PIECE_I, PIECE_O, PIECE_T,
    PIECE_S, PIECE_Z, PIECE_J, PIECE_L,
} ShapeType;

static const int SHAPES[7][2][4] = {
    // I
    {{0, 0, 0, 0}, {1, 1, 1, 1}},
    // O
    {{0, 1, 1, 0}, {0, 1, 1, 0}},
    // T
    {{0, 1, 0, 0}, {1, 1, 1, 0}},
    // S
    {{0, 1, 1, 0}, {1, 1, 0, 0}},
    // Z
    {{1, 1, 0, 0}, {0, 1, 1, 0}},
    // J
    {{1, 0, 0, 0}, {1, 1, 1, 0}},
    // L
    {{0, 0, 1, 0}, {1, 1, 1, 0}}
};

#endif
