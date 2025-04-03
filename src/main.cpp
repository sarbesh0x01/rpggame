#include "../include/world.h"
#include "SDL_render.h"
#include "SDL_timer.h"
#include "SDL_video.h"
#include "imgui_impl_sdl2.h"
#include "include/player.h"
#include "include/world.h"
#include <SDL.h>
#include <imgui.h>
#include <imgui_impl_sdlrenderer2.h>
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
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  ImGui::StyleColorsDark();
  ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
  ImGui_ImplSDLRenderer2_Init(renderer);
  int windowWidht, windowHeight;
  SDL_GetWindowSize(window, &windowWidht, &windowHeight);
  // Main loop flag
  bool isRunning = true;
  SDL_Event event;
  Player player(windowWidht / 2, windowHeight / 2);
  World world(10, 10, 64, 32);
  world.render(renderer);

  // Main loop
  while (isRunning) {
    // Handle events
    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL2_ProcessEvent(&event);
      if (event.type == SDL_QUIT) {
        isRunning = false;
      } else {
        player.handelEvent(event);
      }
    }
    std::cout << "Player Position: " << player.getPosY() << std::endl;
    // Set render draw color to white
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    // Clear the screen
    SDL_RenderClear(renderer);
    player.render(renderer);
    world.render(renderer);
    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
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
