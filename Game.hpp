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
    double ITERATION_TIME = 500.0; // Set default iteration time

    Snake snake;
    Fruit fruit;
    bool gameOver;
    int score;

    std::vector<std::vector<char>> currentBuffer;
    std::vector<std::vector<char>> previousBuffer;

    char lastHorizontalCommand = 'd'; // Default to moving right
    char lastVerticalCommand = '\0'; // Default to no vertical movement

    int grid_width;
    int grid_height;

    /**
     * @brief Set the Iteration Time object
     *
     * @param[in] time  The time in milliseconds
     */
    void SetIterationTime(double time);

    /**
     * @brief   Run the game loop
     *
     * @param[in]   command   The command to be checked
     *
     * @return  char    The opposite command
     */
    char Opposite(char command);

    // Draw renders the game state.
    void Draw();
    // Input handles user input.
    bool Input();
    // Logic updates the game state.
    void Logic();
    // Update updates the game state.
    void Update();
};

#endif