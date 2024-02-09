#include <SDL.h>
#include "Ladder.h"
#include <stdlib.h>

Ladder::Ladder(SDL_Renderer* renderer, int x, int y, int h, int broken)
	: renderer(renderer), y(y), h(h), broken(broken)
{
	SDL_Surface* ladderSurface = SDL_LoadBMP(LADDER_TEXTURE);

	rect = (SDL_Rect*)malloc(h * sizeof(SDL_Rect));
	if (rect == NULL)
	{
		return;
	}

	initLadder(ladderSurface, x);

	texture = SDL_CreateTextureFromSurface(renderer, ladderSurface);
	SDL_FreeSurface(ladderSurface);
}

void Ladder::initLadder(SDL_Surface* ladderSurface, int x)
{
	int i;
	for (i = 0; i < h - 2; i++)
	{
		rect[i].w = ladderSurface->w;
		rect[i].h = ladderSurface->h;
		rect[i].x = x;
		rect[i].y = y - i * ladderSurface->h;
	}

	initInvisibleLadder(ladderSurface, x);
}

void Ladder::initInvisibleLadder(SDL_Surface* ladderSurface, int x)
{
	rect[h - 4].w = ladderSurface->w;
	rect[h - 4].h = ladderSurface->h;
	rect[h - 4].x = x;
	rect[h - 4].y = y - (h - 5) * ladderSurface->h;
	rect[h - 3].w = ladderSurface->w;
	rect[h - 3].h = ladderSurface->h;
	rect[h - 3].x = x;
	rect[h - 3].y = y - (h - 4) * ladderSurface->h;
	rect[h - 2].w = ladderSurface->w;
	rect[h - 2].h = ladderSurface->h;
	rect[h - 2].x = x;
	rect[h - 2].y = y - (h - 3) * ladderSurface->h;
	rect[h - 1].w = ladderSurface->w;
	rect[h - 1].h = ladderSurface->h;
	rect[h - 1].x = x;
	rect[h - 1].y = y - (h - 2) * ladderSurface->h;
}

void Ladder::render()
{
	int i;
	if (broken == 0)
	{
		for (i = 0; i < h-4; i++)
		{
			SDL_RenderCopy(renderer, texture, NULL, &rect[i]);
		}
		SDL_RenderCopy(renderer, NULL, NULL, &rect[h-3]);
		SDL_RenderCopy(renderer, NULL, NULL, &rect[h-2]);
		SDL_RenderCopy(renderer, NULL, NULL, &rect[h-1]);
		SDL_RenderCopy(renderer, NULL, NULL, &rect[h]);
	}
	else
	{
		for (i = 0; i < h-4; i++)
		{
			if (i > (h-4)/2-2 && i < (h-4)/2+2)
				continue;

			SDL_RenderCopy(renderer, texture, NULL, &rect[i]);
		}
	}
}