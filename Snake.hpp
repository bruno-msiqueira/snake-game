#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <vector>
#include <set>
#include <utility> // For std::pair

// The Snake class represents the snake.
class Snake {
public:
    enum class Direction { UP, DOWN, LEFT, RIGHT };

    // Constructor initializes the snake.
    Snake(int grid_width, int grid_height);

    // GetSegments returns the segments of the snake.
    const std::vector<std::pair<unsigned int, unsigned int>>& GetSegments() const;
    // GetLastSegment returns the last segment of the snake.
    std::pair<unsigned int, unsigned int> GetLastSegment() const;
    // GetNextPosition returns the next position of the snake head based on the current direction.
    std::pair<unsigned int, unsigned int> GetNextPosition() const;
    // Move moves the snake in the current direction.
    std::pair<unsigned int, unsigned int> Move(bool fruitEaten);
    // Move moves the snake in the current direction.
    std::pair<unsigned int, unsigned int> Move(Direction dir, bool fruitEaten);
    bool SelfHit() const;
    bool WallHit() const;
    bool EatFruit(const std::pair<unsigned int, unsigned int> fruitPosition);
    inline int GetSize() const { return m_segments.size(); }
    std::pair<unsigned int, unsigned int> GetHead() const;

    void SetDirection(Direction dir);
    Direction GetDirection() const;
    bool IsPositionOccupied(const std::pair<unsigned int, unsigned int>& position) const;
    bool IsAtPosition(const std::pair<unsigned int, unsigned int>& position) const;

private:
    std::vector<std::pair<unsigned int, unsigned int>> m_segments;
    Direction m_direction = Direction::RIGHT; // Default to moving right
    int m_gridWidth;
    int m_gridHeight;
};

#endif