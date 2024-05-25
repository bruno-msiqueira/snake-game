#ifndef GAME_HPP
#define GAME_HPP

#include "GameBoard.hpp"
#include "Snake.hpp"

// The Game class manages the game.
class Game {
public:
    // Constructor initializes the game.
    Game(unsigned int gridWidth, unsigned int gridHeight, unsigned int obstacleCount);
    // Run starts the game loop.
    void Run();
private:
    double ITERATION_TIME = 500.0; // Set default iteration time

    Snake m_snake;
    GameBoard m_gameBoard;
    bool m_gameOver;
    unsigned int m_score;

    std::vector<std::vector<char>> m_currentBuffer;
    std::vector<std::vector<char>> m_previousBuffer;

    char m_lastCommand = 'd'; // Default to moving right

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
    void Draw(bool isGameOver);
    // Input handles user input.
    bool Input();
    // Update updates the game state.
    void Update();
    // PrintScore prints the current score
    void PrintScore();

    // SnakeSelfHit checks if the snake has hit itself.
    bool SnakeSelfHit() const;

    // SnakeWallHit checks if the snake has hit a wall.
    bool SnakeWallHit() const;

    // SnakeObstacleHit checks if the snake has hit an obstacle.
    bool SnakeObstacleHit() const;

    // IsGameOver checks if the game is over.
    bool IsGameOver() const;
    // IsGameWon checks if the game is won.
    bool IsGameWon();
};

#endif