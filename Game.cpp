#include "Game.hpp"
#include "Utility.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <algorithm>

// Constructor initializes the game.
Game::Game(int grid_width, int grid_height) : snake(grid_width, grid_height), fruit(grid_width, grid_height, snake), grid_width(grid_width), grid_height(grid_height) {
    // Initialize game
}

// Run starts the game loop.
void Game::Run() {
    while (!snake.IsGameOver()) {
        Draw();
        bool newCommand = Input();
        Sleep(500);
        if (!newCommand) {
            Input();
        }
        Logic();
    }
    Draw();
}

// Draw renders the game state.
void Game::Draw() {
    // Clear the console
    system("clear");

    // Draw the game state with side borders
    for (int i = 0; i < grid_height; ++i) {
        for (int j = 0; j < grid_width; ++j) {

            std::pair<int, int> point(j, i);

            if (snake.GetSegments()[0] == point) {
                if (snake.IsGameOver()) {
                    std::cout << "X"; // Draw 'X' if game is over
                } else {
                    std::cout << "H"; // Draw snake head
                }
            } else if (i == 0 || i == grid_height - 1) {
                std::cout << "#"; // Draw top and bottom borders
            } else if (j == 0 || j == grid_width - 1) {
                std::cout << "#"; // Draw left and right borders
            } else if (IsInSnakeBody(snake.GetSegments(), point)) {
                std::cout << "o"; // Draw snake body
            } else if (fruit.GetPosition() == point) {
                std::cout << "*"; // Draw fruit
            } else {
                std::cout << " "; // Draw empty space
            }
        }
        std::cout << "\n";
    }
}
// Input handles user input.
bool Game::Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 72: // Up arrow key
            snake.Move('u');
            break;
        case 80: // Down arrow key
            snake.Move('d');
            break;
        case 75: // Left arrow key
            snake.Move('l');
            break;
        case 77: // Right arrow key
            snake.Move('r');
            break;
        }
        return true;
    }
    return false;
}

// Logic updates the game state.
void Game::Logic() {
    std::pair<int, int> next_position = snake.GetNextPosition();

    if (next_position == fruit.GetPosition()) {
        snake.Grow();
        fruit.ResetPosition(snake);
    } else {
        snake.Move();
    }
}
