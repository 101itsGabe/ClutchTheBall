#ifndef SDL_MANAGER_H
#define SDL_MANAGER_H

#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <random>
#include <ctime>
#include "SDL.h"
#include <SDL2/SDL_image.h>
#include <menu.h>
#include "SDL_ttf.h"
#include <player.h>
#include "tile.h"
#include "playerManager.h"
#include "tileManager.h"
#include "gameManager.h"

class SDLManager
{

public:
    SDLManager();
    void Highlight(SDL_Renderer *renderer, Tile *tile);
    void renderBackground(SDL_Renderer *renderer, SDL_Texture *texture, int windowWidth, int windoHeight);
    Menu RenderStart(SDL_Renderer*,int,int, TTF_Font*);

    Menu renderMenu(SDL_Renderer *renderer, TTF_Font *font, vector<Tile> *tList, int windowWidth, int windowHeight, Player *p);
    bool InitSDL();
    bool checkStart(int, int);
};

#endif