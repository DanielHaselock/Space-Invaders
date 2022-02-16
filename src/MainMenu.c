#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "MainMenu.h"
#include <math.h>
#define MAIN_TITLE "assets/title.bmp"
#define FONT "assets/spaceinvader.ttf"
#define WIDTH 800
#define HEIGHT 600


void MainMenu(SDL_Renderer* renderer, Game_t* game_data)
{
	//TITLE
	SDL_Texture *titleTexture = makeTexture(renderer, MAIN_TITLE);
	SDL_Rect titleRect = makeRect(0, 0, WIDTH, HEIGHT-100);

	//PRESS ANY KEY TO CONTINUE
	int textColor[] = {255, 255, 255, 255};
	SDL_Texture *prssAnyKyTexture = makeText("Press any key to continue", FONT, 24, textColor, renderer);
	SDL_Rect pressAnyKyRect = makeRect(200, 500, 400, 50);

	
	MainMenuLoop(renderer, titleTexture, titleRect, prssAnyKyTexture, pressAnyKyRect, game_data);

	SDL_DestroyTexture(prssAnyKyTexture);
    SDL_DestroyTexture(titleTexture);
}

void MainMenuLoop(SDL_Renderer* renderer, SDL_Texture* titleTexture, SDL_Rect titleRect, SDL_Texture* prssAnyKyTexture, SDL_Rect pressAnyKyRect, Game_t* game_data)
{
	bool loopEnds = false;
	while (loopEnds == false)
	{
		loopEnds = MainMenuInput(game_data);
		SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);
		SDL_RenderCopy(renderer, prssAnyKyTexture, NULL, &pressAnyKyRect);
		SDL_RenderPresent(renderer);
    }
}

bool MainMenuInput(Game_t* game_data)
{
	SDL_Event menuInput;
	while (SDL_PollEvent(&menuInput))
	{
		//QUIT GAME
		if (menuInput.type == SDL_KEYDOWN && menuInput.key.keysym.sym == SDLK_ESCAPE)
		{	

			game_data->gameStates.gameStart = false;
			game_data->gameStates.gameQuit = true;
			return true;
		}
		//START GAME
		if (menuInput.type == SDL_KEYDOWN && menuInput.key.keysym.sym != SDLK_ESCAPE)
		{
			//printf("%d\n", game_data->gameStates.gameStart);
			game_data->gameStates.gameStart = true;
			return true;
		}
	}
	return false;
}


