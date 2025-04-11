#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

void MainScreen() {
  ImGui::Begin("Elowen Home Screen");
  ImGui::Button("Start Game");
  ImGui::End();
}
