/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> //For loading images
#include <SDL2/SDL_ttf.h>   //For loading/displaying text
#include "SnakePiece.cpp"
#include "Snake.cpp"
#include <stdio.h>
#include <string>
#include <vector>

// Cell w and h for snake blocks to fit in
const int CELL_WIDTH = 30;
const int CELL_HEIGHT = 30;

// Snake block w and h
const int SNAKE_BLOCK_WIDTH = 28;
const int SNAKE_BLOCK_HEIGHT = 28;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface *loadSurface(std::string path);

//The window we'll be rendering to
SDL_Window *gWindow = NULL;

//The surface contained by the window
SDL_Surface *gScreenSurface = NULL;

//Font used to display text
TTF_Font *font = NULL;

//Defining some colors
SDL_Color White = {255, 255, 255};
SDL_Color Red = {255, 0, 0};
SDL_Color Green = {0, 255, 0};
SDL_Color Blue = {0, 0, 255};

/*
+----------+-----------+-----------+
|  (x0,y0) |  (x1,y0)  |  (x2,y0)  |
+----------+-----------+-----------+
|  (x0,y1) |  (x1,y1)  |  (x2,y1)  |
+----------+-----------+-----------+
|  (x0,y2) |  (x1,y2)  |  (x2,y2)  |
+----------+-----------+-----------+

The play field will be a grid of x by y blocks where a Snake piece is sx by yx pixels
The middle of each block will then just be calculated as its (xidx * x + x/2, yidx * y + y/2)
*/

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags))
            {
                printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                success = false;
            }
            if (TTF_Init() == -1)
            {
                printf("TTF_Init could not initialize! TTF_Init Error: %s\n", TTF_GetError());
                success = false;
            }
            else
            {
                //Get window surface
                gScreenSurface = SDL_GetWindowSurface(gWindow);
            }
        }
    }

    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load font
    font = TTF_OpenFont("FreeSans.ttf", 24);
    if (font == NULL)
    {
        printf("Failed to load PNG image!\n");
        success = false;
    }

    return success;
}

void close()
{

    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

SDL_Surface *loadSurface(std::string path)
{
    //The final optimized image
    SDL_Surface *optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
        if (optimizedSurface == NULL)
        {
            printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return optimizedSurface;
}

int main(int argc, char *args[])
{
    //Start up SDL and create window
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        //Load media
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {

            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            Snake snake(SCREEN_WIDTH, SCREEN_HEIGHT, CELL_WIDTH, CELL_HEIGHT);
            snake.addBodyPart();
            snake.addBodyPart();
            snake.addBodyPart();
            snake.addBodyPart();
            // printf("%d, %d", snake.getHeadX(), snake.getHeadY());
            bool directionSet;

            Uint32 mTicksCount = 0;

            //While application is running
            while (!quit)
            {
                // Delta time is the difference in ticks from last frame
                // (converted to seconds)
                float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
                // Update tick counts for next frame if enough time has passed
                if (deltaTime > .1)
                {
                    mTicksCount = SDL_GetTicks();
                }

                //Color in blank
                SDL_FillRect(gScreenSurface, NULL, 0);

                //Handle events on queue
                while (SDL_PollEvent(&e) != 0)
                {
                    //User requests quit
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }

                    // handle keydown event
                    if (e.type == SDL_KEYDOWN)
                    {
                        // look for the key pushed down.

                        if (SDLK_DOWN == e.key.keysym.sym)
                        {
                            if (snake.getHeadDirection() != up && !directionSet)
                            {
                                directionSet = true;
                                snake.setHeadDirection(down);
                            };
                        }
                        if (SDLK_UP == e.key.keysym.sym)
                        {
                            if (snake.getHeadDirection() != down && !directionSet)
                            {
                                directionSet = true;
                                snake.setHeadDirection(up);
                            };
                        }
                        if (SDLK_LEFT == e.key.keysym.sym)
                        {
                            if (snake.getHeadDirection() != right && !directionSet)
                            {
                                directionSet = true;
                                snake.setHeadDirection(left);
                            };
                        }
                        if (SDLK_RIGHT == e.key.keysym.sym)
                        {
                            if (snake.getHeadDirection() != left && !directionSet)
                            {
                                directionSet = true;
                                snake.setHeadDirection(right);
                            };
                        }
                    }
                }

                //Move snake
                if (deltaTime > .1)
                {
                    directionSet = false;
                    if (snake.move())
                    {
                        // printf("%d, %d", snake.getHeadX(), snake.getHeadY());
                        quit = true;
                    }
                }
                //Render Snake
                snake.draw(gScreenSurface);

                // SDL_BlitSurface(gPNGSurface, NULL, gScreenSurface, &r);

                //Update the surface
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}