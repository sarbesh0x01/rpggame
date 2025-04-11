#include <SDL_render.h>
#include <SDL_ttf.h>
#include <string>
void initFont();

void DrawText(TTF_Font *font, SDL_Renderer *renderer, int x, int y,
              std::string text);
