#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <stdio.h>
#include "makeTexture.h"
#include "makeRect.h"
#include "makeText.h"
#define enemy_lines 10
#define enemy_columns 5
#define enemy_width 32
#define enemy_height 16
#define number_bullets 50
#define enemy_speed_constant 2
#define number_shields 4


typedef struct Game_entity_s
{
    int life;
    int is_right;
    int position_in_array;

    bool is_shooting;
    bool can_shoot;
    SDL_Texture * my_texture;
    SDL_Rect my_Hitbox;
    SDL_Rect textureRect;
}Game_entity_t;

typedef struct bullet_entity_s
{
    int direction;
    bool player_shoot;
    Game_entity_t entity;


}bullet_entity_t;


typedef struct Enemy_array_s
{   
    int active_cases;
    int enemy_speed;
    int active_enemies;
    int direction;
    Game_entity_t entity[enemy_lines * enemy_columns];
}Enemy_array_t;


typedef struct Game_entity_bullet_s
{
    int active_cases;

    bullet_entity_t bullets[number_bullets];
}Game_entity_bullet_t;


typedef struct Game_hud_s{

    bool gameState[4];

	char playerLivesString[11];
    SDL_Texture *playerLivesTexture;
	SDL_Rect playerLivesRect;

    char scoreString[100];
    SDL_Texture *scoreTexture;
    SDL_Rect scoreRect;

    SDL_Texture *keyBindingsTexture;
    SDL_Rect keyBindingsRect;

}Game_hud_t;

typedef struct Shield_array_s
{
    int active_cases;
    Game_entity_t entity[number_shields];
    
}Shield_array_t;

typedef struct Game_state_s
{   
    bool mainMenu;
    bool gamePaused;
    bool gameOver;
    bool gameStart;
    bool gameQuit;
}Game_state_t;

typedef struct Game_s
{
    int score;
    int game_new;
    Game_state_t gameStates;
    Game_hud_t hud;
    Game_entity_t player;
    Enemy_array_t enemies;
    Game_entity_bullet_t bullets;
    Shield_array_t shields;
    //Game_entity_t shields[];

}Game_t;

void MainGame(SDL_Renderer* renderer, Game_t* game_data);
void MainGameLoop(SDL_Renderer* renderer, Game_t* game_data);
void MainGameInput(Game_t* game_data);
void move(Game_t* game_data, bool is_right);
void destroy_bullet(Game_t* game_data,int index);
void destroy_shield(Game_t* game_data,int index);
void destroy_enemy(SDL_Renderer* renderer, Game_t* game_data,int index);
void create_bullet(Game_t* game_data, int direction, int x, int y, bool who_shoots);
int distance_to_player(Game_t* game_data,int bullet);
int distance_to_shield(Game_t* game_data,int bullet, int shield);
int distance_to_enemy(Game_t* game_data,int bullet, int enemy);
Uint32 clear_Texture(Uint32 interval, void* texture);
Uint32 can_shoot(Uint32 interval, void* timer_to_shoot);
int distance_to_bullet(Game_t* game_data,int bullet, int bullet2);
void enemy_speed(Game_t* game_data, int enemy);
int distance_to_player_enemy(Game_t* game_data,int enemy);
void player_enemy_initialise1(SDL_Renderer* renderer, Game_t* game_data);
void player_enemy_initialise2(SDL_Renderer* renderer, Game_t* game_data);
void bullet_initalise(SDL_Renderer* renderer, Game_t* game_data);
void the_hud(SDL_Renderer* renderer, Game_t* game_data);
void player_enemy_speed(SDL_Renderer* renderer, Game_t* game_data);
void destroy_enemies(SDL_Renderer* renderer, Game_t* game_data, int i);
void player_shields(SDL_Renderer* renderer, Game_t* game_data, int i);
void collisions1(SDL_Renderer* renderer, Game_t* game_data);
void collisions2(SDL_Renderer* renderer, Game_t* game_data);
void renderCopy1(SDL_Renderer* renderer, Game_t* game_data);
void renderCopy2(SDL_Renderer* renderer, Game_t* game_data);