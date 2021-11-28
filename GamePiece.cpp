#include <SDL2/SDL.h>
#include "Snake/GamePiece.h"

/**
* @brief Set the position of the Snake Piece object
*
* @param x
* @param y
*/

GamePiece::GamePiece(int width, int height) {
    snakeblockWidth = width;
    snakeblockHeight = height;

}

void GamePiece::setPos(int x, int y) {
    pos[0] = x;
    pos[1] = y;

}

/**
* @brief Get the position of the Snake Piece object
*
* @return The pointer to the pos array of the object
*/

int* GamePiece::getPos() {
    return pos;
}

/**
* @brief Set the the direction this Snake Piece is 'facing'
*
* @param newDirection
*/

void GamePiece::setFacing(Direction newDirection) {
    facing = newDirection;
}

/**
* @brief Get the the direction this Snake Piece is 'facing'
*
* @return The direction Snake Piece is facing
*/

Direction GamePiece::getFacing() {
    return facing;
}

/**
* @brief Draw the object on some SDL_Surface
*
* @param surface is the SDL_Surface that will be drawn on
*/

void GamePiece::draw(SDL_Surface* surface) {
    SDL_Rect r = { pos[0] - (snakeblockWidth / 2),
                   pos[1] - (snakeblockHeight / 2),
                   snakeblockWidth,
                   snakeblockHeight };

    SDL_FillRect(surface, &r, 0xFFFFFF);
}
