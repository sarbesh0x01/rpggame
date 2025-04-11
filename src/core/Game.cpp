#include "SDL.h"
#include "SDL_events.h"
#include "SDL_render.h"
#include "SDL_video.h"
#include <SDL_rect.h>
#include <SDL_surface.h>
#include <SDL_ttf.h>
#include <include/core/Game.h>
#include <iostream>

TTF_Font *font;
SDL_Rect *renderQuad;
SDL_Texture *textTexture;

// Constructor
Game::Game() {}

// Destructor
Game::~Game() {}

void Game::init(const char *title, int xpos, int ypos, int width, int height,
                bool fullscreen) {

  int flags = 0;
  if (fullscreen) {
    flags = SDL_WINDOW_FULLSCREEN;
  }

  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    std::cout << "SDL Subsystem initilized\n" << std::endl;

    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

    renderer = SDL_CreateRenderer(window, -1, 0);

    // Vurenalble to LFI
    TTF_Init();
    font = TTF_OpenFont("../../text/Agave/AgaveNerdFont-Bold.ttf", 24);

    SDL_Color textColor = {0, 0, 0, 255};
    // First render the text to surfac
    SDL_Surface *textSurface =
        TTF_RenderText_Solid(font, "Hello, SDL!", textColor);

    // Create a texture from the surface
    SDL_Texture *textTexture =
        SDL_CreateTextureFromSurface(renderer, textSurface);

    // Get the dimensions of the texture
    int textWidth = textSurface->w;
    int textHeight = textSurface->h;

    // Free the surface as we no longer need it
    SDL_FreeSurface(textSurface);

    // Set the destination rectangle for the text
    renderQuad = {(640 - textWidth) / 2, (480 - textHeight) / 2, textWidth,
                  textHeight};

    isRunning = true;
  } else {
    isRunning = false;
  }
}
void Game::update() {}

void Game::handleEvent() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {

      isRunning = false;
    }
  }
}

void Game::render() {

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
  // This is where we draw our own stuff
  SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);
  SDL_RenderPresent(renderer);
}

void Game::close() {

  SDL_DestroyTexture(textTexture);
  TTF_CloseFont(font);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  SDL_Quit();

  std::cout << " game closed and quit";
}

bool Game::running() { return isRunning; }
