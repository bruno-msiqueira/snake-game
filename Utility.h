// Utility.h
#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include <utility>
#include <string>

/**
 * @brief Checks if a given point is present in the snake's body.
 *
 * @param body The vector representing the snake's body.
 * @param point The point to check.
 * @return true if the point is present in the snake's body, false otherwise.
 */
bool IsInSnakeBody(const std::vector<std::pair<unsigned int, unsigned int>>& body, const std::pair<unsigned int, unsigned int>& point);

/**
 * @brief Retrieves the clear command for the current operating system.
 *
 * This function returns the command that can be used to clear the console screen
 * based on the current operating system. The returned command can be used to
 * clear the console screen and provide a clean output for the snake game.
 *
 * @return The clear command for the current operating system.
 */
std::string GetClearCommand();


#endif // UTILITY_H