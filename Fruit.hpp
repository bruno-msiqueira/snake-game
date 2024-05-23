#ifndef FRUIT_HPP
#define FRUIT_HPP

#include <utility> // For std::pair
#include "Snake.hpp"

// Forward declaration of Snake
class Snake;

// The Fruit class represents the fruit.
/**
 * @class Fruit
 * @brief Represents a fruit in the snake game.
 * 
 * The Fruit class is responsible for managing the position and behavior of a fruit in the game grid.
 */
class Fruit {
public:
    /**
     * @brief Constructs a Fruit object.
     *
     * This constructor initializes the fruit with the given grid width, grid height, and snake object.
     *
     * @param grid_width The width of the game grid.
     * @param grid_height The height of the game grid.
     * @param snake The snake object.
     */
    Fruit(int grid_width, int grid_height, const Snake& snake);

    /**
     * @brief Gets the position of the fruit.
     *
     * @return The position of the fruit as a pair of integers (x, y).
     */
    std::pair<int, int> GetPosition() const;

    /**
     * @brief Resets the position of the fruit.
     *
     * This function sets a new random position for the fruit, ensuring that it does not overlap with the snake.
     *
     * @param snake The snake object.
     */
    void ResetPosition(const Snake& snake);

    /**
     * @brief   Generates a new fruit on the game board.
     *
     * @param[in]   snake   The snake object.
     */
    void Generate(const Snake& snake);

private:
    std::pair<int, int> position; ///< The position of the fruit.
    int grid_width; ///< The width of the game grid.
    int grid_height; ///< The height of the game grid.
};

#endif