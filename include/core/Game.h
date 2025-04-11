#include "SDL_video.h"
#include <SDL2/SDL.h>
#include <SDL_rect.h>
#include <SDL_ttf.h>
#include <string>

class Game {

public:
  Game() = default;

  ~Game() = default;

  void init(const char *title, int xpos, int ypos, int width, int height,
            bool fullscreen);

  void handleEvent();
  void update();
  void render();
  void close();
  // To check the program is running
  bool running();

private:
  bool isRunning;

  SDL_Window *window;
  SDL_Renderer *renderer;
  TTF_Font *font;
  SDL_Rect renderQuad;
  SDL_Texture *textTexture;
};
