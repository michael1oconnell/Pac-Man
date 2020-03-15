#include "main.h"
#include "status.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <stdio.h>
#include <stdlib.h>

#define ROW_SIZE 15
#define COL_SIZE 31
#define PIXEL_CONST 25
#define PAC_PIXEL_CONST 5


/* Initial state of the game is displayed using characters.
   Will continue to change as game goes on.
   The game map keeps track of the locations of
   (1) boundaries ('%') - ,
   (2) food ('.'),
   (3) energy pellets ('o') and
   (4) ghosts ('R', 'Y', 'P', 'B')

   gameMap keeps track of all game object's coordinates and where
   objects are rendered is according to their relative position on
   the gameMap.
*/
char gameMap[ROW_SIZE][COL_SIZE] =
                        {{"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"},
                        {"%.....%.................%.....%"},
                        {"%o%%%.%.%%%.%%%%%%%.%%%.%.%%%o%"},
                        {"%.%.....%......%......%.....%.%"},
                        {"%...%%%.%.%%%%.%.%%%%.%.%%%...%"},
                        {"%%%.%...%.%.........%.%...%.%%%"},
                        {"%...%.%%%.%.%%% %%%.%.%%%.%...%"},
                        {"%.%%%.......%RY PB%.......%%%.%"},
                        {"%...%.%%%.%.%%%%%%%.%.%%%.%...%"},
                        {"%%%.%...%.%.........%.%...%.%%%"},
                        {"%...%%%.%.%%%%.%.%%%%.%.%%%...%"},
                        {"%.%.....%......%......%.....%.%"},
                        {"%o%%%.%.%%%.%%%%%%%.%%%.%.%%%o%"},
                        {"%.....%........C........%.....%"},
                        {"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"}};

void loadGame(Gamestate* game)
{
    /* Pacman images */
    SDL_Surface* pacmanSurface = NULL; // source pixels in memory used to create texture
    SDL_Surface* pacmanUpSurface = NULL;
    SDL_Surface* pacmanDownSurface = NULL;
    SDL_Surface* pacmanLeftSurface = NULL;
    SDL_Surface* pacmanRightSurface = NULL;

    /* Maze images */
    SDL_Surface* foodSurface = NULL;

    /* Ghost images */
    SDL_Surface* redGhostSurface = NULL;
    SDL_Surface* yellowGhostSurface = NULL;
    SDL_Surface* pinkGhostSurface = NULL;
    SDL_Surface* blueGhostSurface = NULL;

    /* Special Ghost images */
    SDL_Surface* blinkGhostSurface = NULL;

    // loading pacman
    pacmanSurface = IMG_Load("pacman_closed.png");
    if(pacmanSurface == NULL)
    {
        printf("%s/n/n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    pacmanLeftSurface = IMG_Load("pacmanLeft.png");
    if(pacmanLeftSurface == NULL)
    {
        printf("%s/n/n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    pacmanRightSurface = IMG_Load("pacmanRight.png");
    if(pacmanRightSurface == NULL)
    {
        printf("%s/n/n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    pacmanUpSurface = IMG_Load("pacmanUp.png");
    if(pacmanUpSurface == NULL)
    {
        printf("%s/n/n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    pacmanDownSurface = IMG_Load("pacmanDown.png");
    if(pacmanDownSurface == NULL)
    {
        printf("%s/n/n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    foodSurface = IMG_Load("food.png");
    if(foodSurface == NULL)
    {
        printf("%s/n/n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    // loading ghosts
    redGhostSurface = IMG_Load("redGhost.png");
    if(redGhostSurface == NULL)
    {
        printf("%s/n/n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    pinkGhostSurface = IMG_Load("pinkGhost.png");
    if(pinkGhostSurface == NULL)
    {
        printf("%s/n/n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    yellowGhostSurface = IMG_Load("yellowGhost.png");
    if(yellowGhostSurface == NULL)
    {
        printf("%s/n/n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    blueGhostSurface = IMG_Load("blueGhost.png");
    if(blueGhostSurface == NULL)
    {
        printf("%s/n/n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    // loading special ghosts
    blinkGhostSurface = IMG_Load("blinkGhost.png");
    if(blinkGhostSurface == NULL)
    {
        printf("%s/n/n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    // pacman textures
    game->pacman_t[0] = SDL_CreateTextureFromSurface(game->renderer, pacmanSurface);
    game->pacman_t[1] = SDL_CreateTextureFromSurface(game->renderer, pacmanLeftSurface);
    game->pacman_t[2] = SDL_CreateTextureFromSurface(game->renderer, pacmanRightSurface);
    game->pacman_t[3] = SDL_CreateTextureFromSurface(game->renderer, pacmanUpSurface);
    game->pacman_t[4] = SDL_CreateTextureFromSurface(game->renderer, pacmanDownSurface);

    // maze textures
    game->food_t = SDL_CreateTextureFromSurface(game->renderer, foodSurface);

    // ghost textures
    game->ghost_t[0] = SDL_CreateTextureFromSurface(game->renderer, redGhostSurface);
    game->ghost_t[1] = SDL_CreateTextureFromSurface(game->renderer, yellowGhostSurface);
    game->ghost_t[2] = SDL_CreateTextureFromSurface(game->renderer, pinkGhostSurface);
    game->ghost_t[3] = SDL_CreateTextureFromSurface(game->renderer, blueGhostSurface);
    game->ghost_t[4] = SDL_CreateTextureFromSurface(game->renderer, blinkGhostSurface);

    /* once texture has been created, we don't need original surface, this frees memory */
    //pacman
    SDL_FreeSurface(pacmanSurface);
    SDL_FreeSurface(pacmanLeftSurface);
    SDL_FreeSurface(pacmanRightSurface);
    SDL_FreeSurface(pacmanUpSurface);
    SDL_FreeSurface(pacmanDownSurface);

    // maze
    SDL_FreeSurface(foodSurface);

    // ghosts
    SDL_FreeSurface(redGhostSurface);
    SDL_FreeSurface(yellowGhostSurface);
    SDL_FreeSurface(pinkGhostSurface);
    SDL_FreeSurface(blueGhostSurface);
    SDL_FreeSurface(blinkGhostSurface);

    // Load Fonts
    game->font = TTF_OpenFont("crackman.ttf", 36);
    if(game->font == NULL)
    {
        printf("%s\n\n", TTF_GetError());
        SDL_Quit();
        exit(1);
    }

    // fonts surface/ textures
    game->scoreLabel = NULL;
    game->livesLabel = NULL;
    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface* fontSurface = TTF_RenderText_Blended(game->font, "Score: ", white);
    SDL_Surface* livesSurface = TTF_RenderText_Blended(game->font, "Lives: ", white);
    game->scoreLabel = SDL_CreateTextureFromSurface(game->renderer, fontSurface);
    game->livesLabel = SDL_CreateTextureFromSurface(game->renderer, livesSurface);
    game->scoreLabelW = fontSurface->w;
    game->scoreLabelH = fontSurface->h;
    game->livesLabelW = livesSurface->w;
    game->livesLabelH = livesSurface->h;
    SDL_FreeSurface(fontSurface);
    SDL_FreeSurface(livesSurface);

    // initial animation frame for pacman
    game->man.animation_frame = 0; // closed mouth

    // initialize game clock
    game->time = 0;

    game->statusState = STATUS_STATE_LIVES;
}


/* Handles event processing, returns whether event loop should be over or not (done) */
int processEvents(SDL_Window* window, Gamestate* game)
{
    // amount pacman moves by
    int moveAmt = 1;

    // whether objects have collided
    unsigned int collide;

    int done = 0;
    // add time
    game->time++;

    if(game->time > 120)
    {
        shutdown_status_lives(game);
    }

    if(game->statusState == STATUS_STATE_GAME) // only do if game is currently being played (i.e. not gameover or start)
    {
        SDL_Event event; //union that contains structures for different events

        // check for events
        while(SDL_PollEvent(&event)) // will fill event structure with next event form the queue
        {
            switch(event.type)
            {
                case SDL_WINDOWEVENT_CLOSE:
                {
                    if(window)
                    {
                        SDL_DestroyWindow(window);
                        window = NULL;
                        done = 1;
                    }
                }
                break;
                case SDL_KEYDOWN: // any key pressed
                {
                    switch(event.key.keysym.sym) //allows you to get key by enum value
                    {
                        case SDLK_ESCAPE:
                            done = 1;
                            break;
                        /* The following keep track of which arrow key was pressed by user */
                        case SDLK_LEFT:
                            game->man.motionState = 0;
                            break;
                        case SDLK_RIGHT:
                            game->man.motionState = 1;
                            break;
                        case SDLK_UP:
                            game->man.motionState = 2;
                            break;
                        case SDLK_DOWN:
                            game->man.motionState = 3;
                            break;
                        // not moving
                        default:
                            game->man.animation_frame = 0;
                    }

                }
                break;
                // user pressed 'X' in upper right corner
                case SDL_QUIT:
                    // quit out of the game
                    done = 1;
                    break;
            }
        }

        // shifts pacman's mouth from being open and closed
        // shuffle between whatever frame animation frame pacman is on and closed
        // for more dynamic movement
        if(game->time % 5 == 0) // every 5 frames
        {
            if(game->man.animation_frame != 0) // if not currently closed
            {
                game->man.animation_frame = 0;
            }
        }

        // controls pacman's speed
        unsigned int delayMoveConst = 12;

        /*
        The following is pacman's movement processing.
        The switch statement above keeps track of which arrow key was pressed.
        The correct arrow key is stored in man's (struct) motionState.
        The time % delayMoveConst allows pacman to be moved once per delayMoveConst number of frames.
        This allows pacman to continue moving after the user has let up on the arrow key.
        Pacman will stop if it hits a wall.
        Pacman will change direction if the user interrupts its movement with another arrow key press.
        */

        // move left
        if(game->man.motionState == 0 && game->time % delayMoveConst == 0)
        {
            do {
                game->man.animation_frame = 1;
                gameMap[game->man.y][game->man.x] = ' ';
                game->man.x = game->man.x - 1;
                collide = collisionDetect(game);

            } while(!SDL_KEYDOWN && !collide);

        }
        // move right
        else if(game->man.motionState == 1 && game->time % delayMoveConst == 0)
        {
            do {
                game->man.animation_frame = 2;
                gameMap[game->man.y][game->man.x] = ' ';
                game->man.x = game->man.x + 1;
                game->man.motionState = 1;
                collide = collisionDetect(game);

            } while(!SDL_KEYDOWN && !collide);
        }
        // move up
        else if(game->man.motionState == 2 && game->time % delayMoveConst == 0)
        {
            do {
                game->man.animation_frame = 3;
                gameMap[game->man.y][game->man.x] = ' ';
                game->man.y = game->man.y - 1;
                collide = collisionDetect(game);

            } while(!SDL_KEYDOWN && !collide);

        }
        // move down
        else if(game->man.motionState == 3 && game->time % delayMoveConst == 0)
        {
            do {
                game->man.animation_frame = 4;
                gameMap[game->man.y][game->man.x] = ' ';
                game->man.y = game->man.y + 1;
                collide = collisionDetect(game);

            } while(!SDL_KEYDOWN && !collide);
        }

        // update the map position
        gameMap[game->man.y][game->man.x] = 'C';
    }

    return done;

}

/* iterate through all your objects see if you're intersecting against rectangles */
// Note: It's good practice to only detect in situations where it's actually possible
// e.g. you can't collide with a wall to the left or right-hand side if you aren't moving left/right
unsigned int collisionDetect(Gamestate* game)
{
    int pacX = game->man.x;
    int pacY = game->man.y;
    int wallX, wallY;
    int pacWidth, wallWidth;
    int pacHeight, wallHeight;
    int motionState = game->man.motionState;

    wallWidth = wallHeight = pacWidth = pacHeight = PIXEL_CONST;

    // collision detection with walls
    for(int i = 0; i < WALL_AMOUNT; i++)
    {
        wallX = game->walls[i].x;
        wallY = game->walls[i].y;

        // collision detected
        if(game->man.x == wallX && game->man.y == wallY)
        {
            // collision on left-hand side
            if(motionState == 0)
            {
                // move man to the right
                game->man.x += 1;
            }
            // collision on right-hand side
            else if(motionState == 1)
            {
                // move man to the left
                game->man.x -= 1;
            }
            // collision on the top
            else if(motionState == 2)
            {
                game->man.y += 1;
            }
            // collision on the bottom
            else if(motionState == 3)
            {
                game->man.y -= 1;
            }

            // man is no longer moving
            game->man.animation_frame = 0;

            return 1;
        }
    }

    return 0;

}


/* Renders images by order (e.g. first image eclipses second) and displays */
void doRender(SDL_Renderer* renderer, Gamestate* game)
{
    /* Draw something on window */

    // Set color used for drawing operations
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // 0,0,0,0 is black

    // Clear the screen to display the Render color
    SDL_RenderClear(renderer);

    // to center food and energy pellets
    int foodOffset = 10;
    int energyOffset = 7;

    // counts for keeping track of game objects
    unsigned int wallCount = 0;
    unsigned int foodCount = 0;
    unsigned int energyCount = 0;

    // render game objects
    for(int i = 0; i < ROW_SIZE; i++)
    {
        for(int j = 0; j < COL_SIZE; j++)
        {
            // render a boundary
            if(gameMap[i][j] == '%')
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0); // dark blue
                SDL_Rect boundRect = {j * PIXEL_CONST, i * PIXEL_CONST, PIXEL_CONST, PIXEL_CONST};
                SDL_RenderFillRect(renderer, &boundRect);


                // update boundary coordinates
                game->walls[wallCount].x = j;
                game->walls[wallCount].y = i;

                wallCount++;

            }
            // render food
            else if(gameMap[i][j] == '.')
            {
                SDL_Rect foodRect = {j * PIXEL_CONST + foodOffset, i * PIXEL_CONST + foodOffset, PIXEL_CONST / 4, PIXEL_CONST / 4};
                SDL_RenderCopy(renderer, game->food_t, NULL, &foodRect);

                // updating food's coordinates
                game->food[foodCount].x = j;
                game->food[foodCount].y = i;

                foodCount++;

            }
            // render energy pellets
            else if(gameMap[i][j] == 'o')
            {
                SDL_Rect energyRect = {j * PIXEL_CONST + energyOffset, i * PIXEL_CONST + energyOffset, PIXEL_CONST / 2, PIXEL_CONST / 2};
                SDL_RenderCopy(renderer, game->food_t, NULL, &energyRect);

                // updating energy coordinates
                game->energy[energyCount].x = j;
                game->energy[energyCount].y = i;

                energyCount++;
            }
            // red ghost
            else if(gameMap[i][j] == 'R')
            {
                SDL_Rect redGhostRect = {j * PIXEL_CONST, i * PIXEL_CONST, PIXEL_CONST, PIXEL_CONST};
                SDL_RenderCopy(renderer, game->ghost_t[0], NULL, &redGhostRect);
            }
            // yellow ghost
            else if(gameMap[i][j] == 'Y')
            {
                SDL_Rect yellowGhostRect = {j * PIXEL_CONST, i * PIXEL_CONST, PIXEL_CONST, PIXEL_CONST};
                SDL_RenderCopy(renderer, game->ghost_t[1], NULL, &yellowGhostRect);
            }
            // pink ghost
            else if(gameMap[i][j] == 'P')
            {
                SDL_Rect pinkGhostRect = {j * PIXEL_CONST, i * PIXEL_CONST, PIXEL_CONST, PIXEL_CONST};
                SDL_RenderCopy(renderer, game->ghost_t[2], NULL, &pinkGhostRect);
            }
            // blue ghost
            else if(gameMap[i][j] == 'B')
            {
                SDL_Rect blueGhostRect = {j * PIXEL_CONST, i * PIXEL_CONST, PIXEL_CONST, PIXEL_CONST};
                SDL_RenderCopy(renderer, game->ghost_t[3], NULL, &blueGhostRect);
            }
            // pacman
            else if(gameMap[i][j] == 'C')
            {
                game->man.x = j;
                game->man.y = i;
            }

        }
    }
    SDL_Rect pacmanRect = {game->man.x * PIXEL_CONST, game->man.y * PIXEL_CONST, PIXEL_CONST, PIXEL_CONST};
    SDL_RenderCopy(renderer, game->pacman_t[game->man.animation_frame], NULL, &pacmanRect);
    // SDL_RenderCopyEx(renderer, game->pacman[game->man.animation_frame], NULL, &pacmanRect, 0, NULL, )
    // You can also use RenderCopyEx to flip the image, rather than have multiple images

    // Rendering Score and Lives (bottom of the screen)
    SDL_Rect textRect = {PIXEL_CONST, PIXEL_CONST * 15, game->scoreLabelW, game->scoreLabelH};
    SDL_Rect livesRect = {PIXEL_CONST * 18, PIXEL_CONST * 15, game->livesLabelW, game->livesLabelH};
    SDL_RenderCopy(renderer, game->scoreLabel, NULL, &textRect);
    SDL_RenderCopy(renderer, game->livesLabel, NULL, &livesRect);

    /* End of drawing */

    /* Displaying Drawing */
    SDL_RenderPresent(renderer);
}

/* Helper method for debugging */
void printMap()
{
    for(int i = 0; i < ROW_SIZE; i++)
    {
        for(int j = 0; j < COL_SIZE; j++)
        {
            fprintf(stdout, '%c /n', gameMap[i][j]);
        }
        fprintf(stdout, "/n");
    }
}

int main(int argc, char* argv[])
{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init(); // initialize font system

    Gamestate game;

    // extends the window to put a score and lives at the bottom
    unsigned int bottomScreen = 1.5 * PIXEL_CONST;


    // Application window with the following settings
    window = SDL_CreateWindow("Pac-Man",                                // Window title
                              SDL_WINDOWPOS_UNDEFINED,                  // Initial x position
                              SDL_WINDOWPOS_UNDEFINED,                  // Initial y position
                              COL_SIZE * PIXEL_CONST,                   // width, in pixels
                              (ROW_SIZE * PIXEL_CONST) + bottomScreen,  // height, in pixels
                              0                                         // flags
                              );

    // -1 is the index of the rendering driver to initialize (the first one supporting the requested flags)
    // SDL_RENDERER_ACCELERATED uses hardware acceleration
    // SDL_RENDERER_VSYNC allows renderer to present with respect to the refresh rate
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    game.renderer = renderer;

    loadGame(&game);

    /* Event loop */
    int done = 0;

    while(!done)
    {
        // handle events
        done = processEvents(window, &game);
        printf("%d %d \n\n", game.man.x, game.man.y);

        // correct positions if collision detected
        //collisionDetect(&game);

        // render images
        doRender(game.renderer, &game);
    }

    /* Clean up/close window,renderer, and texture */
    SDL_DestroyTexture(game.pacman_t[0]);
    SDL_DestroyTexture(game.pacman_t[1]);
    SDL_DestroyTexture(game.pacman_t[2]);
    SDL_DestroyTexture(game.pacman_t[3]);
    SDL_DestroyTexture(game.pacman_t[4]);
    SDL_DestroyTexture(game.ghost_t[0]);
    SDL_DestroyTexture(game.ghost_t[1]);
    SDL_DestroyTexture(game.ghost_t[2]);
    SDL_DestroyTexture(game.ghost_t[3]);
    SDL_DestroyTexture(game.ghost_t[4]);
    SDL_DestroyTexture(game.food_t);
    SDL_DestroyTexture(game.scoreLabel);
    SDL_DestroyTexture(game.livesLabel);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    TTF_CloseFont(game.font);

    /* Quit SDL */
    SDL_Quit();
    TTF_Quit();

    return 0;
}
