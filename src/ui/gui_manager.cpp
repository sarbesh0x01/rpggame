// src/ui/gui_manager.cpp
#include "../../include/ui/gui_manager.h"

GuiManager::GuiManager() : io(nullptr) {}

GuiManager::~GuiManager() { shutdown(); }

bool GuiManager::initialize(SDL_Window *window, SDL_Renderer *renderer) {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  io = &ImGui::GetIO();

  ImGui::StyleColorsDark();
  ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
  ImGui_ImplSDLRenderer2_Init(renderer);

  return true;
}

void GuiManager::newFrame() {
  ImGui_ImplSDLRenderer2_NewFrame();
  ImGui_ImplSDL2_NewFrame();
  ImGui::NewFrame();
}

void GuiManager::render(SDL_Renderer *renderer) {
  ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
}

void GuiManager::shutdown() {
  ImGui_ImplSDLRenderer2_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
}

void GuiManager::processEvent(const SDL_Event &event) {
  ImGui_ImplSDL2_ProcessEvent(&event);
}
