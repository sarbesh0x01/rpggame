
// src/core/engine.cpp
#include "../../include/core/engine.h"
#include "../../include/core/input_manager.h"
#include "../../include/game/player.h"
#include "../../include/game/world.h"
#include "../../include/ui/gui_manager.h"
#include <iostream>

Engine::Engine()
    : window(nullptr), renderer(nullptr), windowWidth(1080), windowHeight(800),
      isRunning(false) {}

Engine::~Engine() { shutdown(); }

bool Engine::initialize() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    return false;
  }

  // Create window
  window = SDL_CreateWindow("RPG Game", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight,
                            SDL_WINDOW_RESIZABLE);
  if (!window) {
    SDL_Log("Failed to create window: %s", SDL_GetError());
    return false;
  }

  // Create renderer
  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer) {
    SDL_Log("Failed to create renderer: %s", SDL_GetError());
    return false;
  }

  // Initialize subsystems
  inputManager = std::make_unique<InputManager>();
  guiManager = std::make_unique<GuiManager>();
  if (!guiManager->initialize(window, renderer)) {
    return false;
  }

  // Create game objects
  world = std::make_unique<World>(10, 10, 128, 64);
  player = std::make_unique<Player>(0, 0, *world);

  // Set up input callbacks
  inputManager->registerMouseButtonCallback([](SDL_MouseButtonEvent &e) {
    if (e.button == SDL_BUTTON_LEFT) {
      if (e.state == SDL_PRESSED) {
        std::cout << "Left button pressed at (" << e.x << ", " << e.y << ")\n";
      } else if (e.state == SDL_RELEASED) {
        std::cout << "Left button released at (" << e.x << ", " << e.y << ")\n";
      }
    }
  });

  inputManager->registerMouseMotionCallback([](SDL_MouseMotionEvent &e) {
    std::cout << "Mouse moved to (" << e.x << ", " << e.y << ")\n";
  });

  inputManager->registerKeyCallback(
      [this](const SDL_Event &e) { player->handleEvent(e); });

  isRunning = true;
  return true;
}

void Engine::run() {
  while (isRunning) {
    // Process input and check if we should quit
    if (!inputManager->processInput()) {
      isRunning = false;
      break;
    }

    update();
    render();

    SDL_Delay(15); // Consistent frame timing
  }
}

void Engine::update() {
  // Update game state here
}

void Engine::render() {
  // Clear the screen
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);

  // Start a new ImGui frame
  guiManager->newFrame();

  // Render game elements
  world->render(renderer);
  player->render(renderer);

  // Render ImGui
  ImGui::Render();
  guiManager->render(renderer);

  // Present the rendered frame
  SDL_RenderPresent(renderer);
}

void Engine::shutdown() {
  // Destroy game objects first
  player.reset();
  world.reset();

  // Clean up subsystems
  guiManager->shutdown();
  guiManager.reset();
  inputManager.reset();

  // Clean up SDL resources
  if (renderer) {
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
  }

  if (window) {
    SDL_DestroyWindow(window);
    window = nullptr;
  }

  SDL_Quit();
}
