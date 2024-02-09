#ifndef GAME_H
#define GAME_H

#include "Levels.h"
#include "Player.h"
#include "Window.h"

#define BARREL_FREQUENCY 5

class Game
{
private:
	SDL_Renderer* renderer;
	SDL_Surface* charset = SDL_LoadBMP(CHARSET_BMP);
	SDL_Window* window;
	Levels* levels;
	struct Level level {};
	Uint32 startTime = 0;

	void printPanelText();
	int gameControl();
	void playerMovementControl();
	void playerControl();
	void playerGravity();
	void barrelsControl();
	void spawnBarrel();

public:
	Player player;
	double deltaTime = 0.0;

	Game(SDL_Renderer* lRenderer, SDL_Window* lWindow);
	void initLevel(int levelNumber);
	int startGame();
	void render();
	void drawPanel();
	int getTimer();
	void printText(int x, int y, const char* text);
};

#endif