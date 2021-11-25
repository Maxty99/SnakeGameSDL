#include <SDL2/SDL.h>
#include "Snake/SnakePiece.h"

/**
* @brief Set the position of the Snake Piece object
*
* @param x
* @param y
*/

void SnakePiece::setPos(int x, int y) {
    pos[0] = x;
    pos[1] = y;
}

/**
* @brief Get the position of the Snake Piece object
*
* @return The pointer to the pos array of the object
*/

int* SnakePiece::getPos() {
    return pos;
}

/**
* @brief Set the the direction this Snake Piece is 'facing'
*
* @param newDirection
*/

void SnakePiece::setFacing(Direction newDirection) {
    facing = newDirection;
}

/**
* @brief Get the the direction this Snake Piece is 'facing'
*
* @return The direction Snake Piece is facing
*/

Direction SnakePiece::getFacing() {
    return facing;
}

/**
* @brief Draw the object on some SDL_Surface
*
* @param surface is the SDL_Surface that will be drawn on
*/

void SnakePiece::draw(SDL_Surface* surface) {
    SDL_Rect r = { pos[0] - (28 / 2),
                   pos[1] - (28 / 2),
                   28,
                   28 };

    SDL_FillRect(surface, &r, 0xFFFFFF);
}
