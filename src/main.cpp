/**
 * @file main.cpp
 * @brief Entry point for the engine-based application.
 *
 * This program creates an instance of the Engine class, initializes it, and
 * then runs the engine. If the initialization fails, the program outputs an
 * error message and exits with a non-zero status code.
 */

#include "../include/core/engine.h" // Include the engine header file from the core module
#include <iostream> // Include the iostream library for input/output operations

/**
 * @brief The main function of the application.
 *
 * This function performs the following steps:
 * 1. Creates an instance of the Engine class.
 * 2. Calls the initialize() method on the Engine object.
 *    - If initialization fails, it prints an error message to std::cerr and
 * exits with status code 1.
 * 3. If initialization is successful, it calls the run() method to start the
 * engine.
 * 4. Returns 0 to indicate successful execution.
 *
 * @param argc The count of command-line arguments.
 * @param argv An array of command-line argument strings.
 * @return int Exit status of the program (0 if successful, non-zero if an error
 * occurred).
 */
int main(int argc, char *argv[]) {
  Engine engine; // Create an instance of the Engine

  // Initialize the engine. If initialization fails, print an error message and
  // exit.
  if (!engine.initialize()) {
    std::cerr << "Failed to initialize engine" << std::endl;
    return 1;
  }

  // Run the engine if initialization was successful.
  engine.run();

  return 0; // Exit the program successfully.
}

