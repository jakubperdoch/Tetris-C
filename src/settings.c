#include "settings.h"
#include "render.h"
#include "board.h"
#include "constants.h"
#include "audio.h"

void load_settings(Settings* settings)
{
    FILE* file = fopen("settings.txt", "r");

    if (!file)
    {
        settings->difficulty = 1;
        settings->music = 1;
        save_settings(settings);
        return;
    }

    char buffer[255];

    if (fgets(buffer, sizeof(buffer), file))
        settings->difficulty = atoi(buffer);
    if (fgets(buffer, sizeof(buffer), file))
        settings->music = atoi(buffer);

    fclose(file);
}

void save_settings(Settings* settings)
{
    FILE* file = fopen("settings.txt", "w");
    if (file)
    {
        fprintf(file, "%d\n", settings->difficulty);
        fprintf(file, "%d\n", settings->music);
        fclose(file);
    }
}

void settings_loop(Game* game)
{
    SDL_Event event;
    int selected = 0;
    const char* difficulties[] = {"Easy", "Normal", "Hard"};
    const char* on_off[] = {"Off", "On"};
    int option_count = 3;

    while (game->running && game->current_screen == SCREEN_SETTINGS)
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
                case SDLK_LEFT:
                    if (selected == 0)
                        game->settings.difficulty = (game->settings.difficulty - 1 + 3) % 3;
                    else if (selected == 1)
                        game->settings.music = !game->settings.music;
                    break;
                case SDLK_RIGHT:
                    if (selected == 0)
                        game->settings.difficulty = (game->settings.difficulty + 1) % 3;
                    else if (selected == 1)
                    {
                        game->settings.music = !game->settings.music;
                    }
                    break;
                case SDLK_ESCAPE:
                    save_settings(&game->settings);
                    game->current_screen = SCREEN_MENU;
                    break;
                case SDLK_RETURN:
                    save_settings(&game->settings);
                    game->current_screen = SCREEN_MENU;
                    break;
                }
            }
        }

        SDL_SetRenderDrawColor(game->renderer, 20, 20, 30, 255);
        SDL_RenderClear(game->renderer);
        background_render(game->renderer);

        SDL_Color white = {255, 255, 255, 255};
        SDL_Color gray = {100, 100, 100, 255};

        render_text(game->renderer, Font_primary, "Settings", SCREEN_WIDTH / 2 - 80, 150, white);

        char difficulty_text[64];
        sprintf(difficulty_text, "< Difficulty: %s >", difficulties[game->settings.difficulty]);
        SDL_Color color0 = (selected == 0) ? white : gray;
        render_text(game->renderer, Font_secondary, difficulty_text, SCREEN_WIDTH / 2 - 100, 280, color0);

        char music_text[64];
        sprintf(music_text, "< Music: %s >", on_off[game->settings.music]);
        SDL_Color color1 = (selected == 1) ? white : gray;
        render_text(game->renderer, Font_secondary, music_text, SCREEN_WIDTH / 2 - 100, 330, color1);

        render_text(game->renderer, Font_secondary, "Press ESC to go back", SCREEN_WIDTH / 2 - 80, 480, gray);

        SDL_RenderPresent(game->renderer);
    }
}
