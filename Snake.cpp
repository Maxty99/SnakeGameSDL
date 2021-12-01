#include "Snake/Snake.h"
#include <SDL2/SDL.h>
#include <random>
#include <time.h>

Snake::Snake(const int& screen_width, const int& screen_height, const int& cell_width, const int& cell_height) {
    SCREEN_WIDTH = screen_width;
    SCREEN_HEIGHT = screen_height;
    CELL_WIDTH = cell_width;
    CELL_HEIGHT = cell_height;
    GamePiece head(28, 28, { 255, 255, 255 });
    head.setPos(CELL_WIDTH / 2, CELL_HEIGHT / 2);
    bodyParts.push_back(head);

}


void Snake::addBodyPart()
{
    int x, y;
    Direction facing;

    int* pos = bodyParts.back().getPos();
    x = *pos;
    y = *(pos + 1);
    facing = bodyParts.back().getFacing();

    GamePiece newPiece(28, 28, { 255, 255, 255 });
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

void Snake::draw(SDL_Surface* surface)
{
    for (int i = 0; i < bodyParts.size(); i++)
    {
        bodyParts.at(i).draw(surface);
    }
    fruit.draw(surface);
}


bool Snake::move()
{
    //Keep track of head being bonked or not
    bool headBonked = false;

    // (I admit this looks a little stupid but it lets me do bonk-checking in the for loop)

    // First move head

    int* pos = bodyParts.at(0).getPos();
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

    //Check fruit collision
    int* fruitPos = fruit.getPos();
    int fruitX = *fruitPos;
    int fruitY = *(fruitPos + 1);
    printf("(%d,%d)", fruitX, fruitY);
    if (newHeadX == fruitX && newHeadY == fruitY) {
        placeFruit();
        addBodyPart();
        score++;
    }

    // Check wall collision
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
            int* pos = bodyParts.at(i).getPos();
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


void Snake::setHeadDirection(Direction newDirection)
{
    bodyParts.at(0).setFacing(newDirection);
}

Direction Snake::getHeadDirection()
{
    return bodyParts.at(0).getFacing();
}

int Snake::getHeadX()
{
    int* pos = bodyParts.at(0).getPos();
    return *pos;
}

int Snake::getHeadY()
{
    int* pos = bodyParts.at(0).getPos();
    return *(pos + 1);
}

void Snake::placeFruit() {
    int maxX = SCREEN_WIDTH / CELL_WIDTH;
    int maxY = SCREEN_HEIGHT / CELL_HEIGHT;

    if (score < maxX * maxY - 1)
    {
        std::srand(time(0));
        // Coords to move fruit to 
        int x, y;
        //Brute force random algo
        bool placed = false;
        while (!placed) {
            placed = true;
            //Potential coords

            x = std::rand() % maxX;
            y = std::rand() % maxY;

            //Check if on snake
            for (int i = 0; i < bodyParts.size(); i++)
            {
                int* pos = bodyParts.at(i).getPos();
                int bodyX = *pos;
                int bodyY = *(pos + 1);
                // If its already false might as well skip, squeeze out extra clock cycles from this nightmarish algo
                if (placed && bodyX == x && bodyY == y) {
                    placed = false;
                }
            }
        }
        fruit.setPos(x * CELL_WIDTH + (CELL_WIDTH / 2), y * CELL_HEIGHT + (CELL_HEIGHT / 2));
    }
    else {
        won = true;
    }
}