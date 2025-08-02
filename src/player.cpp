#include "player.h"
#include "raylib.h"

void Player::Draw() {
  DrawSphere((Vector3){1.0f, 0.0f, 9.0f}, 1.0f, GREEN);
  DrawGrid(10, 1.0f); // Draw a grid
  DrawSphereWires((Vector3){1.0f, 0.0f, 2.0f}, 2.0f, 16, 16, LIME);
  DrawCylinderWires((Vector3){4.0f, 0.0f, -2.0f}, 1.0f, 2.0f, 3.0f, 4,
                    DARKBLUE);
  DrawCylinderWires((Vector3){4.5f, -1.0f, 2.0f}, 1.0f, 1.0f, 2.0f, 6, BROWN);
}
