#include "board.h"
#include "constants.h"
#include "SDL.h"

void board_init(Board* board)
{
    for (int row = 0; row < BOARD_HEIGHT; row++)
        for (int col = 0; col < BOARD_WIDTH; col++)
        {
            {
                board->cells[row][col].occupied = false;
            }
        }
}

void board_render(Board* board, SDL_Renderer* renderer)
{
    for (int row = 0; row < BOARD_HEIGHT; row++)
    {
        for (int col = 0; col < BOARD_WIDTH; col++)
        {
            const int offset_x = (SCREEN_WIDTH - BOARD_WIDTH * CELL_SIZE) / 2;
            const int offset_y = (SCREEN_HEIGHT - BOARD_HEIGHT * CELL_SIZE) / 2;

            SDL_Rect cell = {
                offset_x + col * CELL_SIZE,
                offset_y + row * CELL_SIZE,
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

