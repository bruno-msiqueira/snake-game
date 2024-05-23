#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <vector>
#include <utility> // For std::pair
#include "Fruit.hpp"

// Forward declaration of Fruit
class Fruit;

// The Snake class represents the snake.
class Snake {
public:
    enum class Direction { UP, DOWN, LEFT, RIGHT, UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT };

    // Constructor initializes the snake.
    Snake(int grid_width, int grid_height);
    // IsGameOver checks if the game is over.
    bool IsGameOver() const;
    // GetSegments returns the segments of the snake.
    std::vector<std::pair<int, int>> GetSegments() const;
    // GetNextPosition returns the next position of the snake head based on the current direction.
    std::pair<int, int> GetNextPosition() const;
    // Move moves the snake in the current direction.
    void Move(Direction dir);
    // Grow adds a new segment to the snake.
    void Grow();
    bool SelfHit();
    bool WallHit();
    bool EatFruit(const Fruit &fruit);
    inline int GetSize() const { return segments.size(); }

    void SetDirection(Direction dir);
    Direction GetDirection() const;
    bool IsPositionOccupied(const std::pair<int, int>& position) const;

private:
    std::vector<std::pair<int, int>> segments;
    Direction direction = Direction::RIGHT; // Default to moving right
    int grid_width;
    int grid_height;
};

#endif