#ifndef FRUIT_HPP
#define FRUIT_HPP

#include <utility> // For std::pair
#include "Snake.hpp"

// The Fruit class represents the fruit.
class Fruit {
public:
    // Constructor initializes the fruit.
    Fruit(int grid_width, int grid_height, const Snake& snake);
    // GetPosition returns the fruit's position.
    std::pair<int, int> GetPosition() const;
    // ResetPosition sets a new random position for the fruit.
    void ResetPosition(const Snake& snake);
private:
    std::pair<int, int> position;
    int grid_width;
    int grid_height;
};

#endif