#include <cstdlib>
#include "Game.hpp"

// The main function starts the game.
int main(int argc, char* argv[]) {
    int gridWidth = (argc < 2) ? 20 : std::atoi(argv[1]);
    int gridHeight =(argc < 3) ? 10 : std::atoi(argv[2]);

    Game game(gridWidth, gridHeight);
    game.Run();
    return 0;
}