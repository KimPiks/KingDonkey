#ifndef ENEMY_H
#define ENEMY_H

#include <SDL.h>

#define ENEMY_TEXTURE "assets/enemy/enemy.bmp"	
#define ENEMY_BARREL_TEXTURE "assets/enemy/enemy_barrel.bmp"

class Enemy
{
private:
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Surface* enemySurface;
	SDL_Surface* enemyBarrelSurface;
	int x, y;

public:
	SDL_Rect rect;

	Enemy(SDL_Renderer* renderer, int x, int y);
	void render();
	void prepareToThrowBarrel();
	void resetTexture();
};

#endif