#include <stdio.h>
#include "main.h"
#include "status.h"



void draw_status_lives(Gamestate* game)
{


}

/* Helper method for doRender()
   Updates the score label (bottom left corner) every render cycle
   to successfully display the gamescore as it's changing
   Does the prerequisite work in order to render a texture in doRender
   (creating a surface, then creating a texture)
*/
void updateScoreLabel(Gamestate* game)
{
    SDL_Color white = {255, 255, 255, 255};
    char scoreText[128] = "";
    sprintf(scoreText, "Score %u", game->gameScore);

    SDL_Surface* fontSurface = TTF_RenderText_Blended(game->font, scoreText, white);
    game->scoreLabel = SDL_CreateTextureFromSurface(game->renderer, fontSurface);
    SDL_FreeSurface(fontSurface);

}



// leaving status menu
void shutdown_status_lives(Gamestate* game)
{
    game->statusState = STATUS_STATE_GAME;

}

