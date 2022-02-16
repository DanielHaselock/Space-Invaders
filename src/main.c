#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>
#include <stdio.h>
#include "main.h"
#include <math.h>
#define WINDOW_TITLE "Space Invaders"
#define WIDTH 800
#define HEIGHT 600

int main()
{
	if (SDL_Init(SDL_INIT_VIDEO/* | SDL_INIT_AUDIO*/) < 0)
	{
		
		printf("%s", "SDL could not compile.");SDL_Quit();
		return EXIT_FAILURE;
	}
	TTF_Init();
	//Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	//Mix_Chunk *sound = "assets/title.wav";


	SDL_Window* Window = makeWindow(WINDOW_TITLE, WIDTH, HEIGHT);
	SDL_Renderer* Renderer = makeRenderer(Window);

	Game_t game;

	game.gameStates.gameOver = false;
	game.gameStates.gameStart = false;
	game.gameStates.gameQuit = false;
	game.gameStates.gamePaused = false;
	game.game_new = 0;

	while (game.gameStates.gameQuit == false)
	{
		if (game.game_new == 0)
			MainMenu(Renderer, &game);

		if (game.gameStates.gameStart == true)
		{
			printf("%s", "Game has started");
			MainGame(Renderer, &game);
		}
		if (game.gameStates.gameOver == true)
		{
			printf("%s", "Game over");
			GameOver(Renderer, &game);
		}
	}
	destroy_functions(Renderer, Window);
}

void destroy_functions(SDL_Renderer* renderer, SDL_Window* window)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);;
	TTF_Quit();
	SDL_Quit();
}



