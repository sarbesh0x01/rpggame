
#include "SDL_render.h"
#include "SDL_timer.h"
#include "SDL_video.h"
#include "include/player.h"
#include <SDL.h>
#include <iostream>

// Main function
int main(int argc, char *argv[]) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    return 1;
  }

  // Create a window
  SDL_Window *window =
      SDL_CreateWindow("RPG Game", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 1080, 800, SDL_WINDOW_RESIZABLE);

  // Check if window is created
  if (window == nullptr) {
    SDL_Log("Failed to create window: %s", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  // Create a renderer
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

  // Check if renderer is created
  if (renderer == nullptr) {
    SDL_Log("Failed to create renderer: %s", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  // Main loop flag
  bool isRunning = true;
  SDL_Event event;
  Player player(0, 0);

  // Main loop
  while (isRunning) {
    // Handle events
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        isRunning = false;
      }
    }
    std::cout << "Player Position: " << player.getPosY() << std::endl;

    // Set render draw color to white
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    // Clear the screen
    SDL_RenderClear(renderer);

    player.render(renderer);

    // Present the renderer
    SDL_RenderPresent(renderer);
    SDL_Delay(15); // Delay to slow down the rendering
  }

  // Destroy the renderer
  SDL_DestroyRenderer(renderer);

  // Destroy the window
  SDL_DestroyWindow(window);

  // Quit SDL subsystems
  SDL_Quit();

  return 0;
}
