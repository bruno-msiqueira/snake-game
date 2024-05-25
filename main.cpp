#include <cstdlib>
#include "Game.hpp"

// The main function starts the game.
int main(int argc, char* argv[]) {
    unsigned int gridWidth     = (argc < 2) ? 20 : std::atoi(argv[1]);
    unsigned int gridHeight    = (argc < 3) ? 10 : std::atoi(argv[2]);
    unsigned int obstacleCount = (argc < 4) ? 0  : std::atoi(argv[3]);

    Game game(gridWidth, gridHeight, obstacleCount);
    game.Run();
    return 0;
}