#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <vector>
#include <set>
#include <utility> // For std::pair

// The Snake class represents the snake.
class Snake {
public:
    // Constructor initializes the snake.
    Snake(unsigned int gridWidth, unsigned int gridHeight);

    // GetSegments returns the segments of the snake.
    const std::vector<std::pair<unsigned int, unsigned int>>& GetSegments() const;

    // Move moves the snake in the current direction.
    unsigned int GetSize() const;

    // Move moves the snake in the current direction.
    std::pair<unsigned int, unsigned int> GetHead() const;

    // GetLastSegment returns the last segment of the snake.
    std::pair<unsigned int, unsigned int> GetTail() const;

    // IsAtPosition checks if the snake is at the given position.
    bool IsAtPosition(const std::pair<unsigned int, unsigned int>& position) const;

    // Move moves the snake to the next position.
    std::pair<unsigned int, unsigned int> Move(const std::pair<unsigned int, unsigned int>& next_position, bool grow);

private:
    std::vector<std::pair<unsigned int, unsigned int>> m_segments;
};

#endif