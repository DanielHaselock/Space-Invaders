#pragma once
#include "MainGame3.h"

void MainMenu(SDL_Renderer* renderer, Game_t* game_data);
void MainMenuLoop(SDL_Renderer* renderer, SDL_Texture* titleTexture, SDL_Rect titleRect, SDL_Texture* prssAnyKyTexture, SDL_Rect pressAnyKyRect, Game_t* game_data);
bool MainMenuInput(Game_t* game_data);
