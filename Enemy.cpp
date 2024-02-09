#include "Enemy.h"
#include <SDL.h>

Enemy::Enemy(SDL_Renderer* renderer, int x, int y)
	: renderer(renderer), x(x), y(y)
{
	enemySurface = SDL_LoadBMP(ENEMY_TEXTURE);
	enemyBarrelSurface = SDL_LoadBMP(ENEMY_BARREL_TEXTURE);

	texture = SDL_CreateTextureFromSurface(renderer, enemySurface);

	rect.w = enemySurface->w;
	rect.h = enemySurface->h;
	rect.x = x;
	rect.y = y;
}

void Enemy::render()
{
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Enemy::prepareToThrowBarrel()
{
	SDL_DestroyTexture(texture);
	texture = SDL_CreateTextureFromSurface(renderer, enemyBarrelSurface);
}

void Enemy::resetTexture()
{
	SDL_DestroyTexture(texture);
	texture = SDL_CreateTextureFromSurface(renderer, enemySurface);
}