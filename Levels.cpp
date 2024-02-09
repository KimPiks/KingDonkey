#include <SDL.h>
#include "Levels.h"
#include "Platform.h"
#include "Ladder.h"
#include "Barrel.h"
#include "Enemy.h"
#include <stdlib.h>

Levels::Levels(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}

void Levels::initLevel1(struct Level* level, double* deltaTime)
{
	level->platformsCount = 0;
	level->platforms = (Platform*)malloc(sizeof(Platform));

	if (level->platforms == NULL)
		return;

	level->barrelsCount = 0;
	level->barrels = (Barrel*)malloc(sizeof(Barrel));

	level->enemy = (Enemy*)malloc(sizeof(Enemy));
	if (level->enemy != NULL)
	{
		Enemy enemy (renderer, 370, 135);
		*(level->enemy) = enemy;
	}

	addLevel1Platforms(level);
	addLevel1Ladders(level);

	renderLevel(*level);
}

void Levels::addLevel1Ladders(struct Level* level)
{
	level->ladders = (Ladder*)malloc(7 * sizeof(Ladder));
	level->laddersCount = 7;
	if (level->ladders == NULL)
	{
		return;
	}

	Ladder l1(renderer, 100, 590, 13, 1);
	Ladder l2(renderer, 260, 585, 11, 0);
	Ladder l3(renderer, 120, 485, 11, 0);
	Ladder l4(renderer, 280, 495, 13, 1);
	Ladder l5(renderer, 240, 390, 12, 0);
	Ladder l6(renderer, 120, 290, 12, 0);
	Ladder l7(renderer, 260, 190, 9, 0);

	level->ladders[0] = l1;
	level->ladders[1] = l2;
	level->ladders[2] = l3;
	level->ladders[3] = l4;
	level->ladders[4] = l5;
	level->ladders[5] = l6;
	level->ladders[6] = l7;
}

void Levels::addLevel1Platforms(struct Level* level)
{
	int index = 0;
	
	addLevel1Platform1(level, &index);
	addLevel1Platform2(level, &index);
	addLevel1Platform3(level, &index);
	addLevel1Platform4(level, &index);
	addLevel1Platform5(level, &index);
	addLevel1Platform6(level, &index);
}

void Levels::addLevel1Platform1(struct Level* level, int* index)
{
	int i;
	for (i = 0; i < 24; i++)
	{
		Platform* tmp = (Platform*)realloc(level->platforms, (*index + 1) * sizeof(Platform));
		level->platforms = tmp;
		level->platformsCount++;
		if (level->platforms == NULL)
			break;

		if (i < 10)
		{
			Platform platform(renderer, 20 * i, 600);
			level->platforms[*index] = platform;
		}

		if (i > 9 && i < 24)
		{
			Platform platform(renderer, 20 * i, 600 - 1.5 * (i - 10));
			level->platforms[*index] = platform;
		}
		(*index)++;
	}
}

void Levels::addLevel1Platform2(struct Level* level, int* index)
{
	int i;
	for (i = 0; i < 18; i++)
	{
		Platform* tmp = (Platform*)realloc(level->platforms, (*index + 1) * sizeof(Platform));
		level->platforms = tmp;
		level->platformsCount++;
		if (level->platforms == NULL)
			break;

		Platform platform(renderer, 20 * i, 500 + 1.5 * (i - 10));
		level->platforms[*index] = platform;
		(*index)++;
	}
}

void Levels::addLevel1Platform3(struct Level* level, int* index)
{
	int i;
	for (i = 5; i < 20; i++)
	{
		Platform* tmp = (Platform*)realloc(level->platforms, (*index + 1) * sizeof(Platform));
		level->platforms = tmp;
		level->platformsCount++;
		if (level->platforms == NULL)
			break;

		if (i < 15)
		{
			Platform platform(renderer, 20 * i, 400 - 0.8 * (i - 10));
			level->platforms[*index] = platform;
		}
		else
		{
			Platform platform(renderer, 20 * i, 396);
			level->platforms[*index] = platform;
		}
		(*index)++;
	}
}

void Levels::addLevel1Platform4(struct Level* level, int* index)
{
	int i;
	for (i = 1; i < 14; i++)
	{
		Platform* tmp = (Platform*)realloc(level->platforms, (*index + 1) * sizeof(Platform));
		level->platforms = tmp;
		level->platformsCount++;
		if (level->platforms == NULL)
			break;

		Platform platform(renderer, 20 * i, 300 + 0.8 * (i - 10));
		level->platforms[*index] = platform;
		(*index)++;
	}
}

void Levels::addLevel1Platform5(struct Level* level, int* index)
{
	int i;
	for (i = 5; i < 24; i++)
	{
		Platform* tmp = (Platform*)realloc(level->platforms, (*index + 1) * sizeof(Platform));
		level->platforms = tmp;
		level->platformsCount++;
		if (level->platforms == NULL)
			break;

		Platform platform(renderer, 20 * i, 200 - 0.2 * (i - 10));
		level->platforms[*index] = platform;
		(*index)++;
	}
}

void Levels::addLevel1Platform6(struct Level* level, int* index)
{
	int i;
	for (i = 10; i < 15; i++)
	{
		Platform* tmp = (Platform*)realloc(level->platforms, (*index + 1) * sizeof(Platform));
		level->platforms = tmp;
		level->platformsCount++;
		if (level->platforms == NULL)
			break;

		Platform platform(renderer, 20 * i, 130);
		level->platforms[*index] = platform;
		(*index)++;
	}
}

void Levels::addBarrel(struct Level* level, SDL_Renderer* renderer, double* deltaTime)
{
	level->barrelsCount++;
	Barrel* tmp = (Barrel*)realloc(level->barrels, level->barrelsCount * sizeof(Barrel));
	level->barrels = tmp;
	if (level->barrels == NULL)
		return;

	Barrel barrel(renderer, 330, 170, L, deltaTime);
	level->barrels[level->barrelsCount - 1] = barrel;

	level->enemy[0].resetTexture();
}

void Levels::prepareEnemyToThrowBarrel(struct Level* level)
{
	level->enemy[0].prepareToThrowBarrel();
}

void Levels::renderLevel(struct Level level)
{
	int i;
	for (i = 0; i < level.platformsCount; i++)
	{
		level.platforms[i].render();
	}
	for (i = 0; i < level.laddersCount; i++)
	{
		level.ladders[i].render();
	}
	for (i = 0; i < level.barrelsCount; i++)
	{
		level.barrels[i].render();
	}

	level.enemy[0].render();
}