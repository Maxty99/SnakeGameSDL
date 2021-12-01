#include <vector>
#include "SDL2/SDL.h"
#include "GamePiece.h"

#ifndef DIRECTION_ENUM
#define DIRECTION_ENUM  
//Enum for determining where Snake Piece is facing
enum Direction { left, right, up, down };
#endif 

#ifndef SNAKE_H
#define SNAKE_H

/**
 * @brief The main Snake game class, contains all the logic for the game
 *
 */
class SnakeGame
{
private:

    std::vector<GamePiece> bodyParts;
    GamePiece fruit = GamePiece(28, 28, { 255, 0, 0 });
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    int CELL_WIDTH;
    int CELL_HEIGHT;
    int SNAKE_BLOCK_WIDTH;
    int SNAKE_BLOCK_HEIGHT;
    int score = 0;
    bool won = false;

public:

    SnakeGame(const int& screenWidth, const int& screenHeight, const int& cellWidth, const int& cellHeight, const int& snakeBlockWidth, const int& snakeBlockHeight);

    /**
     * @brief Adds a new bodypart to the end of the Snake
     *
     */
    void addBodyPart();

    /**
     * @brief Calls draw function on each member of the Snake
     *
     * @param surface Is the surface to be drawn on
     */
    void draw(SDL_Surface* surface);

    /**
     * @brief Move the snake forward and check collision
     *
     * @returns true if the snake hit a wall or itself
     * @returns false if the snake didnt hit anything
     */
    bool move();

    /**
     * @brief Set the Head Direction
     *
     * @param newDirection
     */
    void setHeadDirection(Direction newDirection);

    /**
     * @brief Get the Head Direction
     *
     * @return Direction
     */
    Direction getHeadDirection();

    /**
     * @brief Get the Head X
     */
    int getHeadX();

    /**
     * @brief Get the Head Y
     */
    int getHeadY();

    /**
     * @brief Places an fruit in a valid square in the game
     *
     */
    void placeFruit();
};
#endif