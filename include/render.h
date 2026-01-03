#ifndef RENDER_H
#define RENDER_H

#include "SDL.h"
#include "SDL_ttf.h"

extern TTF_Font* Font_secondary;
extern TTF_Font* Font_primary;

typedef enum
{
    SCREEN_MENU,
    SCREEN_GAME,
    SCREEN_SETTINGS,
    SCREEN_GAME_OVER
} GameScreen;

int init_font();
void render_ui(SDL_Renderer* renderer, int score, int lines_cleared);
void render_text(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color);
void render_score(SDL_Renderer* renderer, int score);

#endif
