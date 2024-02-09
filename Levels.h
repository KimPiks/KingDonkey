#ifndef LEVELS_H
#define LEVELS_H

#include "Platform.h"
#include "Ladder.h"
#include "Barrel.h"
#include "Enemy.h"

struct Level
{
	Platform* platforms;
	int platformsCount;
	Ladder* ladders;
	int laddersCount;
	Barrel* barrels;
	int barrelsCount;
	Enemy* enemy;
};

class Levels
{
private:
	SDL_Renderer* renderer;
	void addLevel1Platforms(struct Level* level);
	void addLevel1Ladders(struct Level* level);
	void addLevel1Platform1(struct Level* level, int* index);
	void addLevel1Platform2(struct Level* level, int* index);
	void addLevel1Platform3(struct Level* level, int* index);
	void addLevel1Platform4(struct Level* level, int* index);
	void addLevel1Platform5(struct Level* level, int* index);
	void addLevel1Platform6(struct Level* level, int* index);

public:
	Levels(SDL_Renderer* renderer);
	void initLevel1(struct Level* level, double* deltaTime);
	void renderLevel(struct Level level);
	void addBarrel(struct Level* level, SDL_Renderer* renderer, double* deltaTime);
	void prepareEnemyToThrowBarrel(struct Level* level);
};

#endif