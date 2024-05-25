#include "Game.hpp"
#include "Utility.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <algorithm>
#include <chrono>

// Constructor initializes the game.
Game::Game(unsigned int gridWidth, unsigned int gridHeight, unsigned int obstacleCount)
        :   m_snake(gridWidth, gridHeight),
            m_gameBoard(gridWidth, gridHeight, obstacleCount, &m_snake),
            m_gameOver(false),
            m_score(0),
            m_gridWidth(gridWidth),
            m_gridHeight(gridHeight),
            m_currentBuffer(gridHeight, std::vector<char>(gridWidth, ' ')),
            m_previousBuffer(gridHeight, std::vector<char>(gridWidth, ' ')) {
    // Initialize game
    // Clear the console
    system(GetClearCommand().c_str());
}

void Game::SetIterationTime(double time) {
    ITERATION_TIME = time;
}

// Run starts the game loop.
void Game::Run() {
    printf("\033[?25l"); // Hide cursor
    bool isGameOver = false;
    do
    {
        isGameOver = IsGameOver();
        Draw(isGameOver);
        Input();
        Update();
    } while (!isGameOver && !IsGameWon());

    std::cout << "\033[" << m_gridHeight + 2 << ";1H\033[?25h"; // Move cursor and show it
}

// Draw renders the game state.
void Game::Draw(bool isGameOver) {
    PrintScore();

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
    m_lastCommand = '\0';

    while (elapsed.count() < ITERATION_TIME) {
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
            }
            inputed = true;
        }

        end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;
    }

    return inputed;
}

char Game::Opposite(char command) {
    switch (command) {
        case 'w': return 's';
        case 's': return 'w';
        case 'a': return 'd';
        case 'd': return 'a';
        default: return '\0';
    }
}

void Game::Update() {
    // Update snake's direction based on lastHorizontalCommand and lastVerticalCommand
    if (m_lastCommand == 'l') {
        m_snake.SetDirection(Snake::Direction::LEFT);
    } else if (m_lastCommand == 'r') {
        m_snake.SetDirection(Snake::Direction::RIGHT);
    } else if (m_lastCommand == 'u') {
        m_snake.SetDirection(Snake::Direction::UP);
    } else if (m_lastCommand == 'd') {
        m_snake.SetDirection(Snake::Direction::DOWN);
    }

    // Check if the snake has hit the wall or itself
    if (m_gameBoard.Update()) {
        ++m_score;
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
bool Game::IsGameOver() const {
    return (SnakeWallHit() || SnakeSelfHit() || SnakeObstacleHit());
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
