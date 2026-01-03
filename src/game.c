#include "game.h"
#include "constants.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "audio.h"
#include "render.h"
#include "board.h"
#include "input.h"
#include "shapes.h"
#include "settings.h"

Game game_init()
{
    Game game = {};
    game.running = 1;
    game.current_screen = SCREEN_MENU;

    load_settings(&game.settings);

    if (SDL_Init(SDL_INIT_VIDEO))
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }

    if (init_font() != 0)
    {
        printf("Failed to initialize fonts!\n");
    }

    if (init_audio() != 0)
    {
        printf("Failed to initialize audio!\n");
    }

    game.window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                   SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!game.window)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }

    game.renderer = SDL_CreateRenderer(game.window, -1, SDL_RENDERER_ACCELERATED);
    if (!game.renderer)
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    }

    load_scoreboard(&game.scoreboard);
    board_init(&game.board);

    return game;
}

void game_loop(Game* game)
{
    Shape shape = generate_random_shape(PIECE_COUNT);
    Shape next_shape = generate_random_shape(shape.type);
    SDL_Event event;


    Uint32 last_fall = SDL_GetTicks();

    if (game->settings.music)
    {
        play_soundtrack();
    }

    while (game->running && game->current_screen == SCREEN_GAME)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                game->running = 0;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                handle_input(&shape, &game->board, &event, game);
            }
        }

        Uint32 now = SDL_GetTicks();
        if (now - last_fall >= delay_calcular(game))
        {
            shape.y++;
            if (check_for_collision(&shape, &game->board))
            {
                shape.y--;
                lock_in_shape(&shape, &game->board);

                const int cleared = clear_lines(&game->board);
                if (cleared > 0) play_line_clear();
                game->lines_cleared += cleared;
                game->score += cleared * 100;

                shape = next_shape;
                next_shape = generate_random_shape(shape.type);

                if (check_for_collision(&shape, &game->board))
                {
                    stop_soundtrack();
                    play_gameover();
                    update_scoreboard(&game->scoreboard, game->score);
                    SDL_Delay(2000);
                    game->current_screen = SCREEN_GAME_OVER;
                }
            }
            last_fall = now;
        }

        SDL_SetRenderDrawColor(game->renderer, 20, 20, 30, 255);
        SDL_RenderClear(game->renderer);
        background_render(game->renderer);
        board_render(&game->board, game->renderer);
        render_ui(game->renderer, game->score, game->lines_cleared);
        render_shape(game->renderer, shape);
        render_next_shape(game->renderer, next_shape);
        SDL_RenderPresent(game->renderer);
    }

    stop_soundtrack();
}

void game_reset(Game* game)
{
    game->score = 0;
    game->lines_cleared = 0;
    board_init(&game->board);
}

void game_clear(SDL_Renderer* renderer, SDL_Window* window)
{
    TTF_CloseFont(Font_secondary);
    TTF_CloseFont(Font_primary);
    TTF_Quit();
    cleanup_audio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int delay_calcular(Game* game)
{
    int base_delay;

    switch (game->settings.difficulty)
    {
    case 0: base_delay = 500;
        break;
    case 1: base_delay = 400;
        break;
    case 2: base_delay = 300;
        break;
    default: base_delay = 400;
    }

    int delay = base_delay - (game->lines_cleared / 5) * FALL_SPEED_MULTIPLIER;
    return delay > MIN_DELAY ? delay : MIN_DELAY;
}

void load_scoreboard(Scoreboard* scoreboard)
{
    FILE* file = fopen("scoreboard.txt", "r");

    if (!file)
    {
        printf("Failed to open scoreboard file!\n");
        for (int i = 0; i < 3; i++)
        {
            scoreboard->scores[i] = 0;
        }
        save_scoreboard(scoreboard);
        return;
    }

    char buffer[255] = {};
    for (int record = 0; record < 3; record++)
    {
        if (fgets(buffer, sizeof(buffer), file))
        {
            scoreboard->scores[record] = atoi(buffer);
            scoreboard->count++;
        }
        else
        {
            scoreboard->scores[record] = 0;
            break;
        }
    }

    fclose(file);
}

void save_scoreboard(const Scoreboard* scoreboard)
{
    FILE* file = fopen("scoreboard.txt", "w");
    if (file)
    {
        for (int i = 0; i < 3; i++)
        {
            fprintf(file, "%d\n", scoreboard->scores[i]);
        }

        fclose(file);
    }
}

void update_scoreboard(Scoreboard* scoreboard, int score)
{
    int index = -1;
    for (int i = 0; i < 3; i++)
    {
        if (score > scoreboard->scores[i])
        {
            index = i;
            break;
        }
    }

    if (index >= 0)
    {
        for (int i = 3; i > index; i--)
        {
            scoreboard->scores[i] = scoreboard->scores[i - 1];
        }
        scoreboard->scores[index] = score;
        save_scoreboard(scoreboard);
    }
}

void gameover_loop(Game* game)
{
    SDL_Event event;
    int selected = 0;
    const char* options[] = {"Play Again", "Menu", "Quit"};
    int option_count = 3;

    while (game->running && game->current_screen == SCREEN_GAME_OVER)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                game->running = 0;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    selected = (selected - 1 + option_count) % option_count;
                    break;
                case SDLK_DOWN:
                    selected = (selected + 1) % option_count;
                    break;
                case SDLK_RETURN:
                    if (selected == 0)
                    {
                        game_reset(game);
                        game->current_screen = SCREEN_GAME;
                    }
                    else if (selected == 1)
                    {
                        game_reset(game);
                        game->current_screen = SCREEN_MENU;
                    }
                    else if (selected == 2)
                    {
                        game->running = 0;
                    }
                    break;
                }
            }
        }

        SDL_SetRenderDrawColor(game->renderer, 20, 20, 30, 255);
        SDL_RenderClear(game->renderer);
        background_render(game->renderer);

        SDL_Color white = {255, 255, 255, 255};
        SDL_Color gray = {100, 100, 100, 255};
        SDL_Color red = {255, 80, 80, 255};

        render_text(game->renderer, Font_primary, "Game Over", SCREEN_WIDTH / 2 - 90, 150, red);

        char score_text[32];
        sprintf(score_text, "Score: %d", game->score);
        render_text(game->renderer, Font_secondary, score_text, SCREEN_WIDTH / 2 - 50, 220, white);

        char lines_text[32];
        sprintf(lines_text, "Lines: %d", game->lines_cleared);
        render_text(game->renderer, Font_secondary, lines_text, SCREEN_WIDTH / 2 - 50, 260, white);

        for (int i = 0; i < option_count; i++)
        {
            SDL_Color color = (i == selected) ? white : gray;
            char text[32];
            sprintf(text, "%s %s", (i == selected) ? ">" : " ", options[i]);
            render_text(game->renderer, Font_secondary, text, SCREEN_WIDTH / 2 - 60, 340 + i * 50, color);
        }

        SDL_RenderPresent(game->renderer);
    }
}

