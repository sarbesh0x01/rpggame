// src/main.cpp
#include "../include/core/engine.h"
#include <iostream>

int main(int argc, char *argv[]) {
  Engine engine;

  if (!engine.initialize()) {
    std::cerr << "Failed to initialize engine" << std::endl;
    return 1;
  }

  engine.run();

  return 0;
}

