#include "board.h"
#include "constants.h"
#include "SDL.h"
#include "shapes.h"

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

void board_render(const Board* board, SDL_Renderer* renderer)
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
                const SDL_Color color = board->cells[row][col].color;
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

    SDL_Rect rect = {SCREEN_OFFSET_X, SCREEN_OFFSET_Y, BOARD_WIDTH * CELL_SIZE, BOARD_HEIGHT * CELL_SIZE};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &rect);
}

bool board_cell_is_occupied(const Board* board, const int row, const int col)
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

bool check_for_collision(const Shape* shape, const Board* board)
{
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            if (SHAPES[shape->type][shape->rotation][row][col])
            {
                const int board_x = shape->x + col;
                const int board_y = shape->y + row;

                if (board_x < 0 || board_x >= BOARD_WIDTH ||
                    board_y >= BOARD_HEIGHT ||
                    board_cell_is_occupied(board, board_y, board_x))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void background_render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 25, 25, 35, 255);
    for (int x = 0; x < SCREEN_WIDTH; x += 20)
    {
        SDL_RenderDrawLine(renderer, x, 0, x, SCREEN_HEIGHT);
    }
    for (int y = 0; y < SCREEN_HEIGHT; y += 20)
    {
        SDL_RenderDrawLine(renderer, 0, y, SCREEN_WIDTH, y);
    }
}

void lock_in_shape(const Shape* shape, Board* board)
{
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            if (SHAPES[shape->type][shape->rotation][row][col])
            {
                board_set_cell(board, shape->y + row, shape->x + col, shape->color);
            }
        }
    }
}

int clear_lines(Board* board)
{
    int lines_cleared = 0;

    for (int row = BOARD_HEIGHT - 1; row >= 0; row--)
    {
        bool full = true;
        for (int col = 0; col < BOARD_WIDTH; col++)
        {
            if (!board_cell_is_occupied(board, row, col))
            {
                full = false;
                break;
            }
        }
        if (full)
        {
            for (int i = row; i > 0; i--)
            {
                for (int col = 0; col < BOARD_WIDTH; col++)
                {
                    board->cells[i][col] = board->cells[i - 1][col];
                }
            }
            for (int col = 0; col < BOARD_WIDTH; col++)
            {
                board->cells[0][col].occupied = false;
            }

            lines_cleared++;
            row++;
        }
    }

    return lines_cleared;
}
