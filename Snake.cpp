#include "Snake.hpp"

// Constructor initializes the snake.
Snake::Snake(int grid_width, int grid_height) : grid_width(grid_width), grid_height(grid_height) {
    // Initialize snake with one segment at the center of the grid
    segments.push_back(std::make_pair(grid_width / 2, grid_height / 2));
    direction = 'r'; // Start moving to the right
}

// IsGameOver checks if the game is over.
bool Snake::IsGameOver() const {
    // The game is over if the snake has filled the entire grid
    if (GetSize() == (grid_height - 2) * (grid_width - 2)) {
        return true;
    }

    // The game is over if the snake has moved out of bounds
    auto head = segments.front();
    if (head.first == 0 || head.first >= grid_width - 1 || head.second == 0 || head.second >= grid_height - 1) {
        return true;
    }

    // The game is also over if the snake has collided with itself
    for (auto it = segments.begin() + 1; it != segments.end(); ++it) {
        if (*it == head) {
            return true;
        }
    }

    // Otherwise, the game is not over
    return false;
}

// GetSegments returns the segments of the snake.
std::vector<std::pair<int, int>> Snake::GetSegments() const {
    return segments;
}

// GetNextPosition returns the next position of the snake head based on the current direction.
std::pair<int, int> Snake::GetNextPosition() const {
    std::pair<int, int> next_position = segments.front();

    switch (direction) {
    case 'u':
        next_position.second--;
        break;
    case 'd':
        next_position.second++;
        break;
    case 'l':
        next_position.first--;
        break;
    case 'r':
        next_position.first++;
        break;
    }

    return next_position;
}

// Move moves the snake in the current direction.
void Snake::Move(char direction) {
    if (direction) {
        this->direction = direction;
    }

    std::pair<int, int> next_position = GetNextPosition();
    segments.insert(segments.begin(), next_position);
    segments.pop_back();
}

// Grow adds a new segment to the snake.
void Snake::Grow() {
    std::pair<int, int> next_position = GetNextPosition();
    segments.insert(segments.begin(), next_position);
}