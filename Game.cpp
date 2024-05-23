#include "Game.hpp"
#include "Utility.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <algorithm>
#include <chrono>

// Constructor initializes the game.
Game::Game(int grid_width, int grid_height)
        : snake(grid_width, grid_height),
            fruit(grid_width, grid_height, snake),
            gameOver(false),
            score(0),
            grid_width(grid_width),
            grid_height(grid_height),
            currentBuffer(grid_height, std::vector<char>(grid_width, ' ')),
            previousBuffer(grid_height, std::vector<char>(grid_width, ' ')) {
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

    while (!snake.IsGameOver()) {
        Draw();
        Input();
        Update();
    }
    Draw();
    std::cout << "\033[" << grid_height + 2 << ";1H\033[?25h"; // Move cursor and show it
}

// Draw renders the game state.
void Game::Draw() {
    // Fill the current buffer with the game state
    for (int i = 0; i < grid_height; ++i) {
        for (int j = 0; j < grid_width; ++j) {
            std::pair<int, int> point(j, i);

            if (snake.GetSegments()[0] == point) {
                if (snake.IsGameOver()) {
                    currentBuffer[i][j] = 'X'; // Draw 'X' if game is over
                } else {
                    currentBuffer[i][j] = 'H'; // Draw snake head
                }
            } else if (i == 0 || i == grid_height - 1) {
                currentBuffer[i][j] = '#'; // Draw top and bottom borders
            } else if (j == 0 || j == grid_width - 1) {
                currentBuffer[i][j] = '#'; // Draw left and right borders
            } else if (IsInSnakeBody(snake.GetSegments(), point)) {
                currentBuffer[i][j] = 'o'; // Draw snake body
            } else if (fruit.GetPosition() == point) {
                currentBuffer[i][j] = '*'; // Draw fruit
            } else {
                currentBuffer[i][j] = ' '; // Draw empty space
            }
        }
    }

    // Compare the current buffer with the previous one and update the screen
    for (int i = 0; i < grid_height; ++i) {
        for (int j = 0; j < grid_width; ++j) {
            if (currentBuffer[i][j] != previousBuffer[i][j]) {
                // Move the cursor to the position (j, i) and print the new character
                printf("\033[%d;%dH%c", i + 1, j + 1, currentBuffer[i][j]);
            }
        }
    }

    // Swap the buffers
    previousBuffer.swap(currentBuffer);
}
// Input handles user input.
bool Game::Input() {
    bool inputed = false;
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    lastVerticalCommand = lastHorizontalCommand = '\0';

    while (elapsed.count() < ITERATION_TIME) {
        if (_kbhit()) {
            switch (_getch()) {
            case 72: // Up arrow key
                if (lastVerticalCommand != 'd') {
                    lastVerticalCommand = 'u';
                }
                break;
            case 80: // Down arrow key
                if (lastVerticalCommand != 'u') {
                    lastVerticalCommand = 'd';
                }
                break;
            case 75: // Left arrow key
                if (lastHorizontalCommand != 'r') {
                    lastHorizontalCommand = 'l';
                }
                break;
            case 77: // Right arrow key
                if (lastHorizontalCommand != 'l') {
                    lastHorizontalCommand = 'r';
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

// Logic updates the game state.
void Game::Logic() {
}

void Game::Update() {
    // Update snake's direction based on lastHorizontalCommand and lastVerticalCommand
    if (lastHorizontalCommand == 'l' && lastVerticalCommand == 'u') {
        snake.SetDirection(Snake::Direction::UP_LEFT);
    } else if (lastHorizontalCommand == 'r' && lastVerticalCommand == 'u') {
        snake.SetDirection(Snake::Direction::UP_RIGHT);
    } else if (lastHorizontalCommand == 'l' && lastVerticalCommand == 'd') {
        snake.SetDirection(Snake::Direction::DOWN_LEFT);
    } else if (lastHorizontalCommand == 'r' && lastVerticalCommand == 'd') {
        snake.SetDirection(Snake::Direction::DOWN_RIGHT);
    } else if (lastHorizontalCommand == 'l') {
        snake.SetDirection(Snake::Direction::LEFT);
    } else if (lastHorizontalCommand == 'r') {
        snake.SetDirection(Snake::Direction::RIGHT);
    } else if (lastVerticalCommand == 'u') {
        snake.SetDirection(Snake::Direction::UP);
    } else if (lastVerticalCommand == 'd') {
        snake.SetDirection(Snake::Direction::DOWN);
    }

    // Move the snake in the updated direction
    snake.Move(snake.GetDirection());

    // Check for game over condition
    if (snake.SelfHit() || snake.WallHit()) {
        gameOver = true;
    }

    // Check if the snake has eaten the fruit
    if (snake.EatFruit(fruit)) {
        // Increase score and generate a new fruit
        score++;
        fruit.Generate(snake);

        // Add a new segment to the snake
        snake.Grow();
    }
}