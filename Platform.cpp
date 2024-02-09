#include <SDL.h>
#include "Platform.h"

Platform::Platform(SDL_Renderer* renderer, int x, int y)
	: renderer(renderer), x(x), y(y)
{
	SDL_Surface* platformSurface = SDL_LoadBMP(PLATFORM_TEXTURE);
	texture = SDL_CreateTextureFromSurface(renderer, platformSurface);

	rect.w = platformSurface->w;
	rect.h = platformSurface->h;

	SDL_FreeSurface(platformSurface);
}

void Platform::render()
{
	rect.x = x;
	rect.y = y;
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}