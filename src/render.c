#include <stdlib.h>
#include "render.h"
#include "types.h"
#include "shapes.h"
#include "constants.h"

void render_shape(SDL_Renderer* renderer, Shape shape)
{
 for (int row = 0; row < 2; row++)
 {
  for (int col = 0; col < 4; col++)
  {
   if (SHAPES[shape.type][row][col])
   {
    SDL_Rect shape_piece = {
     SCREEN_OFFSET_X + (shape.x + col) * CELL_SIZE,
     SCREEN_OFFSET_Y + (shape.y + row) * CELL_SIZE,
     CELL_SIZE,
     CELL_SIZE
    };

    SDL_SetRenderDrawColor(renderer, shape.color.r, shape.color.g, shape.color.b, shape.color.a);
    SDL_RenderFillRect(renderer, &shape_piece);
    SDL_SetRenderDrawColor(renderer, 20, 20, 30, 255);
    SDL_RenderDrawRect(renderer, &shape_piece);
   }
  }
 }
}

Shape generate_random_shape()
{
 ShapeType type = rand() % PIECE_COUNT;

 return (Shape){
  .type = type,
  .rotation = rand() % 4,
  .color = SHAPE_COLORS[type],
  .x = rand() % (BOARD_WIDTH - 3),
  .y = 0
 };
}


