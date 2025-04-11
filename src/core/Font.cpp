#include "include/core/Font.h"
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

void DrawText(TTF_Font *font, SDL_Renderer *renderer, int x, int y,
              std::string text) {
  SDL_Color color = {0, 0, 0, 0};
  // First render the text to surface
  SDL_Surface *textSurface = TTF_RenderText_Blended(font, text.c_str(), color);

  // Change the Surface to Texture
  SDL_Texture *textTexture =
      SDL_CreateTextureFromSurface(renderer, textSurface);

  SDL_Rect rect = {x, y, 100, 100};

  SDL_RenderCopy(renderer, textTexture, NULL, &rect);
  SDL_DestroyTexture(textTexture);
  SDL_FreeSurface(textSurface);
}
