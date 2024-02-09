#ifndef BARREL_H
#define BARREL_H

#include <SDL.h>
#include "Platform.h"

#define BARREL1_TEXTURE "assets/barrel/barrel1.bmp"
#define BARREL2_TEXTURE "assets/barrel/barrel2.bmp"
#define BARREL3_TEXTURE "assets/barrel/barrel3.bmp"
#define BARREL4_TEXTURE "assets/barrel/barrel4.bmp"

#define BARREL_SPEED 120
#define BARREL_FALL_SPEED 200

enum Direction
{
	N,
	L,
	R
};

enum Animation
{
	BARREL1,
	BARREL2,
	BARREL3,
	BARREL4
};

class Barrel
{
private:
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Surface* animationTextures[4];
	Animation state;
	double x;
	double y;
	int isFalling;
	double yBeforeFall;
	Direction direction = N;
	Direction initDirection;
	double* deltaTime;

public:
	SDL_Rect rect;

	Barrel(SDL_Renderer* renderer, int x, int y, Direction direction, double* deltaTime);
	~Barrel();
	void render();
	void fallDown(Platform* platforms, int platformsCount);
	void move();
	void changeDirection();
	int isOnGround(Platform* platforms, int platformsCount);
	void setTexture();
};

#endif