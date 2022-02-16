#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "makeText.h"

SDL_Texture* makeText(char *string, char *font, int fontSize, int color[], SDL_Renderer* renderer)
{
    TTF_Font* thisFont = TTF_OpenFont(font, fontSize);
    if (thisFont == NULL)
    {
        printf("%s \n", "Font could not load.");
        return NULL;
    }
    

    SDL_Color thisFontColor = {color[0], color[1], color[2], color[3]};
  
  


    SDL_Surface* thisMessageSurface = TTF_RenderText_Solid(thisFont, string, thisFontColor);
    if (thisMessageSurface == NULL)
    {
        printf("%s \n", "Message surface could not load.");
    }

    SDL_Texture* thisMessage = SDL_CreateTextureFromSurface(renderer, thisMessageSurface);
    SDL_FreeSurface(thisMessageSurface);
    TTF_CloseFont(thisFont);


    return thisMessage;
}
