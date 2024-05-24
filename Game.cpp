#include "Game.hpp"
#include "Utility.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <algorithm>
#include <chrono>

// Constructor initializes the game.
Game::Game(int grid_width, int grid_height)
        :   m_snake(grid_width, grid_height),
            m_boardGame(grid_width, grid_height, &m_snake),
            m_gameOver(false),
            m_score(0),
            m_gridWidth(grid_width),
            m_gridHeight(grid_height),
            m_currentBuffer(grid_height, std::vector<char>(grid_width, ' ')),
            m_previousBuffer(grid_height, std::vector<char>(grid_width, ' ')) {
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

    while (!m_snake.IsGameOver() && !m_snake.IsGameWon()) {
        Draw();
        Input();
        Update();
    }

    Draw();
    std::cout << "\033[" << m_gridHeight + 2 << ";1H\033[?25h"; // Move cursor and show it
}

// Draw renders the game state.
void Game::Draw() {
    PrintScore();

    // Fill the current buffer with the game state
    for (int i = 0; i < m_gridHeight; ++i) {
        for (int j = 0; j < m_gridWidth; ++j) {
            std::pair<int, int> point(j, i);

            if (m_snake.GetSegments()[0] == point) {
                if (m_snake.IsGameOver()) {
                    m_currentBuffer[i][j] = 'X'; // Draw 'X' if game is over
                } else {
                    m_currentBuffer[i][j] = 'H'; // Draw snake head
                }
            } else if (i == 0 || i == m_gridHeight - 1) {
                m_currentBuffer[i][j] = '#'; // Draw top and bottom borders
            } else if (j == 0 || j == m_gridWidth - 1) {
                m_currentBuffer[i][j] = '#'; // Draw left and right borders
            } else if (IsInSnakeBody(m_snake.GetSegments(), point)) {
                m_currentBuffer[i][j] = 'O'; // Draw snake body
            } else if (m_boardGame.GetFruitPosition() == point) {
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
    m_lastVerticalCommand = m_lastHorizontalCommand = '\0';

    while (elapsed.count() < ITERATION_TIME) {
        if (_kbhit()) {
            switch (_getch()) {
            case 72: // Up arrow key
                if (m_lastVerticalCommand != 'd') {
                    m_lastVerticalCommand = 'u';
                }
                break;
            case 80: // Down arrow key
                if (m_lastVerticalCommand != 'u') {
                    m_lastVerticalCommand = 'd';
                }
                break;
            case 75: // Left arrow key
                if (m_lastHorizontalCommand != 'r') {
                    m_lastHorizontalCommand = 'l';
                }
                break;
            case 77: // Right arrow key
                if (m_lastHorizontalCommand != 'l') {
                    m_lastHorizontalCommand = 'r';
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
    if (m_lastHorizontalCommand == 'l') {
        m_snake.SetDirection(Snake::Direction::LEFT);
    } else if (m_lastHorizontalCommand == 'r') {
        m_snake.SetDirection(Snake::Direction::RIGHT);
    } else if (m_lastVerticalCommand == 'u') {
        m_snake.SetDirection(Snake::Direction::UP);
    } else if (m_lastVerticalCommand == 'd') {
        m_snake.SetDirection(Snake::Direction::DOWN);
    }

    // Check if the snake has hit the wall or itself
    if (m_boardGame.Update()) {
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