#include "Barrel.h"
#include <SDL.h>
#include <stdio.h>

Barrel::Barrel(SDL_Renderer* renderer, int x, int y, Direction direction, double* deltaTime)
	: renderer(renderer), x(x), y(y), initDirection(direction), deltaTime(deltaTime)
{
	animationTextures[BARREL1] = SDL_LoadBMP(BARREL1_TEXTURE);
	animationTextures[BARREL2] = SDL_LoadBMP(BARREL2_TEXTURE);
	animationTextures[BARREL3] = SDL_LoadBMP(BARREL3_TEXTURE);
	animationTextures[BARREL4] = SDL_LoadBMP(BARREL4_TEXTURE);

	state = BARREL1;

	SDL_Surface* platformSurface = SDL_LoadBMP(BARREL1_TEXTURE);
	texture = SDL_CreateTextureFromSurface(renderer, platformSurface);

	rect.w = platformSurface->w;
	rect.h = platformSurface->h;

	isFalling = 1;
	yBeforeFall = y;

	SDL_FreeSurface(platformSurface);
}

Barrel::~Barrel()
{
	SDL_DestroyTexture(texture);
}

void Barrel::setTexture()
{
	SDL_DestroyTexture(texture);
	texture = SDL_CreateTextureFromSurface(renderer, animationTextures[state]);
}

void Barrel::render()
{
	rect.x = x;
	rect.y = y;
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Barrel::fallDown(Platform* platforms, int platformsCount)
{
	if (isFalling == 0)
	{
		yBeforeFall = y;
		isFalling = 1;
	}
	y += BARREL_FALL_SPEED * (*deltaTime);
}

void Barrel::move()
{
	if (direction == L)
	{
		x -= BARREL_SPEED * (*deltaTime);
	}
	else
	{
		x += BARREL_SPEED * (*deltaTime);
	}

	switch (state)
	{
	case BARREL1:
		state = BARREL2;
		break;
	case BARREL2:
		state = BARREL3;
		break;
	case BARREL3:
		state = BARREL4;
		break;
	case BARREL4:
		state = BARREL1;
		break;
	}
}

int Barrel::isOnGround(Platform* platforms, int platformsCount)
{
	int i;
	for (i = 0; i < platformsCount; i++)
	{
		if (rect.x + rect.w > platforms[i].rect.x &&
			rect.x < platforms[i].rect.x + platforms[i].rect.w)
		{
			if ((rect.y + rect.h) == platforms[i].rect.y)
			{
				changeDirection();
				return 1;
			}
			else if (((rect.y + rect.h) > platforms[i].rect.y) &&
				((rect.y + rect.h) < (platforms[i].rect.y + 5)))
			{
				y = platforms[i].rect.y - rect.h;
				changeDirection();
				return 1;
			}
		}
	}
	return 0;
}

void Barrel::changeDirection()
{
	if (isFalling == 1)
	{
		isFalling = 0;
		if (y - yBeforeFall > 10)
		{
			if (direction == N)
			{
				direction = initDirection;
			}
			else if (direction == L)
			{
				direction = R;
			}
			else
			{
				direction = L;
			}
		}
		yBeforeFall = y;
	}
}