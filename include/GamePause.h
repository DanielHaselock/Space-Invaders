#pragma once
#include "MainGame3.h"
#include "makeText.h"
#include "makeRect.h"

void GamePause(SDL_Renderer* renderer, Game_t* game_data);
void GamePauseLoop(SDL_Renderer* renderer, Game_t* game_data, SDL_Texture *pausedTexture, SDL_Rect pausedRect, SDL_Texture *psdTxtrePrsKy, SDL_Rect psdTxtrePrsKyRect);
bool GamePauseInput(Game_t* game_data);