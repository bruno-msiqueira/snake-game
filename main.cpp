#include "Game.hpp"

// The main function starts the game.
int main() {
    int grid_width = 20;
    int grid_height = 10;
    Game game(grid_width, grid_height);
    game.Run();
    return 0;
}