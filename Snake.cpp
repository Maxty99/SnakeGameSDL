#include "Snake/Snake.h"
#include <SDL2/SDL.h>

Snake::Snake(const int &screen_width, const int &screen_height, const int &cell_width, const int &cell_height)
{
    // addBodyPart();
    SCREEN_WIDTH = screen_width;
    SCREEN_HEIGHT = screen_height;
    CELL_WIDTH = cell_width;
    CELL_HEIGHT = cell_height;
}

/**
* @brief Adds a new bodypart to the end of the Snake
*
*/

void Snake::addBodyPart()
{
    int x, y;
    Direction facing;

    int *pos = bodyParts.back().getPos();
    x = *pos;
    y = *(pos + 1);
    facing = bodyParts.back().getFacing();

    SnakePiece newPiece(28, 28);
    switch (facing)
    {
    case left:
        newPiece.setPos(x + CELL_WIDTH, y);
        newPiece.setFacing(left);
        break;
    case right:
        newPiece.setPos(x - CELL_WIDTH, y);
        newPiece.setFacing(right);
        break;
    case up:
        newPiece.setPos(x, y + CELL_HEIGHT);
        newPiece.setFacing(up);
        break;
    case down:
        newPiece.setPos(x, y - CELL_HEIGHT);
        newPiece.setFacing(down);
        break;
    }

    bodyParts.push_back(newPiece);
}

/**
* @brief Calls draw function on each member of the Snake
*
* @param surface Is the surface to be drawn on
*/

void Snake::draw(SDL_Surface *surface)
{
    for (int i = 0; i < bodyParts.size(); i++)
    {
        bodyParts.at(i).draw(surface);
    }
}

/**
* @brief Move the snake forward
*
* @returns true if the snake hit a wall or itself
* @returns false if the snake didnt hit anything
*/

bool Snake::move()
{
    //Keep track of head being bonked or not
    bool headBonked = false;

    // (I admit this looks a little stupid but it lets me do bonk-checking in the for loop)

    // First do for head

    int *pos = bodyParts.at(0).getPos();
    int headX = *pos;
    int headY = *(pos + 1);
    Direction headFacing = bodyParts.at(0).getFacing();

    int newHeadX, newHeadY;

    switch (headFacing)
    {
    case left:
        newHeadX = headX - CELL_WIDTH;
        newHeadY = headY;
        break;
    case right:
        newHeadX = headX + CELL_WIDTH;
        newHeadY = headY;
        break;
    case up:
        newHeadX = headX;
        newHeadY = headY - CELL_HEIGHT;
        break;
    case down:
        newHeadX = headX;
        newHeadY = headY + CELL_HEIGHT;
        break;
    }

    if (newHeadX < 0 || newHeadY < 0 || newHeadX > SCREEN_WIDTH || newHeadY > SCREEN_HEIGHT)
    {
        headBonked = true;
    }

    bodyParts.at(0).setPos(newHeadX, newHeadY);

    if (!bodyParts.empty())
    {
        // variables used to store the previously moved snake part's position and facing direction
        int prevX, prevY;
        Direction prevFacing;

        //Since the head was previously moved we store the values in the variables
        prevX = headX;
        prevY = headY;
        prevFacing = headFacing;

        // Moving up every single member except head. Also check if head will bonk into it
        for (int i = 1; i < bodyParts.size(); i++)
        {
            //Temp variables
            int *pos = bodyParts.at(i).getPos();
            int x = *pos;
            int y = *(pos + 1);

            Direction facing = bodyParts.at(i).getFacing();

            //Move
            bodyParts.at(i).setFacing(prevFacing);
            bodyParts.at(i).setPos(prevX, prevY);

            // Bonk-checking
            if (!headBonked && prevX == newHeadX && prevY == newHeadY)
            {
                headBonked = true;
            }

            //Store for next iteration
            prevFacing = facing;
            prevX = x;
            prevY = y;
        }
    }

    return headBonked;
}

/**
* @brief Set the Head Direction
*
* @param newDirection
*/

void Snake::setHeadDirection(Direction newDirection)
{
    bodyParts.at(0).setFacing(newDirection);
}

/**
* @brief Get the Head Direction
*
* @return Direction
*/

Direction Snake::getHeadDirection()
{
    return bodyParts.at(0).getFacing();
}

int Snake::getHeadX()
{
    int *pos = bodyParts.at(0).getPos();
    return *pos;
}

int Snake::getHeadY()
{
    int *pos = bodyParts.at(0).getPos();
    return *(pos + 1);
}