#ifndef GAME_HPP
#define GAME_HPP

#include "GameBoard.hpp"
#include "Snake.hpp"

// The Direction enum represents the direction of the snake.
enum class Direction { STOPPED, UP, DOWN, LEFT, RIGHT };

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
    Direction m_snakeDirection = Direction::STOPPED;
    GameBoard m_gameBoard;
    bool m_gameOver;
    unsigned int m_score;

    std::vector<std::vector<char>> m_currentBuffer;
    std::vector<std::vector<char>> m_previousBuffer;

    char m_lastCommand = 's'; // Default command is stopped

    int m_gridWidth;
    int m_gridHeight;

    /**
     * @brief Set the Iteration Time object
     *
     * @param[in] time  The time in milliseconds
     */
    void SetIterationTime(double time);

    // Draw renders the game state.
    void Draw(bool isGameOver);

    // Input handles user input.
    bool Input();

    // Update updates the game state.
    void Update();

    // PrintScore prints the current score
    void PrintScore();

    // IsGameOver checks if the game is over.
    bool IsGameOver();

    // IsGameWon checks if the game is won.
    bool IsGameWon();

    // SnakeSelfHit checks if the snake has hit itself.
    bool SnakeSelfHit() const;

    // SnakeWallHit checks if the snake has hit a wall.
    bool SnakeWallHit() const;

    // SnakeObstacleHit checks if the snake has hit an obstacle.
    bool SnakeObstacleHit() const;

    // IsInSnakeBody checks if a point is in the snake's body.
    bool MoveSnake();

    // CheckSnakeEatFruit checks if the snake has eaten a fruit.
    bool CheckSnakeEatFruit() const;

    // CheckSnakeEatFruit checks if the snake has eaten a fruit.
    bool CheckSnakeEatFruit(std::pair<unsigned int, unsigned int> snakePosition) const;

    // SetDirection sets the direction of the snake.
    void SetSnakeDirection(Direction dir);

    // GetDirection gets the direction of the snake.
    Direction GetSnakeDirection() const;

    // GetSnakeNextPosition returns the next position of the snake.
    std::pair<unsigned int, unsigned int> GetSnakeNextPosition() const;
};

#endif