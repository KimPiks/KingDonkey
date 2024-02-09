#ifndef PLATFORM_H
#define PLATFORM_H

#include <SDL.h>

#define PLATFORM_TEXTURE "assets/platform/platform.bmp"

class Platform
{
private:
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	int x, y;

public:
	SDL_Rect rect;

	Platform(SDL_Renderer* renderer, int x, int y);
	void render();
};

#endif