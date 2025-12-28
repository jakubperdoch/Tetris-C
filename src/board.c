#include "board.h"
#include "constants.h"
#include "SDL.h"

void board_init(Board* board)
{
    for (int row = 0; row < BOARD_HEIGHT; row++)
        for (int col = 0; col < BOARD_WIDTH; col++)
        {
            {
                SDL_Color color = {0, 0, 255};
                board->cells[row][col].occupied = false;
                board->cells[row][col].color = color;
            }
        }
}

void board_render(Board* board, SDL_Renderer* renderer)
{
    for (int row = 0; row < BOARD_HEIGHT; row++)
    {
        for (int col = 0; col < BOARD_WIDTH; col++)
        {
            SDL_Rect cell = {
                SCREEN_OFFSET_X + col * CELL_SIZE,
                SCREEN_OFFSET_Y + row * CELL_SIZE,
                CELL_SIZE,
                CELL_SIZE
            };

            if (board->cells[row][col].occupied)
            {
                SDL_Color color = board->cells[row][col].color;
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 20, 20, 30, 255);
            }

            SDL_RenderFillRect(renderer, &cell);
            SDL_SetRenderDrawColor(renderer, 80, 80, 90, 255);
            SDL_RenderDrawRect(renderer, &cell);
        }
    }
}

bool board_cell_is_occupied(Board* board, int row, int col)
{
    if (row < 0 || row >= BOARD_HEIGHT || col < 0 || col >= BOARD_WIDTH)
    {
        return true;
    }
    return board->cells[row][col].occupied;
}

void board_set_cell(Board* board, int row, int col, SDL_Color color)
{
    board->cells[row][col].occupied = true;
    board->cells[row][col].color = color;
}

bool check_for_collision(Shape* shape, Board* board)
{
    for (int row = 0; row < 2; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            if (SHAPES[shape->type][row][col])
            {
                const int board_x = shape->x + col;
                const int board_y = shape->y + row;

                if (board_x < 0 || board_x >= BOARD_WIDTH ||
                    board_y >= BOARD_HEIGHT || board_cell_is_occupied(board, row, col))
                {
                    return true;
                }
            }
        }
    }
}

