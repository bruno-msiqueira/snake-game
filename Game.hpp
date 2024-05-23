#ifndef GAME_HPP
#define GAME_HPP

#include "Snake.hpp"
#include "Fruit.hpp"

// The Game class manages the game.
class Game {
public:
    // Constructor initializes the game.
    Game(int grid_width, int grid_height);
    // Run starts the game loop.
    void Run();
private:
    Snake snake;
    Fruit fruit;
    int grid_width;
    int grid_height;
    // Draw renders the game state.
    void Draw();
    // Input handles user input.
    bool Input();
    // Logic updates the game state.
    void Logic();
};

#endif