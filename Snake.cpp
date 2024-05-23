#include "Snake.hpp"

// Constructor initializes the snake.
Snake::Snake(int grid_width, int grid_height) : grid_width(grid_width), grid_height(grid_height) {
    // Initialize snake with one segment at the center of the grid
    segments.push_back(std::make_pair(grid_width / 2, grid_height / 2));
    direction = Direction::RIGHT; // Start moving to the right
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

void Snake::SetDirection(Direction dir) {
    direction = dir;
}

Snake::Direction Snake::GetDirection() const {
    return direction;
}

// GetNextPosition returns the next position of the snake head based on the current direction.
std::pair<int, int> Snake::GetNextPosition() const {
    std::pair<int, int> next_position = segments[0];

    switch (direction) {
    case Direction::UP:
        next_position.second--;
        break;
    case Direction::DOWN:
        next_position.second++;
        break;
    case Direction::LEFT:
        next_position.first--;
        break;
    case Direction::RIGHT:
        next_position.first++;
        break;
    case Direction::UP_LEFT:
        next_position.second--;
        next_position.first--;
        break;
    case Direction::UP_RIGHT:
        next_position.second--;
        next_position.first++;
        break;
    case Direction::DOWN_LEFT:
        next_position.second++;
        next_position.first--;
        break;
    case Direction::DOWN_RIGHT:
        next_position.second++;
        next_position.first++;
        break;
    }

    return next_position;
}

// Move moves the snake in the current direction.
void Snake::Move(Direction dir) {
    // Get the next position based on the current direction
    std::pair<int, int> next_position = GetNextPosition();

    // Move the snake to the next position
    segments.insert(segments.begin(), next_position);
    segments.pop_back();
}

// Grow adds a new segment to the snake.
void Snake::Grow() {
    std::pair<int, int> next_position = GetNextPosition();
    segments.insert(segments.begin(), next_position);
}

bool Snake::SelfHit() {
    for (int i = 1; i < segments.size(); i++) {
        if (segments[0] == segments[i]) {
            return true;
        }
    }
    return false;
}

bool Snake::WallHit() {
    if (segments[0].first < 0 || segments[0].first >= grid_width ||
        segments[0].second < 0 || segments[0].second >= grid_height) {
        return true;
    }
    return false;
}

bool Snake::EatFruit(const Fruit& fruit) {
    if (segments[0] == fruit.GetPosition()) {
        return true;
    }
    return false;
}

bool Snake::IsPositionOccupied(const std::pair<int, int>& position) const {
    for (const auto& segment : segments) {
        if (segment == position) {
            return true;
        }
    }
    return false;
}