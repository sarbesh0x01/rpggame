#include "main.h"
#include "Level1.h"
#include "player.h"
#include "raylib.h"
#include <stdbool.h>

#define DefaultWindowHeight 900
#define DefaultWindowWidth 900

// Global Defination of player
Player testPlayer;
Game::Game() { mRunning = true; }

bool Game::Initialize() {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(DefaultWindowWidth, DefaultWindowHeight, "Not Decided Yet");
  camera.position = (Vector3){0.0f, 10.0f, 10.0f};
  camera.target = (Vector3){0.0f, 0.0f, 0.0f};
  camera.up = (Vector3){0.0f, 1.0f, 0.0f};
  camera.fovy = 45.0f;
  camera.projection = CAMERA_PERSPECTIVE;
  SetTargetFPS(60);
  return IsWindowReady();
}
void Game::DrawGame() {
  BeginDrawing();
  ClearBackground(RAYWHITE);
  BeginMode3D(camera);
  testPlayer.Draw();
  EndMode3D();
  DrawFPS(10, 10);
  EndDrawing();
}

void Game::CloseGame() { CloseWindow(); }

void Game::UpdateGame() {}
void Game::ProcessInput() {}

void Game::RunLoop() {
  while (!WindowShouldClose() && mRunning) {
    ProcessInput();
    UpdateGame();
    DrawGame();
  }
}
