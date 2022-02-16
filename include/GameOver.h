#pragma once
#include "MainGame3.h"
#include "makeText.h"
#include "makeRect.h"

bool GameOver(SDL_Renderer* renderer, Game_t* game_data);
void GameOverLoop(SDL_Renderer* renderer, Game_t* game_data, SDL_Texture *gameOverTexture, SDL_Rect gameOverRect, SDL_Texture *gameOverHead, SDL_Rect gameOverHeadRect, SDL_Texture *gameOverTxt, SDL_Rect gameOverTxtRect);
bool GameOverInput(Game_t* game_data);
