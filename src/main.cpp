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
#include <string>

// Function declaration for renderHUD
void renderHUD(SDL_Renderer *renderer, int windowWidth, int windowHeight,
               const std::string &message, int timer, int timeout);

int main(int argc, char *argv[]) {
  // Initialize SDL with all necessary subsystems
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) != 0) {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    return 1;
  }

  // Create a fullscreen window
  SDL_DisplayMode displayMode;
  SDL_GetCurrentDisplayMode(0, &displayMode);

  // Use 90% of the screen size to leave room for system UI elements
  int windowWidth = displayMode.w * 0.95;
  int windowHeight = displayMode.h * 0.95;

  SDL_Window *window =
      SDL_CreateWindow("Isometric RPG Adventure", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight,
                       SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

  // Check if window is created
  if (window == nullptr) {
    SDL_Log("Failed to create window: %s", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  // Create a renderer with hardware acceleration and vsync
  SDL_Renderer *renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  // Check if renderer is created
  if (renderer == nullptr) {
    SDL_Log("Failed to create renderer: %s", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  // Setup Dear ImGui
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  ImGui::StyleColorsDark();
  ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
  ImGui_ImplSDLRenderer2_Init(renderer);

  // Create the game world (50x50 grid for a large playable area)
  World world(50, 50, 64, 32);

  // Initialize player at a specific starting position
  Player player(25, 25);

  // Set player size proportional to tile size
  player.setPlayerSize(world.getTileWidth() * 0.75,
                       world.getTileHeight() * 0.75);

  // Game state flags
  bool isRunning = true;
  bool showDebugInfo = true;
  bool cameraFollowsPlayer = true;

  // Key state tracking
  bool keyUp = false;
  bool keyDown = false;
  bool keyLeft = false;
  bool keyRight = false;
  bool keyZoomIn = false;
  bool keyZoomOut = false;

  // Game HUD messages
  std::string statusMessage = "Welcome to Isometric RPG Adventure!";
  int messageTimeout = 180; // frames
  int messageTimer = messageTimeout;

  // For FPS calculation
  Uint32 frameStart;
  int frameTime;
  const int FPS = 60;
  const int frameDelay = 1000 / FPS;

  // Focus camera on player initially
  world.focusOnPosition(player.getGridX(), player.getGridY());

  // Main loop
  while (isRunning) {
    frameStart = SDL_GetTicks();

    // Handle events
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL2_ProcessEvent(&event);

      if (event.type == SDL_QUIT) {
        isRunning = false;
      } else if (event.type == SDL_KEYDOWN) {
        // Handle key presses
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
          isRunning = false;
          break;
        case SDLK_F1:
          showDebugInfo = !showDebugInfo;
          break;
        case SDLK_F2:
          cameraFollowsPlayer = !cameraFollowsPlayer;
          statusMessage = cameraFollowsPlayer ? "Camera now follows player"
                                              : "Free camera mode";
          messageTimer = messageTimeout;
          break;
        case SDLK_w:
        case SDLK_UP:
          keyUp = true;
          break;
        case SDLK_s:
        case SDLK_DOWN:
          keyDown = true;
          break;
        case SDLK_a:
        case SDLK_LEFT:
          keyLeft = true;
          break;
        case SDLK_d:
        case SDLK_RIGHT:
          keyRight = true;
          break;
        case SDLK_PLUS:
        case SDLK_EQUALS:
          keyZoomIn = true;
          break;
        case SDLK_MINUS:
          keyZoomOut = true;
          break;
        }
      } else if (event.type == SDL_KEYUP) {
        // Handle key releases
        switch (event.key.keysym.sym) {
        case SDLK_w:
        case SDLK_UP:
          keyUp = false;
          break;
        case SDLK_s:
        case SDLK_DOWN:
          keyDown = false;
          break;
        case SDLK_a:
        case SDLK_LEFT:
          keyLeft = false;
          break;
        case SDLK_d:
        case SDLK_RIGHT:
          keyRight = false;
          break;
        case SDLK_PLUS:
        case SDLK_EQUALS:
          keyZoomIn = false;
          break;
        case SDLK_MINUS:
          keyZoomOut = false;
          break;
        }
      } else if (event.type == SDL_WINDOWEVENT &&
                 event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
        // Update window size when resized
        int newWidth, newHeight;
        SDL_GetWindowSize(window, &newWidth, &newHeight);
        world.updateWindowSize(newWidth, newHeight);
      }
    }

    // Process continuous key inputs for smooth movement
    int deltaX = 0, deltaY = 0;

    if (keyUp)
      deltaY--;
    if (keyDown)
      deltaY++;
    if (keyLeft)
      deltaX--;
    if (keyRight)
      deltaX++;

    // Move player if valid
    if (deltaX != 0 || deltaY != 0) {
      int newX = player.getGridX() + deltaX;
      int newY = player.getGridY() + deltaY;

      // Check if the destination is walkable
      if (world.isWalkable(newX, newY)) {
        player.moveOnGrid(deltaX, deltaY);

        // Update status message based on terrain
        TerrainType terrain = world.getTerrainAt(newX, newY);
        switch (terrain) {
        case TerrainType::GRASS:
          statusMessage = "Walking through grassy plains...";
          break;
        case TerrainType::SAND:
          statusMessage = "Trudging through sandy ground...";
          break;
        case TerrainType::FOREST:
          statusMessage = "Moving through dense forest...";
          break;
        case TerrainType::ROCK:
          statusMessage = "Climbing over rocky terrain...";
          break;
        default:
          break;
        }
        messageTimer = messageTimeout;
      } else {
        statusMessage = "Can't go that way!";
        messageTimer = messageTimeout;
      }
    }

    // Handle zoom controls
    if (keyZoomIn) {
      world.zoomIn();
      player.setPlayerSize(world.getTileWidth() * 0.75,
                           world.getTileHeight() * 0.75);
    }
    if (keyZoomOut) {
      world.zoomOut();
      player.setPlayerSize(world.getTileWidth() * 0.75,
                           world.getTileHeight() * 0.75);
    }

    // Update player screen position based on grid position
    Point screenPos =
        world.getTileScreenPosition(player.getGridX(), player.getGridY());
    player.setScreenPosition(screenPos.x, screenPos.y);

    // Update camera to follow player if enabled
    if (cameraFollowsPlayer) {
      world.focusOnPosition(player.getGridX(), player.getGridY());
    }

    // Update message timer
    if (messageTimer > 0) {
      messageTimer--;
    }

    // Set render draw color for background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Start ImGui frame
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    // Clear the screen
    SDL_RenderClear(renderer);

    // Render world first, then player
    world.render(renderer);
    player.render(renderer);

    // Render game HUD
    renderHUD(renderer, windowWidth, windowHeight, statusMessage, messageTimer,
              messageTimeout);

    // Debug display if enabled
    if (showDebugInfo) {
      ImGui::Begin("Debug Info");

      ImGui::Text("Grid Position: (%d, %d)", player.getGridX(),
                  player.getGridY());
      ImGui::Text("Screen Position: (%d, %d)", screenPos.x, screenPos.y);
      ImGui::Text("Camera Position: (%d, %d)", world.getCameraX(),
                  world.getCameraY());
      ImGui::Text("Zoom Level: %.2f", world.getZoomLevel());

      ImGui::Separator();
      ImGui::Text("Controls:");
      ImGui::BulletText("WASD / Arrows: Move");
      ImGui::BulletText("+/-: Zoom in/out");
      ImGui::BulletText("F1: Toggle debug");
      ImGui::BulletText("F2: Toggle camera mode");
      ImGui::BulletText("ESC: Quit");

      // Calculate and display FPS
      frameTime = SDL_GetTicks() - frameStart;
      float currentFPS = (frameTime > 0) ? 1000.0f / frameTime : 0;
      ImGui::Text("FPS: %.1f", currentFPS);

      ImGui::End();
    }

    // Render ImGui
    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);

    // Present the renderer
    SDL_RenderPresent(renderer);

    // Cap frame rate
    frameTime = SDL_GetTicks() - frameStart;
    if (frameDelay > frameTime) {
      SDL_Delay(frameDelay - frameTime);
    }
  }

  // Cleanup
  ImGui_ImplSDLRenderer2_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  // Destroy the renderer
  SDL_DestroyRenderer(renderer);

  // Destroy the window
  SDL_DestroyWindow(window);

  // Quit SDL subsystems
  SDL_Quit();

  return 0;
}

// Game HUD rendering implementation
void renderHUD(SDL_Renderer *renderer, int windowWidth, int windowHeight,
               const std::string &message, int timer, int timeout) {
  // Only show message if timer is active
  if (timer <= 0)
    return;

  // Create message box at the bottom of the screen
  int boxHeight = 40;
  int boxWidth = windowWidth * 0.6;
  int boxX = (windowWidth - boxWidth) / 2;
  int boxY = windowHeight - boxHeight - 20;

  // Calculate alpha value for fade-out effect
  Uint8 alpha = static_cast<Uint8>(255.0f * (float)timer / timeout);

  // Draw semi-transparent background
  SDL_Rect msgBox = {boxX, boxY, boxWidth, boxHeight};
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, alpha * 0.7);
  SDL_RenderFillRect(renderer, &msgBox);

  // Draw border
  SDL_SetRenderDrawColor(renderer, 255, 215, 0, alpha); // Gold color
  SDL_RenderDrawRect(renderer, &msgBox);

  // SDL doesn't have built-in text rendering, so we'd normally use SDL_ttf
  // Since we can't add that here, we'll just note that this is where you'd
  // render the text SDL_RenderText(renderer, message, boxX + 10, boxY + 10);
}
