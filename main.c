//Using SDL, SDL_image and standard IO
#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

typedef struct {
    // Images
    SDL_Texture* pacman;
} Gamestate;

void do_render(SDL_Window* window, SDL_Renderer* renderer) {

    // setting draw color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // clear the screen (to black)
    SDL_RenderClear(renderer);

    //We are done drawing, show to the screen what we've drawn
    SDL_RenderPresent(renderer);
}

int processEvents(SDL_Window* window) {

    SDL_Event event;
    int done = 0;

    // if there is an event, 1 will be returned and the event will be removed from the queue and stored in event variable
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            // Window was closed
            case SDL_WINDOWEVENT_CLOSE:
                // Window object does exist
                if(window)
                {
                    SDL_DestroyWindow(window);
                    window = NULL;
                    done = 1;
                }
            break;
            // SDL quit unexpectedly
            case SDL_QUIT:
                done = 1;
            break;
        }
    }
    return done;
}

int main( int argc, char* argv[] )
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* pacman_surface = NULL;

    // Initializes entire SDL system. Argument passed is which SDL subsystem we want to initialize.
    SDL_Init(SDL_INIT_EVERYTHING);

    // Create an application window
    window = SDL_CreateWindow("Pac-Man",
                            SDL_WINDOWPOS_UNDEFINED, // initial x position
                            SDL_WINDOWPOS_UNDEFINED, // initial y position
                            SCREEN_WIDTH, // width, in pixels
                            SCREEN_HEIGHT,// height, in pixels
                            0 // flags
                            );

    // renderer accelerated flag allows us to use graphics hardware, and SDL_PRESENTVSYNC flag
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // load images and create rendering textures form them
    pacman_surface = IMG_Load("pacman.png");

    // failed to load image
    if(pacman_surface == NULL)
    {
        printf(IMG_GetError());
        SDL_Quit();
        return 1;
    }

    int done = 0;

    // Event loop
    while(done == 0) {
        // check for events
        done = processEvents(window);

        // render display
        do_render(window, renderer);

        // don't burn up CPU
        SDL_Delay(10);
    }

    // Destroy Window
    SDL_DestroyWindow(window);
    // Destroy Renderer
    SDL_DestroyRenderer(renderer);

    SDL_Quit();
    return 0;
}
