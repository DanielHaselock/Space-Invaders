#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "makeTexture.h"

SDL_Texture *makeTexture(SDL_Renderer* renderer, char* path)
{
    return IMG_LoadTexture(renderer, path);
}



