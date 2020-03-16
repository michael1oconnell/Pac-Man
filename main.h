#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include "SDL.h"
#include "SDL_ttf.h" // for fonts
#include "SDL_image.h"

#define STATUS_STATE_LIVES 0
#define STATUS_STATE_GAME 1
#define STATUS_STATE_GAMEOVER 2

#define WALL_AMOUNT 239 // wall amount will not change
#define INIT_FOOD_AMOUNT 215


typedef struct
{
    int x, y;
    short life;
    char* name;

    unsigned int motionState; // 0,1,2,3 = left, right, up, down

    // frame that matches pacman's state. E.g. static mouth if standing still
    int animation_frame; // 0,1,2,3,4 = closed, left, right, up, down

} Man; // pacman

typedef struct
{
    int x, y;

} Ghost;

typedef struct
{
    int x, y;

} Wall;


typedef struct
{
    int x, y;

} Food;

typedef struct
{
    int x, y;

} EnergyPellet;

typedef struct
{
    /* players/characters */

    // ghosts
    Ghost redGhost;
    Ghost yellowGhost;
    Ghost pinkGhost;
    Ghost blueGhost;
    Ghost blinkGhost;

    // walls
    Wall walls[WALL_AMOUNT];

    // pacman
    Man man;

    // food
    Food food[215];

    // total amount of food
    unsigned int totalFood;

    // energy pellets
    EnergyPellet pellet[4];

    // amount of energy pellet
    unsigned int totalPellet;

    // score of the game
    unsigned int gameScore;

    // score increase if food pellet is eaten
    unsigned int foodScore;

    // score increase if energy pellet is eaten
    unsigned int pelletScore;

    // Images (texture is the main type for images in SDL)
    SDL_Renderer* renderer;
    SDL_Texture* pacman_t[5];
    SDL_Texture* ghost_t[5]; // red, yellow, pink, blue, blink respectively
    SDL_Texture* food_t;
    SDL_Texture* scoreLabel;
    SDL_Texture* livesLabel;

    // Fonts
    TTF_Font* font;

    // Font properties
    int labelWidth;
    int labelHeight;

    // Time
    int time;
    int statusState;

} Gamestate;

// function prototypes
int processEvents(SDL_Window* window, Gamestate* game);
unsigned int collisionDetect(Gamestate* game);
void doRender(SDL_Renderer* renderer, Gamestate* game);
void loadGame(Gamestate* game);

#endif // MAIN_H_INCLUDED
