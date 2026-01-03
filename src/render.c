#include "render.h"
#include "constants.h"
#include "SDL.h"
#include "SDL_ttf.h"

TTF_Font* Font_primary = NULL;
TTF_Font* Font_secondary = NULL;


int init_font()
{
 if (TTF_Init() != 0)
 {
  SDL_LogError(0, "TTF init failed: %s\n", TTF_GetError());
  return -1;
 }

 Font_primary = TTF_OpenFont(FONT_PRIMARY_PATH, FONT_PRIMARY_SIZE);
 Font_secondary = TTF_OpenFont(FONT_PRIMARY_PATH, FONT_SECONDARY_SIZE);

 if (!Font_primary || !Font_secondary)
 {
  SDL_LogError(0, "Font load failed: %s\n", TTF_GetError());
  TTF_Quit();
  return -1;
 }

 return 0;
}


void render_text(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color)
{
 SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
 if (!surface) return;

 SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
 SDL_Rect rect = {x, y, surface->w, surface->h};
 SDL_FreeSurface(surface);

 if (!texture) return;

 SDL_RenderCopy(renderer, texture, NULL, &rect);
 SDL_DestroyTexture(texture);
}

void render_ui(SDL_Renderer* renderer, int score, int lines_cleared)
{
 SDL_Color white = {255, 255, 255, 255};
 char score_text[32];
 char lines_cleared_text[32];
 sprintf(score_text, "Score: %d", score);
 sprintf(lines_cleared_text, "Lines cleared: %d", lines_cleared);

 render_text(renderer, Font_primary, "TetriC", SCREEN_WIDTH / 2 - 60, 20, white);
 render_text(renderer, Font_secondary, lines_cleared_text, SCREEN_WIDTH / 2 - 100, 80, white);
 render_text(renderer, Font_secondary, score_text, SCREEN_WIDTH / 2 - 35, 110, white);
}




