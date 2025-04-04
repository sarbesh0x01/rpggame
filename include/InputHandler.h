#pragma onc#pragma once
#include <SDL.h>

class Player; // Forward declaration
class World;  // Forward declaration

class InputHandler {
public:
    InputHandler(Player& playerRef, World& worldRef); // Constructor with both Player and World references
    void handleButton(const SDL_MouseButtonEvent& event);
    static void handleMotion(const SDL_MouseMotionEvent& event);
    void ChangeMouseScreenToIsometric();

private:
    Player& player; // Reference to the player
    World& world;   // Reference to the world
};
