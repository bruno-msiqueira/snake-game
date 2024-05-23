#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <vector>
#include <utility> // For std::pair

// The Snake class represents the snake.
class Snake {
public:
    // Constructor initializes the snake.
    Snake(int grid_width, int grid_height);
    // IsGameOver checks if the game is over.
    bool IsGameOver() const;
    // GetSegments returns the segments of the snake.
    std::vector<std::pair<int, int>> GetSegments() const;
    // GetNextPosition returns the next position of the snake head based on the current direction.
    std::pair<int, int> GetNextPosition() const;
    // Move moves the snake in the current direction.
    void Move(char direction = 0);
    // Grow adds a new segment to the snake.
    void Grow();
    inline int GetSize() const { return segments.size(); }
private:
    std::vector<std::pair<int, int>> segments;
    char direction;
    int grid_width;
    int grid_height;
};

#endif