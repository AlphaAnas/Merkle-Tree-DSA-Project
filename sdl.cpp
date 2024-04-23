// Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h> // Include SDL_image header
#include <stdio.h>
#include <iostream>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The surface contained by the window
SDL_Surface *gScreenSurface = NULL;

// The image we will load and show on the screen
SDL_Surface *gMerkleTree = NULL;

bool init()
{
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Create window
        gWindow = SDL_CreateWindow("Merkle Tree", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return success;
}

bool loadMedia()
{
    // Loading success flag
    bool success = true;

    // Load splash image
    gMerkleTree = IMG_Load(".\\images\\bg.jpg"); // Load JPG image with SDL_image
    if (gMerkleTree == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", ".\\images\\bg.jpg", SDL_GetError());
        success = false;
    }

    return success;
}

void close()
{
    // Deallocate surface
    SDL_FreeSurface(gMerkleTree);
    gMerkleTree = NULL;

    // Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    // Quit SDL subsystems
    SDL_Quit();
}
void keep_running()
{
    // Hack to get window to stay up
    SDL_Event e;
    bool quit = false;
    // std::cin.get(); // take input from the user
    while (quit == false)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = true;
        }
    }
}

int main(int argc, char *args[])
{
<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
    // Start up SDL and create window
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        // Load media
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            main_merkle();
            // Apply the image
            SDL_BlitSurface(gMerkleTree, NULL, gScreenSurface, NULL);

            // Update the surface
            SDL_UpdateWindowSurface(gWindow);

<<<<<<< Updated upstream
            // Hack to get window to stay up
            SDL_Event e;
            bool quit = false;
            while (quit == false)
            {
                while (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_QUIT)
                        quit = true;
                }
            }
=======
            keep_running();
>>>>>>> Stashed changes
        }
    }

    // Free resources and close SDL
    close();

    return 0;
}