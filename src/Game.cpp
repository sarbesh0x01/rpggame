// Game.cpp
#include "../include/Game.h"
#include <SDL.h>
#include <SDL_timer.h>
// Include additional headers for your World and Player classes
//
Game::Game()
    : window(nullptr), renderer(nullptr), isRunning(true),
      world(10, 10, 64, 32), player(0, 0, world), inputHandler(player, world) {}

Game::~Game() { cleanup(); }

bool Game::init() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    return false;
  }
  window =
      SDL_CreateWindow("RPG Game", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 1080, 800, SDL_WINDOW_RESIZABLE);
  if (!window) {
    SDL_Log("Failed to create window: %s", SDL_GetError());
    SDL_Quit();
    return false;
  }
  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer) {
    SDL_Log("Failed to create renderer: %s", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return false;
  }
  // Initialize other systems like ImGui, World, Player, etc.
  return true;
}

void Game::run() {
  SDL_Event event;
  while (isRunning) {
    while (SDL_PollEvent(&event)) {
      // Process events with SDL and ImGui
      if (event.type == SDL_QUIT) {
        isRunning = false;
      } else if (event.type == SDL_MOUSEBUTTONDOWN ||
                 event.type == SDL_MOUSEBUTTONUP) {
        inputHandler.handleButton(event.button);
      } else if (event.type == SDL_MOUSEMOTION) {
        InputHandler::handleMotion(event.motion);
      }
      player.handelEvent(event);
      // Add event handling for world/player etc.
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    // Render game objects
    world.loadTileTexture(renderer, "../assets/tile_000.png");
    world.render(renderer);
    player.render(renderer);

    SDL_RenderPresent(renderer);
    SDL_Delay(15); // Control frame rate
  }
}

void Game::cleanup() {
  if (renderer) {
    SDL_DestroyRenderer(renderer);
  }
  if (window) {
    SDL_DestroyWindow(window);
  }
  SDL_Quit();
}
