
#ifndef DIRECTION_ENUM
#define DIRECTION_ENUM  
//Enum for determining where Snake Piece is facing
enum Direction { left, right, up, down };
#endif 

#ifndef SNAKEPIECE_H
#define SNAKEPIECE_H
class SnakePiece {
private:
    Direction facing = right;
    // [x,y] of the middle of the square 
    int pos[2];
    int snakeblockWidth;
    int snakeblockHeight;

public:

    SnakePiece(int width, int height);

    /**
     * @brief Set the position of the Snake Piece object
     *
     * @param x
     * @param y
     */
    void setPos(int x, int y);

    /**
     * @brief Get the position of the Snake Piece object
     *
     * @return The pointer to the pos array of the object
     */
    int* getPos();

    /**
     * @brief Set the the direction this Snake Piece is 'facing'
     *
     * @param newDirection
     */
    void setFacing(Direction newDirection);

    /**
     * @brief Get the the direction this Snake Piece is 'facing'
     *
     * @return The direction Snake Piece is facing
     */
    Direction getFacing();

    /**
     * @brief Draw the object on some SDL_Surface
     *
     * @param surface is the SDL_Surface that will be drawn on
     */
    void draw(SDL_Surface* surface);
};
#endif 