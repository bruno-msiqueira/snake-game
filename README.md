# Snake Game

This repository contains the source code for a simple console-based Snake game. It was developed as a laboratory for using GitHub Copilot as a developer support tool.

## Compilation

To compile the game, use the following command:

```bash
$ g++ -o game.exe main.cpp Game.cpp GameBoard.cpp Snake.cpp Utility.cpp
```

## Running the Game

To run the game, use the following command:

```bash
$ ./game.exe [gridWidth] [gridHeight] [obstacleCount] [gameSpeed] [silent]
```

- gridWidth: The width of the game grid (default: 20)
- gridHeight: The height of the game grid (default: 10)
- obstacleCount: The number of obstacles in the game (default: 0)
- gameSpeed: The speed of the game (default: 500)
- silent: Pass 's' or 'S' to suppress the printing of game instructions

## Game Instructions

The game starts in a paused state, waiting for a direction key to be pressed. You can press any key to start the game. The commands that can be used in the game include:

- Moving up: Arrow UP
- Moving down:  Arrow DOWN
- Moving left:  Arrow LEFT
- Moving right:  Arrow RIGH
- Stopping the snake: 'p' or 'P'
- Reset the game: 'r' or 'R'
- Quit the game: 'q' or 'Q'

Remember, the game ends when the snake hits the grid boundaries, an obstacle, or itself.

## Game Elements

Here's a breakdown of the visual elements you'll encounter in the game:

- **|#|** **Game Grid**: This is the area where the snake moves. It's defined by the `gridWidth` and `gridHeight` parameters when running the game. The grid boundaries are usually represented by a different character or color.
- **|H|** **Snake Head**: The head of the snake is usually differentiated from the body to help you identify the direction of movement.
- **|O|** **Snake Body**: The body of the snake is represented by a series of connected characters moving across the game grid.
- **|*|** **Fruit**: Food items appear randomly on the game grid. The snake grows in length each time it eats a food item.
- **|#|** **Obstacles**: If the `obstacleCount` parameter is greater than 0, there will be obstacles placed randomly on the game grid. The snake cannot pass through these obstacles.
- **Score**: The score is usually displayed at the top or bottom of the game grid. The score increases each time the snake eats a food item.
- **| |** **Empty Space**: This represents the unoccupied areas on the game grid where the snake can move. In the game's visual representation, empty spaces might be represented by a specific character or simply left blank.



## Screenshots

### SCR-01

```
$ ./game.exe 5 5 1
Welcome to the Snake Game!

Game settings should be passed when running the game in the following order:
1. Grid width (default is 20)
2. Grid height (default is 10)
3. Obstacle count (default is 0)
4. Game speed (default is 500msec)

The game starts in a paused state, waiting for a direction key to be pressed.
Press any key to start the game.
Here are the commands you can use:
1. Up Arrow: Move up (unless the last command was down)
2. Down Arrow: Move down (unless the last command was up)
3. Left Arrow: Move left (unless the last command was right)
4. Right Arrow: Move right (unless the last command was left)
5. 's' or 'S': Stop the snake
6. 'r' or 'R': Reset the game
7. 'q' or 'Q': Quit the game
Enjoy the game!

Press any key to start the game...
```

### SCR-02

```
Score: 0
#####
#  *#
##H #
#   #
#####
```

### SCR-03

```
Score: 2
#####
XOO #
##  #
#*  #
#####

Game Over!
```

### SCR-04

```
Score: 10
########
# O #  #
# O    #
# O H  #
# O O  #
# O#O ##
#*OOO  #
########
```

### SCR-05

```
Score: 0
######
# #  #
#   *#
#  H##
#   ##
######

Game Abandoned!
```

### SCR-06

```
Score: 10
#####
##OO#
#OOH#
#OOO#
#OOO#
#####

Congratulations! You won!
```

### SCR-07

```
Score: 0
###############
#          #  #
#             #
#             #
# # #   *     #
#      H      #
#    #     #  #
#             #
##       #    #
###############
```

**Enjoy the game!**
