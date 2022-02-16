#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "makeRect.h"

SDL_Rect makeRect(int X, int Y, int W, int H)
{
    SDL_Rect thisRect;
    thisRect.x = X;
    thisRect.y = Y;
    thisRect.w = W;
    thisRect.h = H;

    return thisRect;
}
