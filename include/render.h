#include "types.h"
#include "SDL.h"
#include "SDL_ttf.h"

extern TTF_Font* Font_secondary;
extern TTF_Font* Font_primary;

void render_shape(SDL_Renderer* renderer, Shape shape);
Shape generate_random_shape();
int init_font();
void render_ui(SDL_Renderer* renderer, int score);
void render_text(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color);
void render_score(SDL_Renderer* renderer, int score);
