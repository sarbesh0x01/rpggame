// include/ui/gui_manager.h
#pragma once
#include <SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

class GuiManager {
public:
  GuiManager();
  ~GuiManager();

  bool initialize(SDL_Window *window, SDL_Renderer *renderer);
  void newFrame();
  void render(SDL_Renderer *renderer);
  void shutdown();
  void processEvent(const SDL_Event &event);

private:
  ImGuiIO *io;
};
