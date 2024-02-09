#include "Player.h"
#include "Platform.h"
#include "Window.h"
#include "Game.h"
#include <SDL.h>

Player::Player(Game* game, SDL_Renderer* renderer, int x, int y)
	: game(game), renderer(renderer), x(x), y(y)
{
	state = IDLE_RIGHT;
	SDL_Surface* platformSurface = SDL_LoadBMP(PLAYER_IDLE_RIGHT_TEXTURE);

	rect.w = platformSurface->w;
	rect.h = platformSurface->h;

	texture = SDL_CreateTextureFromSurface(renderer, platformSurface);
	SDL_FreeSurface(platformSurface);

	initTextures();
}

Player::~Player()
{
	SDL_DestroyTexture(texture);
	
	int i;
	for (i = 0; i < 12; i++)
	{
		SDL_FreeSurface(animationTextures[i]);
	}
}

void Player::initTextures()
{
	initIdleTextures();
	initWalkTextures();
	initJumpTextures();
	initClimbTextures();
}

void Player::initIdleTextures()
{
	animationTextures[IDLE_LEFT] = SDL_LoadBMP(PLAYER_IDLE_LEFT_TEXTURE);
	animationTextures[IDLE_RIGHT] = SDL_LoadBMP(PLAYER_IDLE_RIGHT_TEXTURE);
}

void Player::initWalkTextures()
{
	animationTextures[WALK_LEFT] = SDL_LoadBMP(PLAYER_WALK_LEFT_TEXTURE);
	animationTextures[WALK_RIGHT] = SDL_LoadBMP(PLAYER_WALK_RIGHT_TEXTURE);
}

void Player::initJumpTextures()
{
	animationTextures[JUMP_LEFT] = SDL_LoadBMP(PLAYER_JUMP_LEFT_TEXTURE);
	animationTextures[JUMP_RIGHT] = SDL_LoadBMP(PLAYER_JUMP_RIGHT_TEXTURE);
	animationTextures[JUMP_UP_L] = SDL_LoadBMP(PLAYER_JUMP_LEFT_TEXTURE);
	animationTextures[JUMP_UP_R] = SDL_LoadBMP(PLAYER_JUMP_RIGHT_TEXTURE);
}

void Player::initClimbTextures()
{
	animationTextures[CLIMB_LADDER_UP1] = SDL_LoadBMP(PLAYER_CLIMB_LADDER1_TEXTURE);
	animationTextures[CLIMB_LADDER_UP2] = SDL_LoadBMP(PLAYER_CLIMB_LADDER2_TEXTURE);
	animationTextures[CLIMB_LADDER_DOWN1] = SDL_LoadBMP(PLAYER_CLIMB_LADDER1_TEXTURE);
	animationTextures[CLIMB_LADDER_DOWN2] = SDL_LoadBMP(PLAYER_CLIMB_LADDER2_TEXTURE);
}

void Player::render()
{
	rect.x = x;
	rect.y = y;
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Player::moveRight()
{
	switch (state)
	{
	case WALK_RIGHT:
		state = IDLE_RIGHT;
		break;
	default:
		state = WALK_RIGHT;
		break;
	}

	x += WALK_SPEED * game->deltaTime;

	preventLeavingScreen();
}

void Player::moveLeft()
{
	switch (state)
	{
	case WALK_LEFT:
		state = IDLE_LEFT;
		break;
	default:
		state = WALK_LEFT;
		break;
	}

	x -= WALK_SPEED * game->deltaTime;

	preventLeavingScreen();
}

void Player::jump(const Uint8* keys)
{
	isJumping = 1;
	initJumpY = y;
	if (keys[SDL_SCANCODE_RIGHT] && !keys[SDL_SCANCODE_LEFT])
	{
		state = JUMP_RIGHT;
	}
	else if (!keys[SDL_SCANCODE_RIGHT] && keys[SDL_SCANCODE_LEFT])
	{
		state = JUMP_LEFT;
	}
	else
	{
		if (state == IDLE_LEFT)
		{
			state = JUMP_UP_L;
		}
		else
		{
			state = JUMP_UP_R;
		}
	}
}

void Player::flightInJump(Platform* platforms, int platformsCount)
{
	if (state == JUMP_LEFT)
	{
		x -= WALK_SPEED * game->deltaTime;
	}
	else if (state == JUMP_RIGHT)
	{
		x += WALK_SPEED * game->deltaTime;
	}
	y -= JUMP_POWER * game->deltaTime;

	if (hitsTheCeiling(platforms, platformsCount))
	{
		y += JUMP_POWER * game->deltaTime;
		isJumping = 0;
	}
	preventLeavingScreen();
}

void Player::climbLadderUp()
{
	isClimbing = 1;
	if (state == CLIMB_LADDER_UP1)
	{
		state = CLIMB_LADDER_UP2;
	}
	else
	{
		state = CLIMB_LADDER_UP1;
	}

	y -= WALK_SPEED * game->deltaTime;
}

void Player::climbLadderDown()
{
	isClimbing = 1;
	if (state == CLIMB_LADDER_DOWN1)
	{
		state = CLIMB_LADDER_DOWN2;
	}
	else
	{
		state = CLIMB_LADDER_DOWN1;
	}

	y += WALK_SPEED * game->deltaTime;
}

void Player::fallDown(Platform* platforms, int platformsCount, enum FallDirection fallDirection)
{
	y += JUMP_POWER * game->deltaTime;
	if (fallDirection == LEFT)
	{
		x -= JUMP_POWER * game->deltaTime;
	}
	else if (fallDirection == RIGHT)
	{
		x += JUMP_POWER * game->deltaTime;
	}
	preventLeavingScreen();
}

void Player::setTexture()
{
	SDL_DestroyTexture(texture);
	texture = SDL_CreateTextureFromSurface(renderer, animationTextures[state]);
}

void Player::resetAnimation()
{
	switch (state)
	{
	case WALK_LEFT:
	case JUMP_LEFT:
		state = IDLE_LEFT;
		break;
	case WALK_RIGHT:
	case JUMP_RIGHT:
		state = IDLE_RIGHT;
		break;
	}
}

void Player::preventLeavingScreen()
{
	if ((rect.x + rect.w) >= WINDOW_WIDTH)
	{
		x = WINDOW_WIDTH - rect.w - 1;
	}
	else if (rect.x <= 0)
	{
		x = 1;
	}
}

int Player::isOnGround(Platform* platforms, int platformsCount)
{
	int i;
	for (i = 0; i < platformsCount; i++)
	{
		if (rect.x + rect.w > platforms[i].rect.x &&
			rect.x < platforms[i].rect.x + platforms[i].rect.w)
		{
			if ((rect.y + rect.h) == platforms[i].rect.y)
			{
				return 1;
			}
			else if (((rect.y + rect.h) > platforms[i].rect.y) &&
				((rect.y + rect.h) < (platforms[i].rect.y + 5) && !isClimbing))
			{
				y = platforms[i].rect.y - rect.h;
				return 1;
			}
		}
	}
	return 0;
}

int Player::isOnLadder(Ladder* ladders, int laddersCount)
{
	int i, j;
	for (i = 0; i < laddersCount; i++)
	{
		if (ladders[i].broken)
		{
			continue;
		}
		for (j = 0; j < ladders[i].h; j++)
		{
			if (rect.x + rect.w > ladders[i].rect[j].x &&
				rect.x < ladders[i].rect[j].x + ladders[i].rect[j].w)
			{
				if (rect.y + rect.h > ladders[i].rect[0].y + ladders[i].rect[0].h && 
					rect.y + rect.h < ladders[i].rect[0].y + ladders[i].rect[0].h + 10)
				{
					y = ladders[i].rect[0].y - rect.h;
					return 0;
				}

				if (rect.y + rect.h <= ladders[i].rect[j].y + ladders[i].rect[j].h &&
					rect.y + rect.h >= ladders[i].rect[j].y)
				{
					return 1;
				}
			}
		}
	}
	return 0;
}

int Player::hitsTheCeiling(Platform* platforms, int platformsCount)
{
	if (rect.y < GAME_MAX_HEIGHT)
	{
		return 1;
	}
	int i;
	for (i = 0; i < platformsCount; i++)
	{
		if (rect.x + rect.w > platforms[i].rect.x &&
			rect.x < platforms[i].rect.x + platforms[i].rect.w)
		{
			if (rect.y <= (platforms[i].rect.y + platforms[i].rect.h)
				&& rect.y > platforms[i].rect.y)
			{
				return 1;
			}
		}
	}
	return 0;
}

int Player::hitsBarrel(Barrel* barrels, int barrelsCount)
{
	int i;
	for (i = 0; i < barrelsCount; i++)
	{
		if (rect.x + rect.w > barrels[i].rect.x &&
			rect.x < barrels[i].rect.x + barrels[i].rect.w)
		{
			if (rect.y + rect.h > barrels[i].rect.y &&
				rect.y < barrels[i].rect.y + barrels[i].rect.h)
			{
				return 1;
			}
		}
	}
	return 0;
}