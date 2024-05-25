#include "Game.hpp"
#include "Utility.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <algorithm>
#include <chrono>

// Constructor initializes the game.
Game::Game(unsigned int gridWidth, unsigned int gridHeight, unsigned int obstacleCount, float iterationTime)
        :   m_iterationTime(iterationTime),
            m_snake(gridWidth, gridHeight),
            m_gameBoard(gridWidth, gridHeight, obstacleCount, &m_snake),
            m_gameOver(false),
            m_score(0),
            m_gridWidth(gridWidth),
            m_gridHeight(gridHeight),
            m_currentBuffer(gridHeight, std::vector<char>(gridWidth, ' ')),
            m_previousBuffer(gridHeight, std::vector<char>(gridWidth, ' ')) {
    // Initialize game
    if (m_iterationTime < 100) {
        m_iterationTime = 500;
    }

    // Clear the console
    system(GetClearCommand().c_str());
}

void Game::SetIterationTime(double time) {
    m_iterationTime = time;
}

// Run starts the game loop.
void Game::Run() {
    printf("\033[?25l"); // Hide cursor
    PrintScore();

    while (!IsGameWon() && !IsGameOver())
    {
        Draw(false);
        Input();
        Update();
    };

    std::cout << "\033[" << m_gridHeight + 2 << ";1H\033[?25h"; // Move cursor and show it
}

// Draw renders the game state.
void Game::Draw(bool isGameOver) {
    // Fill the current buffer with the game state
    for (int i = 0; i < m_gridHeight; ++i) {
        for (int j = 0; j < m_gridWidth; ++j) {
            std::pair<unsigned int, unsigned int> point(j, i);

            if (m_snake.GetSegments()[0] == point) {
                if (isGameOver) {
                    m_currentBuffer[i][j] = 'X'; // Draw 'X' if game is over
                } else {
                    m_currentBuffer[i][j] = 'H'; // Draw snake head
                }
            } else if (i == 0 || i == m_gridHeight - 1) {
                m_currentBuffer[i][j] = '#'; // Draw top and bottom borders
            } else if (j == 0 || j == m_gridWidth - 1) {
                m_currentBuffer[i][j] = '#'; // Draw left and right borders
            } else if (m_gameBoard.IsObstacle(point)) {
                m_currentBuffer[i][j] = '#'; // Draw Obstacle
            } else if (IsInSnakeBody(m_snake.GetSegments(), point)) {
                m_currentBuffer[i][j] = 'O'; // Draw snake body
            } else if (m_gameBoard.GetFruitPosition() == point) {
                m_currentBuffer[i][j] = '*'; // Draw fruit
            } else {
                m_currentBuffer[i][j] = ' '; // Draw empty space
            }
        }
    }

    // Compare the current buffer with the previous one and update the screen
    for (int i = 0; i < m_gridHeight; ++i) {
        for (int j = 0; j < m_gridWidth; ++j) {
            if (m_currentBuffer[i][j] != m_previousBuffer[i][j]) {
                // Move the cursor to the position (j, i) and print the new character
                printf("\033[%d;%dH%c", i + 2, j + 1, m_currentBuffer[i][j]);
            }
        }
    }

    // Swap the buffers
    m_previousBuffer.swap(m_currentBuffer);
}

// Input handles user input.
bool Game::Input() {
    bool inputed = false;
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    while (elapsed.count() < m_iterationTime) {
        if (_kbhit()) {
            switch (_getch()) {
            case 72: // Up arrow key
                if (m_lastCommand != 'd') {
                    m_lastCommand = 'u';
                }
                break;
            case 80: // Down arrow key
                if (m_lastCommand != 'u') {
                    m_lastCommand = 'd';
                }
                break;
            case 75: // Left arrow key
                if (m_lastCommand != 'r') {
                    m_lastCommand = 'l';
                }
                break;
            case 77: // Right arrow key
                if (m_lastCommand != 'l') {
                    m_lastCommand = 'r';
                }
                break;
            case 's': // Stop the snake
            case 'S': // Stop the snake
                m_lastCommand = 's';
                break;
            }
            inputed = true;
        }

        end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;
    }

    return inputed;
}

void Game::Update() {
    // Update snake's direction based on lastHorizontalCommand and lastVerticalCommand
    switch (m_lastCommand) {
        case 'u':
            if (m_snakeDirection != Direction::DOWN) {
                SetSnakeDirection(Direction::UP);
            }
            break;
        case 'd':
            if (m_snakeDirection != Direction::UP) {
                SetSnakeDirection(Direction::DOWN);
            }
            break;
        case 'l':
            if (m_snakeDirection != Direction::RIGHT) {
                SetSnakeDirection(Direction::LEFT);
            }
            break;
        case 'r':
            if (m_snakeDirection != Direction::LEFT) {
                SetSnakeDirection(Direction::RIGHT);
            }
            break;
        case 's':
            SetSnakeDirection(Direction::STOPPED);
            return;
    }

    // Check if the snake has hit the wall or itself
    bool snakeGrew = MoveSnake();
    m_gameBoard.Update(snakeGrew);
    if (snakeGrew) {
        ++m_score;
        PrintScore();
    }
}

void Game::PrintScore() {
    static bool init = false;
    if (!init) {
        // Move cursor to the start of the game area
        std::cout << "\033[1;1H" << "Score: " << m_score << std::endl;
        init = true;
    }
    else {
        std::cout << "\033[1;8H" << m_score;
    }
}

bool Game::SnakeWallHit() const {
    // Get the head of the snake
    std::pair<unsigned int, unsigned int> head = m_snake.GetHead();

    // Check if the head is at the edge of the grid
    return (head.first == 0 || head.first == m_gridWidth - 1 || head.second == 0 || head.second == m_gridHeight - 1);
}

bool Game::SnakeSelfHit() const {
    // Get the head of the snake
    std::pair<unsigned int, unsigned int> head = m_snake.GetHead();

    // Check if the head is at the same position as any other segment of the snake
    for (auto it = ++m_snake.GetSegments().begin(); it != m_snake.GetSegments().end(); ++it) {
        if (*it == head) {
            return true;
        }
    }

    return false;
}

// SnakeObstacleHit checks if the snake has hit an obstacle.
bool Game::SnakeObstacleHit() const {
    // Get the head of the snake
    std::pair<unsigned int, unsigned int> head = m_snake.GetHead();

    // Get the obstacles from the game board
    const std::set<std::pair<unsigned int, unsigned int>>& obstacles = m_gameBoard.GetObstacles();

    // Check if the head is at the same position as an obstacle
    return (obstacles.find(head) != obstacles.end());
}

// IsGameOver checks if the game is over.
bool Game::IsGameOver() {
    if (SnakeWallHit() || SnakeSelfHit() || SnakeObstacleHit()) {
        Draw(true);
        return true;
    }

    return false;
}

// IsGameWon checks if the game is won.
bool Game::IsGameWon() {
    // The game is over if the snake has filled the entire grid
    if (m_snake.GetSize() >= m_gameBoard.GetAvailableCells()) {
        Draw(false);
        return true;
    }

    return false;
}

bool Game::MoveSnake() {
    // Get the next position based on the current direction
    std::pair<unsigned int, unsigned int> nextPosition = GetSnakeNextPosition();
    if (CheckSnakeEatFruit(nextPosition)) {
        m_snake.Move(nextPosition, true);
        return true;
    } else {
        m_gameBoard.SetCell(m_snake.Move(nextPosition, false), GameBoard::CellType::Empty);
        return false;
    }
}

// GetNextPosition returns the next position of the snake head based on the current direction.
std::pair<unsigned int, unsigned int> Game::GetSnakeNextPosition() const {
    std::pair<unsigned int, unsigned int> step = std::make_pair(0, 0);
    switch (GetSnakeDirection()) {
        case Direction::UP:
            step.second = -1;
            break;
        case Direction::DOWN:
            step.second = 1;
            break;
        case Direction::LEFT:
            step.first = -1;
            break;
        case Direction::RIGHT:
            step.first = 1;
            break;
    }

    std::pair<unsigned int, unsigned int> nextPosition = m_snake.GetHead();
    if (nextPosition.first + step.first >= 0 && nextPosition.first + step.first < m_gridWidth &&
        nextPosition.second + step.second >= 0 && nextPosition.second + step.second < m_gridHeight) {
        nextPosition.first += step.first;
        nextPosition.second += step.second;
    }

    return nextPosition;
}

bool Game::CheckSnakeEatFruit() const {
    return (CheckSnakeEatFruit(m_snake.GetHead()));
}

bool Game::CheckSnakeEatFruit(std::pair<unsigned int, unsigned int> snakePosition) const {
    return (snakePosition == m_gameBoard.GetFruitPosition());
}

void Game::SetSnakeDirection(Direction dir) {
    m_snakeDirection = dir;
}

Direction Game::GetSnakeDirection() const {
    return m_snakeDirection;
}