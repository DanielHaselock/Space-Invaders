#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "makeRenderer.h"


SDL_Renderer* makeRenderer(SDL_Window* Window)
{
	SDL_Renderer* thisRenderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

	if (thisRenderer == NULL)
	{
	    SDL_DestroyRenderer(thisRenderer);
		SDL_Quit();
		printf("%s", "Renderer could not compile.");
		return 0;
	}

    return thisRenderer;
}
