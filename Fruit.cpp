#include "Fruit.hpp"
#include "Utility.h"
#include <cstdlib> // For rand() and srand()
#include <ctime> // For time()

// Constructor initializes the fruit.
Fruit::Fruit(int grid_width, int grid_height, const Snake& snake) : grid_width(grid_width), grid_height(grid_height) {
    srand(time(0)); // Initialize random seed
    ResetPosition(snake); // Set initial position
}

// GetPosition returns the fruit's position.
std::pair<int, int> Fruit::GetPosition() const {
    return position;
}

// ResetPosition sets a new random position for the fruit.
void Fruit::ResetPosition(const Snake& snake) {
    int x, y;
    std::pair<int, int> new_position;

    do {
        x = (rand() % (grid_width - 2)) + 1;
        y = (rand() % (grid_height - 2)) + 1;
        new_position = std::make_pair(x, y);
    } while (IsInSnakeBody(snake.GetSegments(), new_position));

    position = new_position;
}