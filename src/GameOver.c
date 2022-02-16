#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "GameOver.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define FONT "assets/spaceinvader.ttf"

bool GameOver(SDL_Renderer* renderer, Game_t* game_data)
{
    int textColor[] = {255, 0, 0, 255};
	SDL_Texture *gameOverTexture = makeText("GAME OVER", FONT, 24, textColor, renderer);
	SDL_Rect gameOverRect = makeRect(200, 200, 400, 70);

    SDL_Texture* gameOverHead = IMG_LoadTexture(renderer, "assets/gameover.bmp");
    SDL_Rect gameOverHeadRect = makeRect(240, 300, 300, 300);

    int textColor2[] = {255, 255, 255, 255};
    SDL_Texture *gameOverTxt = makeText("Press any key to try again or ESC to leave", FONT, 24, textColor2, renderer);
	SDL_Rect gameOverTxtRect = makeRect(25, 100, 750, 30);

    GameOverLoop(renderer, game_data, gameOverTexture, gameOverRect, gameOverHead, gameOverHeadRect, gameOverTxt, gameOverTxtRect);
}

void GameOverLoop(SDL_Renderer* renderer, Game_t* game_data, SDL_Texture *gameOverTexture, 
                  SDL_Rect gameOverRect, SDL_Texture *gameOverHead, SDL_Rect gameOverHeadRect, SDL_Texture *gameOverTxt, SDL_Rect gameOverTxtRect)
{

    bool loopEnds = true;
    int gameOvrHdTck = 100;
    while (true)
    {

        loopEnds = GameOverInput(game_data);
        if (loopEnds == false)
            break;
        
        SDL_RenderClear(renderer);
        gameOvrHdTck--;
        if (gameOvrHdTck <= 0)
            gameOvrHdTck = 100;

        if (gameOvrHdTck > 50)
            SDL_RenderCopy(renderer, gameOverHead, NULL, &gameOverHeadRect);

        SDL_RenderCopy(renderer, gameOverTxt, NULL, &gameOverTxtRect);

        SDL_RenderCopy(renderer, gameOverTexture, NULL, &gameOverRect);
		SDL_RenderPresent(renderer);
    }

    game_data->gameStates.gameOver = false;
}

bool GameOverInput(Game_t* game_data)
{
    SDL_Event gameOverEvent;
	while (SDL_PollEvent(&gameOverEvent))
    {
        if (gameOverEvent.type == SDL_KEYDOWN && gameOverEvent.key.keysym.sym == SDLK_ESCAPE)
        {
            game_data->gameStates.gameQuit = true;
            game_data->gameStates.gameStart = false;
            return false;
        }
        if (gameOverEvent.type == SDL_KEYDOWN && gameOverEvent.key.keysym.sym != SDLK_ESCAPE)
        {
            game_data->gameStates.gameQuit = false;
            game_data->gameStates.gameStart = true;
            return false;
        }
    }
    return true;
}
