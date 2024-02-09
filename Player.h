#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include "Platform.h"
#include "Ladder.h"
#include "Barrel.h"

#define PLAYER_IDLE_RIGHT_TEXTURE "assets/mario/mario_right_stay.bmp"
#define PLAYER_IDLE_LEFT_TEXTURE "assets/mario/mario_left_stay.bmp"
#define PLAYER_WALK_RIGHT_TEXTURE "assets/mario/mario_right_walk.bmp"
#define PLAYER_WALK_LEFT_TEXTURE "assets/mario/mario_left_walk.bmp"
#define PLAYER_JUMP_LEFT_TEXTURE "assets/mario/mario_left_jump.bmp"
#define PLAYER_JUMP_RIGHT_TEXTURE "assets/mario/mario_right_jump.bmp"
#define PLAYER_CLIMB_LADDER1_TEXTURE "assets/mario/mario_climb_ladder1.bmp"
#define PLAYER_CLIMB_LADDER2_TEXTURE "assets/mario/mario_climb_ladder2.bmp"

#define WALK_SPEED 80
#define JUMP_POWER 120
#define JUMP_HEIGHT 100

enum PlayerState
{
	IDLE_LEFT,
	IDLE_RIGHT,
	WALK_LEFT,
	WALK_RIGHT,
	JUMP_LEFT,
	JUMP_UP_L,
	JUMP_UP_R,
	JUMP_RIGHT,
	CLIMB_LADDER_UP1,
	CLIMB_LADDER_UP2,
	CLIMB_LADDER_DOWN1,
	CLIMB_LADDER_DOWN2
};

enum FallDirection
{
	LEFT,
	RIGHT,
	DOWN
};

class Game;

class Player
{
private:
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	double x, y = 0;
	Game* game;

	SDL_Surface* animationTextures[12];

	void initTextures();
	void initIdleTextures();
	void initWalkTextures();
	void initJumpTextures();
	void initClimbTextures();
	
public:
	SDL_Rect rect;
	int isJumping = 0;
	int isClimbing = 0;
	int initJumpY = 0;
	enum PlayerState state;
	
	Player(Game* game, SDL_Renderer* renderer, int x, int y);
	~Player();
	void render();
	void moveRight();
	void moveLeft();
	void climbLadderUp();
	void climbLadderDown();
	void jump(const Uint8* keys);
	void preventLeavingScreen();
	void fallDown(Platform* platforms, int platformsCount, enum FallDirection fallDirection);
	int isOnGround(Platform* platforms, int platformsCount);
	int hitsTheCeiling(Platform* platforms, int platformsCount);
	int isOnLadder(Ladder* ladders, int laddersCount);
	void resetAnimation();
	void flightInJump(Platform* platforms, int platformsCount);
	void setTexture();
	int hitsBarrel(Barrel* barrels, int barrelsCount);
};
#endif