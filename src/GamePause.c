#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "GamePause.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define FONT "assets/spaceinvader.ttf"

void GamePause(SDL_Renderer* renderer, Game_t* game_data)
{
    int textColor[] = {0, 255, 0, 255};
	SDL_Texture *pausedTexture = makeText("PAUSED", FONT, 24, textColor, renderer);
	SDL_Rect pausedRect = makeRect(200, 200, 400, 70);

    int textColor2[] = {255, 255, 255, 255};
    SDL_Texture *psdTxtrePrsKy = makeText("Press any key to continue or ESC to leave", FONT, 24, textColor2, renderer);
	SDL_Rect psdTxtrePrsKyRect = makeRect(185, 400, 430, 40);
    GamePauseLoop(renderer, game_data, pausedTexture, pausedRect, psdTxtrePrsKy, psdTxtrePrsKyRect);
}

void GamePauseLoop(SDL_Renderer* renderer, Game_t* game_data, SDL_Texture *pausedTexture, SDL_Rect pausedRect, SDL_Texture *psdTxtrePrsKy, SDL_Rect psdTxtrePrsKyRect)
{
    bool loopEnds = true;
    int psdTxtrePrsKyTck = 100;
    while(true)
    {
        loopEnds = GamePauseInput(game_data);
        
        if (loopEnds == false)
            break;

        SDL_RenderClear(renderer);
        psdTxtrePrsKyTck--;
        if (psdTxtrePrsKyTck <= 0)
            psdTxtrePrsKyTck = 100;

        if (psdTxtrePrsKyTck > 40)
            SDL_RenderCopy(renderer, psdTxtrePrsKy, NULL, &psdTxtrePrsKyRect);

        SDL_RenderCopy(renderer, pausedTexture, NULL, &pausedRect);
		SDL_RenderPresent(renderer);
    }
}

bool GamePauseInput(Game_t* game_data)
{
    SDL_Event pauseEvent;
	while (SDL_PollEvent(&pauseEvent))
	{
        if (pauseEvent.type == SDL_KEYDOWN && pauseEvent.key.keysym.sym != SDLK_ESCAPE)
        {
            return false;
        }
		if (pauseEvent.type == SDL_KEYDOWN && pauseEvent.key.keysym.sym == SDLK_ESCAPE)
        {

            game_data->gameStates.gameQuit = true;
            return false;
        }

    }
    return true;
}
