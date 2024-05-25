#include <iostream>
#include <conio.h>
#include <cstdlib>
#include "Game.hpp"

void printGameInstructions();

// The main function starts the game.
int main(int argc, char* argv[]) {
    unsigned int gridWidth     = (argc < 2) ? 20   : std::atoi(argv[1]);
    unsigned int gridHeight    = (argc < 3) ? 10   : std::atoi(argv[2]);
    unsigned int obstacleCount = (argc < 4) ? 0    : std::atoi(argv[3]);
    unsigned int gameSpeed     = (argc < 5) ? 500  : std::atoi(argv[4]);
    char         silent        = (argc < 6) ? '\0' : *argv[5] & 0xDF;

    printf("\033[?25l"); // Hide cursor

    if (silent != 'S') {
        printGameInstructions();
        std::cout << "Press any key to start the game...\n";
        getchar();
    }

    Game* pGame = new Game(gridWidth, gridHeight, obstacleCount, gameSpeed);
    pGame->Run();
    std::cout << "\033[" << gridHeight + 3 << ";1H";
    if (pGame->IsGameOver())
    {
        std::cout << "Game Over!";
    }
    else if (pGame->IsGameWon())
    {
        std::cout << "Congratulations! You won!";
    }
    else
    {
        std::cout << "Game Abandoned!";
    }

    std::cout << "\033[" << gridHeight + 4 << ";1H\033[?25h"; // Move cursor and show it

    return 0;
}

void printGameInstructions() {
    std::cout << "Welcome to the Snake Game!\n";
    std::cout << "\nGame settings should be passed when running the game in the following order:\n";
    std::cout << "1. Grid width (default is 20)\n";
    std::cout << "2. Grid height (default is 10)\n";
    std::cout << "3. Obstacle count (default is 0)\n";
    std::cout << "4. Game speed (default is 500msec)\n";
    std::cout << "\nThe game starts in a paused state, waiting for a direction key to be pressed.\n";
    std::cout << "Press any key to start the game.\n";
    std::cout << "Here are the commands you can use:\n";
    std::cout << "1. Up Arrow: Move up (unless the last command was down)\n";
    std::cout << "2. Down Arrow: Move down (unless the last command was up)\n";
    std::cout << "3. Left Arrow: Move left (unless the last command was right)\n";
    std::cout << "4. Right Arrow: Move right (unless the last command was left)\n";
    std::cout << "5. 's' or 'S': Stop the snake\n";
    std::cout << "6. 'r' or 'R': Reset the game\n";
    std::cout << "7. 'q' or 'Q': Quit the game\n";
    std::cout << "Enjoy the game!\n\n";
}