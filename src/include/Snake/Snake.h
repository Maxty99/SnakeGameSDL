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
class Snake
{
private:

    std::vector<GamePiece> bodyParts;
    GamePiece fruit = GamePiece(28, 28);
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    int CELL_WIDTH;
    int CELL_HEIGHT;

public:

    Snake(const int& screen_width, const int& screen_height, const int& cell_width, const int& cell_height);

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
     * @brief Move the snake forward
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

    int getHeadX();
    int getHeadY();
};
#endif