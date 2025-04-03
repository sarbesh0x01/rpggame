#include "../include/world.h"
#include "SDL_render.h"
#include "SDL_timer.h"
#include "SDL_video.h"
#include "imgui_impl_sdl2.h"
#include "include/player.h"
#include "include/world.h"
#include <SDL.h>
#include <SDL_events.h>
#include <imgui.h>
#include <imgui_impl_sdlrenderer2.h>
#include <iostream>
// Main function
//
//
void HandleButton(SDL_MouseButtonEvent &E) {
  if (E.button == SDL_BUTTON_LEFT) {
    if (E.state == SDL_PRESSED) {
      std::cout << "Left button pressed at (" << E.x << ", " << E.y << ")\n";
    } else if (E.state == SDL_RELEASED) {
      std::cout << "Left button released at (" << E.x << ", " << E.y << ")\n";
    }
  }
}

void HandleMotion(SDL_MouseMotionEvent &E) {
  std::cout << "Mouse moved to (" << E.x << ", " << E.y << ")\n";
}
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

  int mousepos_x;
  int mousepos_y;
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
  World world(10, 10, 128, 64);
  Player player(0, 0, world); // Grid coordinates
  world.render(renderer);
  Uint32 button = SDL_GetMouseState(&mousepos_x, &mousepos_y);

  // Main loop
  while (isRunning) {
    // Handle events
    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL2_ProcessEvent(&event);
      if (event.type == SDL_QUIT) {
        isRunning = false;
      } else if (event.type == SDL_MOUSEBUTTONDOWN ||
                 event.type == SDL_MOUSEBUTTONUP) {
        HandleButton(event.button);
      } else if (event.type == SDL_MOUSEMOTION) {
        HandleMotion(event.motion);
      } else {
        player.handelEvent(event);
      }
    }

    // Set render draw color to white
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    // Clear the screen
    SDL_RenderClear(renderer);
    world.render(renderer);
    player.render(renderer);
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
