#ifndef LADDER_H
#define LADDER_H

#include <SDL.h>

#define LADDER_TEXTURE "assets/ladder/ladder.bmp"

class Ladder
{
private:
	SDL_Renderer* renderer;
	SDL_Texture* texture = NULL;

	void initLadder(SDL_Surface* ladderSurface, int x);
	void initInvisibleLadder(SDL_Surface* ladderSurface, int x);

public:
	SDL_Rect* rect;
	int y, h, broken;

	Ladder(SDL_Renderer* renderer, int x, int y, int h, int broken);
	void render();
};

#endif