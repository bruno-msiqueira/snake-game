#ifndef GAME_HPP
#define GAME_HPP

#include "GameBoard.hpp"
#include "Snake.hpp"

// The Game class manages the game.
class Game {
public:
    // Constructor initializes the game.
    Game(int gridWidth, int gridHeight);
    // Run starts the game loop.
    void Run();
private:
    double ITERATION_TIME = 500.0; // Set default iteration time

    Snake m_snake;
    GameBoard m_boardGame;
    bool m_gameOver;
    unsigned int m_score;

    std::vector<std::vector<char>> m_currentBuffer;
    std::vector<std::vector<char>> m_previousBuffer;

    char m_lastHorizontalCommand = 'd'; // Default to moving right
    char m_lastVerticalCommand = '\0'; // Default to no vertical movement

    int m_gridWidth;
    int m_gridHeight;

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
    // Update updates the game state.
    void Update();
    // PrintScore prints the current score
    void PrintScore();
};

#endif