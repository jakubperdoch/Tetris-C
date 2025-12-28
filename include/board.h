#include "types.h"

void board_init(Board* board);
void board_render(const Board* board, SDL_Renderer* renderer);
bool board_cell_is_occupied(const Board* board, int row, int col);
void board_set_cell(Board* board, int row, int col, SDL_Color color);
bool check_for_collision(const Shape* shape, const Board* board);

void lock_in_shape(const Shape* shape, Board* board);
int clear_lines(Board* board);
