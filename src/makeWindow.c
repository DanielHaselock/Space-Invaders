#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "makeWindow.h"

SDL_Window* makeWindow(const char *windowTitle, const int W, const int H)
{
	SDL_Window* thisWindow = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_SHOWN);

	if (thisWindow == NULL)
	{
		SDL_Quit();
		SDL_DestroyWindow(thisWindow);
		printf("%s", "Window could not compile.");
		return 0;
	}

    return thisWindow;
}
