#include <stdio.h>
#include <SDL.h>
#include "Platform.h"
#include "Levels.h"
#include "Player.h"
#include "Window.h"
#include "Game.h"

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "KingDonkey by Kamil Prorok");
    SDL_ShowCursor(SDL_DISABLE);

    int end = 0;
    while (!end)
    {
        Game game(renderer, window);
        game.initLevel(1);
        end = game.startGame();
        SDL_Delay(500);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}