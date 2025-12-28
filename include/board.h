#include "types.h"

void board_init(Board* board);
void board_render(Board* board, SDL_Renderer* renderer);
bool board_cell_is_occupied(Board* board, int row, int col);
void board_set_cell(Board* board, int row, int col, SDL_Color color);
bool check_for_collision(Shape* shape, Board* board);

void lock_in_shape(Shape* shape, Board* board);
int clear_lines(Board* board);
