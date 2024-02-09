#include <SDL.h>
#include "Game.h"
#include "Player.h"
#include "Window.h"
#include <stdio.h>
#include <stdlib.h>

Game::Game(SDL_Renderer* lRenderer, SDL_Window* lWindow) : player(this, lRenderer, 40, 566) 
{
	renderer = lRenderer;
    window = lWindow;
   
    levels = (Levels*)malloc(sizeof(Levels));
    if (levels != NULL)
    {
        Levels llevels(renderer);
		*levels = llevels;
	}
}

void Game::initLevel(int levelNumber)
{
    startTime = SDL_GetTicks();

	switch (levelNumber)
	{
	case 1:
		levels->initLevel1(&level, &deltaTime);
	}
}

int Game::startGame()
{
    Uint32 lastTimeSec = 0;
    int t1 = SDL_GetTicks();

    while (1)
    {
        int t2 = SDL_GetTicks();
        deltaTime = (double)(t2 - t1) / 1000;
        t1 = t2;

        render();

        int control = gameControl();
        if (control != -1)
        {
            return control;
        }
        
        playerControl();
        barrelsControl();

        if (SDL_GetTicks() > lastTimeSec + 100)
        {
            lastTimeSec = SDL_GetTicks();
            player.setTexture();

            int i;
            for (i = 0; i < level.barrelsCount; i++)
            {
                level.barrels[i].setTexture();
            }
        }
        
        if (player.hitsBarrel(level.barrels, level.barrelsCount))
        {
			return 0;
		}
    }
}

int Game::gameControl()
{
    SDL_Event event;
    
    playerMovementControl();

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYUP)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_RIGHT:
            case SDLK_LEFT:
                player.resetAnimation();
                break;
            }
        }
        else if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_n:
                return 0;
                break;
            case SDLK_ESCAPE:
                return 1;
                break;
            }
        }
    }
    return -1;
}

void Game::playerMovementControl()
{
    const Uint8* keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_SPACE])
    {
        if (!player.isJumping && !player.isClimbing && player.isOnGround(level.platforms, level.platformsCount))
            player.jump(SDL_GetKeyboardState(NULL));
    }
    else if (keys[SDL_SCANCODE_RIGHT])
    {
        player.moveRight();
    }
    else if (keys[SDL_SCANCODE_LEFT])
    {
        player.moveLeft();
    }
    else if (keys[SDL_SCANCODE_UP])
    {
        if (player.isOnLadder(level.ladders, level.laddersCount))
            player.climbLadderUp();
    }
    else if (keys[SDL_SCANCODE_DOWN])
    {
        if (player.isOnLadder(level.ladders, level.laddersCount))
            player.climbLadderDown();
    }
}

void Game::playerControl()
{
    if (player.isJumping)
    {
        if (player.rect.y > player.initJumpY - JUMP_HEIGHT)
        {
            player.flightInJump(level.platforms, level.platformsCount);
        }
        else
        {
            player.isJumping = 0;
        }
    }

    if (!player.isOnLadder(level.ladders, level.laddersCount) && player.isClimbing)
    {
        player.isClimbing = 0;
    }

    playerGravity();
}

void Game::playerGravity()
{
    if (!player.isOnGround(level.platforms, level.platformsCount) && !player.isJumping && !player.isClimbing)
    {
        if (player.state == JUMP_LEFT)
        {
            player.fallDown(level.platforms, level.platformsCount, LEFT);
        }
        else if (player.state == JUMP_RIGHT)
        {
            player.fallDown(level.platforms, level.platformsCount, RIGHT);
        }
        else
        {
            player.fallDown(level.platforms, level.platformsCount, DOWN);
        }
    }
}

void Game::barrelsControl()
{
    int i;
    for (i = 0; i < level.barrelsCount; i++)
    {
        if (!level.barrels[i].isOnGround(level.platforms, level.platformsCount))
        {
            level.barrels[i].fallDown(level.platforms, level.platformsCount);
        }

        level.barrels[i].move();
    }

    if (level.barrels[0].rect.w > 0 && level.barrels[0].rect.x < 0)
    {
        for (i = 0; i < level.barrelsCount - 1; i++)
        {
            level.barrels[i] = level.barrels[i + 1];
        }
        level.barrelsCount--;
    }

    spawnBarrel();
}

void Game::spawnBarrel()
{
    if (getTimer() != 0 && getTimer() % BARREL_FREQUENCY == 0 &&
        (getTimer() / BARREL_FREQUENCY >= level.barrelsCount))
    {
        levels->addBarrel(&level, renderer, &deltaTime);
    }
    else if (getTimer() % BARREL_FREQUENCY == 3)
    {
        levels->prepareEnemyToThrowBarrel(&level);
    }
}

void Game::drawPanel()
{
    SDL_Rect rect = { 0, 0, WINDOW_WIDTH, 70 };
    SDL_FillRect(SDL_GetWindowSurface(window), &rect, 80);

    SDL_Texture* scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        WINDOW_WIDTH, WINDOW_HEIGHT);

    printPanelText();

    SDL_UpdateTexture(scrtex, NULL, SDL_GetWindowSurface(window)->pixels, SDL_GetWindowSurface(window)->pitch);
    SDL_RenderCopy(renderer, scrtex, NULL, NULL);

    SDL_DestroyTexture(scrtex);
}

void Game::printPanelText()
{
    char text[28];
    sprintf_s(text, "Author: Kamil Prorok");
    printText(10, 10, text);

    sprintf_s(text, "Timer: %d", getTimer());
    printText(10, 30, text);

    sprintf_s(text, "1234ACEH");
    printText(120, 30, text);

    sprintf_s(text, "[ESC] - leave");
    printText(10, 50, text);

    sprintf_s(text, "[N] - new game");
    printText(120, 50, text);
}

int Game::getTimer()
{
    return (SDL_GetTicks() - startTime) / 1000;
}

void Game::printText(int x, int y, const char* text)
{
    int px, py, c;
    SDL_Rect s, d;
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    s.w = 8;
    s.h = 8;
    d.w = 8;
    d.h = 8;
    while (*text) {
        c = *text & 255;
        px = (c % 16) * 8;
        py = (c / 16) * 8;
        s.x = px;
        s.y = py;
        d.x = x;
        d.y = y;
        SDL_BlitSurface(charset, &s, surface, &d);
        x += 8;
        text++;
    };

    SDL_FreeSurface(surface);
};

void Game::render()
{
    SDL_RenderClear(renderer);

    drawPanel();

    levels->renderLevel(level);

    player.render();

    SDL_RenderPresent(renderer);
}