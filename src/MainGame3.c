#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "MainGame3.h"
#include "GamePause.h"
#define MAIN_TITLE "assets/title.bmp"
#define WIDTH 800
#define HEIGHT 600
#define FONT "assets/spaceinvader.ttf"
#define ENEMY_LINES 10
#define ENEMY_COLUMNS 5
#define ENEMY_WIDTH 32
#define ENEMY_HEIGHT 16
#define ENEMY_SPEED_CONSTANT 1
#include <stdio.h>
#include <math.h>
#include <stdlib.h>





void MainGame(SDL_Renderer* renderer, Game_t* game_data)
{

	player_enemy_initialise1(renderer, game_data);
	player_enemy_initialise2( renderer, game_data);
	bullet_initalise( renderer, game_data);


    MainGameLoop(renderer, game_data);


	SDL_DestroyTexture(game_data->player.my_texture);
	for(int i = 0; i< game_data->enemies.active_cases; i++)
	{
		SDL_DestroyTexture(game_data->enemies.entity[i].my_texture);
	}

}





void MainGameLoop(SDL_Renderer* renderer, Game_t* game_data)
{
	while (true)
	{
		MainGameInput(game_data);
		the_hud(renderer, game_data);
		player_enemy_speed(renderer, game_data);
		for(int i = 0; i< game_data->bullets.active_cases; i++)
		{
			bullet_entity_t * current_bullet = &game_data->bullets.bullets[i];
			SDL_Rect * bullet_hitbox = &game_data->bullets.bullets[i].entity.my_Hitbox;
			bullet_hitbox->y += 1 * current_bullet->direction;
			destroy_enemies(renderer,game_data, i);
			player_shields( renderer, game_data, i);
		}
		collisions1(renderer, game_data);
		collisions2(renderer, game_data);
		renderCopy1(renderer, game_data);
		for(int i = 0; i<game_data->shields.active_cases; i++)
		{
			SDL_RenderCopy(renderer, game_data->shields.entity[i].my_texture, NULL, &game_data->shields.entity[i].my_Hitbox);
		}
		if (game_data->gameStates.gamePaused == true)
		{
			printf("%s", "Test16");
			GamePause(renderer, game_data);
			game_data->gameStates.gamePaused = false;
		}
		if (game_data->gameStates.gameQuit == true)
			break;
		if(game_data->player.life < 1)
		{
			game_data->player.my_texture = IMG_LoadTexture(renderer, "./assets/playerdeath.bmp");
			game_data->game_new++;
			game_data->gameStates.gameOver = true;
			break;
		}
		if(game_data->enemies.active_enemies < 1)
		{
			game_data->game_new++;
			game_data->gameStates.mainMenu = false;
			game_data->gameStates.gameOver = false;
			break;
		}
		SDL_RenderPresent(renderer);
	}
}

void MainGameInput(Game_t* game_data)
{
	SDL_Event thisEvent;
	while (SDL_PollEvent(&thisEvent))
	{
		if (thisEvent.type == SDL_KEYDOWN && thisEvent.key.keysym.sym == SDLK_l)
		{
			game_data->player.life--;
		}
		if (thisEvent.type == SDL_KEYDOWN && thisEvent.key.keysym.sym == SDLK_y)
		{
			game_data->player.life++;
		}
		if (thisEvent.type == SDL_KEYDOWN && thisEvent.key.keysym.sym == SDLK_p)
		{
			game_data->gameStates.gamePaused = true;
		}
        if (thisEvent.type == SDL_KEYDOWN && thisEvent.key.keysym.sym == SDLK_d)
		{
			game_data->player.is_right = 1;
		}
		if (thisEvent.type == SDL_KEYUP && thisEvent.key.keysym.sym == SDLK_d)
		{
			game_data->player.is_right--;
		}
		if(thisEvent.type == SDL_KEYUP && thisEvent.key.keysym.sym == SDLK_a)
		{
			game_data->player.is_right++;
		}
        if (thisEvent.type == SDL_KEYDOWN && thisEvent.key.keysym.sym == SDLK_a)
		{
			game_data->player.is_right = -1;
	
		}
		if (thisEvent.type == SDL_KEYDOWN && thisEvent.key.keysym.sym == SDLK_SPACE)
		{
			
			if(game_data->player.can_shoot == true)
			{
				game_data->player.can_shoot = false;
				game_data->player.is_shooting = true;
				SDL_TimerID timerID2 = SDL_AddTimer(500, can_shoot, &game_data->player.can_shoot);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void move(Game_t* game_data, bool is_right)
{
	if(is_right == true)
	{	
		if(game_data->player.my_Hitbox.x > WIDTH - game_data->player.my_Hitbox.w)
		{
			game_data->player.my_Hitbox.x = WIDTH - game_data->player.my_Hitbox.w;
		}
        game_data->player.my_Hitbox.x += 5;

	} else
	{
		if(game_data->player.my_Hitbox.x < 0)
		{
			game_data->player.my_Hitbox.x = 0;
		}
        game_data->player.my_Hitbox.x -= 5;


	}


}





void destroy_bullet(Game_t* game_data,int index)
{
	game_data->bullets.bullets[index] = game_data->bullets.bullets[game_data->bullets.active_cases - 1];
	
	
	
	game_data->bullets.active_cases--;
	


}


void destroy_shield(Game_t* game_data,int index)
{
	game_data->shields.entity[index] = game_data->shields.entity[game_data->shields.active_cases - 1];
	
	
	
	game_data->shields.active_cases--;
	


}





void destroy_enemy(SDL_Renderer* renderer, Game_t* game_data,int index)
{

	game_data->enemies.entity[index].life = 0;
	game_data->enemies.entity[index].my_texture = IMG_LoadTexture(renderer, "./assets/aliendeath.bmp");

	

}

void create_bullet(Game_t* game_data, int direction, int x, int y, bool who_shoots)
{
	bullet_entity_t * new_bullet = &game_data->bullets.bullets[game_data->bullets.active_cases];
	new_bullet->entity.my_Hitbox.x = x;
	new_bullet->entity.my_Hitbox.y = y;
	new_bullet->direction = direction;
	game_data->bullets.active_cases = game_data->bullets.active_cases + 1;

	if(who_shoots == true)
	{
		new_bullet->player_shoot = true;
	}
	else if(who_shoots == false)
	{
		new_bullet->player_shoot = false;
	}

}



int distance_to_player(Game_t* game_data,int bullet)
{
	int a = game_data->player.my_Hitbox.x - game_data->bullets.bullets[bullet].entity.my_Hitbox.x;
	int b = game_data->player.my_Hitbox.y- game_data->bullets.bullets[bullet].entity.my_Hitbox.y;
	int c = a *a + b * b;
	int d = sqrt(c);

	return d;


}
int distance_to_player_enemy(Game_t* game_data,int enemy)
{
	int a = game_data->player.my_Hitbox.x - game_data->enemies.entity[enemy].my_Hitbox.x;
	int b = game_data->player.my_Hitbox.y- game_data->enemies.entity[enemy].my_Hitbox.y;
	int c = a *a + b * b;
	int d = sqrt(c);

	return d;


}


int distance_to_shield(Game_t* game_data,int bullet, int shield)
{
	int a = game_data->shields.entity[shield].my_Hitbox.x + 30- game_data->bullets.bullets[bullet].entity.my_Hitbox.x;
	int b = game_data->shields.entity[shield].my_Hitbox.y + 30- game_data->bullets.bullets[bullet].entity.my_Hitbox.y;
	int c = a *a + b * b;
	int d = sqrt(c);

	return d;


}


int distance_to_enemy(Game_t* game_data,int bullet, int enemy)
{
	int a = game_data->enemies.entity[enemy].my_Hitbox.x - game_data->bullets.bullets[bullet].entity.my_Hitbox.x;
	int b = game_data->enemies.entity[enemy].my_Hitbox.y - game_data->bullets.bullets[bullet].entity.my_Hitbox.y;
	int c = a *a + b * b;
	int d = sqrt(c);

	return d;


}

Uint32 clear_Texture(Uint32 interval, void* texture)
{
	SDL_Texture** my_texture =(SDL_Texture**)texture;
	*my_texture = NULL;
	return 0;

}

Uint32 can_shoot(Uint32 interval, void* timer_to_shoot)
{
	bool * can_shoot2 = (bool*)timer_to_shoot;
	*can_shoot2 = true;
	return 0;	
}


int distance_to_bullet(Game_t* game_data,int bullet, int bullet2)
{
	int a = game_data->bullets.bullets[bullet].entity.my_Hitbox.x - game_data->bullets.bullets[bullet2].entity.my_Hitbox.x;
	int b = game_data->bullets.bullets[bullet].entity.my_Hitbox.y - game_data->bullets.bullets[bullet2].entity.my_Hitbox.y;
	int c = a *a + b * b;
	int d = sqrt(c);

	return d;


}

void enemy_speed(Game_t* game_data, int enemy)
{
	if(game_data->enemies.entity[enemy].my_Hitbox.x > WIDTH - 50 && game_data->enemies.entity[enemy].life != 0)
	{
		game_data->enemies.direction = -1;
		for(int i = 0; i< game_data->enemies.active_cases; i++)
		{

			game_data->enemies.entity[i].my_Hitbox.x +=  enemy_speed_constant * game_data->enemies.direction + (game_data->game_new * game_data->enemies.direction);
			game_data->enemies.entity[i].my_Hitbox.y += 6; 


	

		}



	} else if(game_data->enemies.entity[enemy].my_Hitbox.x < 0 && game_data->enemies.entity[enemy].life != 0)
	{
		game_data->enemies.direction = 1;
		for(int i = 0; i< game_data->enemies.active_cases; i++)
		{
			game_data->enemies.entity[i].my_Hitbox.x +=  enemy_speed_constant * game_data->enemies.direction + (game_data->game_new * game_data->enemies.direction);
			game_data->enemies.entity[i].my_Hitbox.y += 6; 
		}

	} else 
	{
		game_data->enemies.entity[enemy].my_Hitbox.x +=   enemy_speed_constant * game_data->enemies.direction + (game_data->game_new * game_data->enemies.direction); 
	}
}
//CLEANUP FUNCTIONS

void player_enemy_initialise1(SDL_Renderer* renderer, Game_t* game_data)
{
	game_data->player.my_texture = makeTexture(renderer, "./assets/player.bmp");
	game_data->player.my_Hitbox = makeRect(375, 550, 32, 16);
	game_data->player.is_right = 0;

	game_data->player.life = 3;
	if(game_data->game_new == 0)
	{
		game_data->score = 0;
	}


}
void player_enemy_initialise2(SDL_Renderer* renderer, Game_t* game_data)
{
	SDL_Texture* enemy_texture = IMG_LoadTexture(renderer, "./assets/alien1.bmp");
	SDL_Texture* enemy_texture2 = IMG_LoadTexture(renderer, "./assets/alien2.bmp");
	SDL_Texture* enemy_texture3 = IMG_LoadTexture(renderer, "./assets/alien3.bmp");
	game_data->enemies.active_cases = enemy_lines * enemy_columns;
	game_data->enemies.active_enemies = game_data->enemies.active_cases;


	for(int i = 0; i <enemy_lines; i++)
	{
		for(int j = 0; j < enemy_columns; j++)
		{
			game_data->enemies.entity[i + j * enemy_lines].life = 1;
			if(j == 0)
			{
				game_data->enemies.entity[i + j * enemy_lines].my_texture = enemy_texture;
				game_data->enemies.entity[i + j * enemy_lines].position_in_array = 1;
			} else if (j == 1 || j == 2)
			{
				game_data->enemies.entity[i + j * enemy_lines].position_in_array = 2;
				game_data->enemies.entity[i + j * enemy_lines].my_texture = enemy_texture2;
			} else if (j == 3 || j == 4) {
				game_data->enemies.entity[i + j * enemy_lines].position_in_array = 3;
				game_data->enemies.entity[i + j * enemy_lines].my_texture = enemy_texture3;
			}

			game_data->enemies.entity[i + j * enemy_lines].textureRect.x = 0;
			game_data->enemies.entity[i + j * enemy_lines].textureRect.y = 0;
			game_data->enemies.entity[i + j * enemy_lines].textureRect.w = 48;
			game_data->enemies.entity[i + j * enemy_lines].textureRect.h = 18;
			game_data->enemies.entity[i + j * enemy_lines].textureRect.w /= 2;
			game_data->enemies.entity[i + j * ENEMY_LINES].my_Hitbox = makeRect(ENEMY_WIDTH * 1.5 * i, ENEMY_HEIGHT * j * 2.5, ENEMY_WIDTH, ENEMY_HEIGHT);
			game_data->enemies.direction = 1;
		}
	}

}

void bullet_initalise(SDL_Renderer* renderer, Game_t* game_data)
{
	for(int a = 0; a < number_bullets; a++)
	{
		game_data->bullets.bullets[a].entity.my_texture = makeTexture(renderer, "./assets/missile.bmp");
		game_data->bullets.bullets[a].entity.my_Hitbox = makeRect(100, 100, 8, 4);
		game_data->bullets.active_cases = 0;
	}
	game_data->hud.playerLivesRect = makeRect(585, 570, 200, 30);
	game_data->hud.scoreTexture = NULL;
	game_data->hud.playerLivesTexture = NULL;
	game_data->hud.scoreRect = makeRect(10, 570, 200, 30);
	game_data->player.is_shooting = false;
	game_data->player.can_shoot = true;
	//SHIELDS 
	int x = 80;
	for (int a = 0; a < number_shields; a++)
	{
		game_data->shields.entity[a].my_texture = makeTexture(renderer, "./assets/shield.bmp");
		game_data->shields.active_cases = 4;
		game_data->shields.entity[a].my_Hitbox = makeRect(x, 450, 60, 60);
		game_data->shields.entity[a].life = 5;
		x += 200;
	}

}

void the_hud(SDL_Renderer* renderer, Game_t* game_data)
{


	int textColor[] = {255, 255, 255, 255};


	sprintf(game_data->hud.playerLivesString, "Lives: %d", game_data->player.life);
	sprintf(game_data->hud.scoreString, "Score: %d", game_data->score*50);

	SDL_DestroyTexture(game_data->hud.playerLivesTexture);

	game_data->hud.playerLivesTexture = makeText(game_data->hud.playerLivesString, FONT, 24, textColor, renderer);



	SDL_DestroyTexture(game_data->hud.scoreTexture);
	game_data->hud.scoreTexture = makeText(game_data->hud.scoreString, FONT, 24, textColor, renderer);
		

		
}


void player_enemy_speed(SDL_Renderer* renderer, Game_t* game_data)
{
	if(game_data->player.is_right == 1)
	{
		move(game_data, true);
	}

	if(game_data->player.is_right == -1)
	{
		move(game_data, false);
	}

		//PLAYER SHOOTING

	if(game_data->player.is_shooting == true)
	{
		create_bullet(game_data, -10, game_data->player.my_Hitbox.x + 10, game_data->player.my_Hitbox.y - 30, true);
		game_data->player.is_shooting = false;
	}
		// enemy SPEED
	for(int i = 0; i< game_data->game_new; i++)
	{
		game_data->enemies.enemy_speed += 1;
	}



}

void destroy_enemies(SDL_Renderer* renderer, Game_t* game_data, int i)
{
	for(int a = 0; a < game_data->enemies.active_cases; a++)
	{
					
				
				
				

		if(distance_to_enemy(game_data, i, a) < 20 && game_data->enemies.entity[a].life != 0 && game_data->bullets.bullets[i].player_shoot == true)
		{
					

			game_data->enemies.active_enemies--;
			destroy_enemy(renderer, game_data, a);
			destroy_bullet(game_data, i);
			if(game_data->enemies.entity[a].position_in_array == 3)
			{
				game_data->score += 1;
			} else if (game_data->enemies.entity[a].position_in_array == 2)
			{
				game_data->score += 2;
			}
			else if (game_data->enemies.entity[a].position_in_array == 1)
			{
				game_data->score += 3;
			}
			SDL_Texture ** texture = &game_data->enemies.entity[a].my_texture;
			SDL_TimerID timerID = SDL_AddTimer( 500, clear_Texture, texture);



		}
		else if (distance_to_enemy(game_data, i, a) < 10 && game_data->enemies.entity[a].life != 0 && game_data->bullets.bullets[i].player_shoot == false)
		{
			destroy_bullet(game_data, i);
		}
	}

}

void player_shields(SDL_Renderer* renderer, Game_t* game_data, int i)
{
	bullet_entity_t * current_bullet = &game_data->bullets.bullets[i];
	SDL_Rect * bullet_hitbox = &game_data->bullets.bullets[i].entity.my_Hitbox;
	for(int a = 0; a < game_data->bullets.active_cases; a++)
	{
		if(distance_to_bullet(game_data, i, a) <10 && distance_to_bullet(game_data, i, a) != 0) 
		{

			destroy_bullet(game_data, i);
			destroy_bullet(game_data, a);
		}

	}




	if(distance_to_player(game_data, i) < 30)
	{
		game_data->player.life -= 1;
		destroy_bullet(game_data, i);
				
	}

	if(bullet_hitbox->y < 0 || bullet_hitbox->y > HEIGHT) //destroy bullets
	{	
		destroy_bullet(game_data, i);


	}

	for(int a = 0; a<game_data->shields.active_cases; a++)
	{
		if(distance_to_shield(game_data, i, a) < 30)
		{
			destroy_bullet(game_data, i);
			game_data->shields.entity[a].life -= 1;
		}
	}
			


}

void collisions1(SDL_Renderer* renderer, Game_t* game_data)
{
	for(int a = 0; a<game_data->enemies.active_cases; a++)
	{
		if(distance_to_player_enemy(game_data, a) < 30)
		{
			game_data->player.life = 0;
		}
	}
		

	for(int a = 0; a<game_data->shields.active_cases; a++)
	{
		if(game_data->shields.entity[a].life < 1)
		{
			destroy_shield(game_data, a);
		}
	}
		

	for(int a = 0; a < game_data->enemies.active_cases; a++)
	{
		enemy_speed(game_data, a);
	}
		


}

void collisions2(SDL_Renderer* renderer, Game_t* game_data)
{
	for(int a = 0; a < game_data->enemies.active_cases; a++)
	{
		int b = rand();
		if(a < (ENEMY_COLUMNS - 1) * ENEMY_LINES)
		{
			if (b % 5000 / (game_data->game_new + 1) == 0 && game_data->enemies.entity[a].life !=0 && game_data->enemies.entity[a+ENEMY_LINES].life < 1)
			{
				create_bullet(game_data, 10, game_data->enemies.entity[a].my_Hitbox.x + 10, game_data->enemies.entity[a].my_Hitbox.y, false);
			}
		} else
		{	
		if (b % 5000 / (game_data->game_new + 1) == 0 && game_data->enemies.entity[a].life !=0)
			{
				create_bullet(game_data, 10, game_data->enemies.entity[a].my_Hitbox.x + 10, game_data->enemies.entity[a].my_Hitbox.y, false);
			}
		}
	}


	//SHIELDS

	for(int a = 0; a < game_data->shields.active_cases; a++)
	{
		if(game_data->shields.entity[a].life == 5)
		{
			game_data->shields.entity[a].my_texture = makeTexture(renderer, "./assets/shield.bmp");
		}
		else if(game_data->shields.entity[a].life == 4)
		{
			game_data->shields.entity[a].my_texture = makeTexture(renderer, "./assets/shield2.bmp");
		}
		else if(game_data->shields.entity[a].life == 3)
		{
			game_data->shields.entity[a].my_texture = makeTexture(renderer, "./assets/shield3.bmp");
		}
		else if(game_data->shields.entity[a].life == 2)
		{
			game_data->shields.entity[a].my_texture = makeTexture(renderer, "./assets/shield4.bmp");
		}
		else if(game_data->shields.entity[a].life == 1)
		{
			game_data->shields.entity[a].my_texture = makeTexture(renderer, "./assets/shield5.bmp");
		}

	}


}

void renderCopy1(SDL_Renderer* renderer, Game_t* game_data)
{
	int totalFrames = 2;

    int delay = 200;

    int frame = (SDL_GetTicks() / delay) % totalFrames;


	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, game_data->hud.playerLivesTexture, NULL, &game_data->hud.playerLivesRect);
	SDL_RenderCopy(renderer, game_data->hud.scoreTexture, NULL, &game_data->hud.scoreRect);

	
	SDL_RenderCopy(renderer, game_data->player.my_texture, NULL, &game_data->player.my_Hitbox);
	for(int i = 0; i< game_data->bullets.active_cases; i++)
	{
		SDL_RenderCopy(renderer, game_data->bullets.bullets[i].entity.my_texture, NULL, &game_data->bullets.bullets[i].entity.my_Hitbox);

	}
	for(int i = 0; i < game_data->enemies.active_cases; i++)
	{
		if(game_data->enemies.entity[i].life != 0)
		{
			game_data->enemies.entity[i].textureRect.x = frame * game_data->enemies.entity[i].textureRect.w;
			SDL_RenderCopy(renderer, game_data->enemies.entity[i].my_texture, &game_data->enemies.entity[i].textureRect, &game_data->enemies.entity[i].my_Hitbox);
		}
		else
		{
			SDL_RenderCopy(renderer, game_data->enemies.entity[i].my_texture, NULL, &game_data->enemies.entity[i].my_Hitbox);
		}


		
	}
}

