#include "playerManager.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <SDL_image.h>

using namespace std;

PlayerManager::PlayerManager()
{
}

PlayerManager::PlayerManager(int numPlayers)
{
    playerSheet = IMG_Load("images/pngsheet.png");
    SDL_FreeSurface(playerSheet);
    int pngCount = 0;
    for (int i = 0; i < numPlayers; i++)
    {
        Player p;
        playerList.emplace_back(p);
    }
}

vector<Player> &PlayerManager::getPlayerList()
{
    return playerList;
}

SDL_Surface *PlayerManager::getSurface()
{
    SDL_Surface *copy = playerSheet;
    SDL_FreeSurface(copy);
    return copy;
}

void PlayerManager::RenderPlayers(SDL_Renderer *renderer, Tile *tile, PlayerManager pm)
{

        // cout << "Player Renderer TileX: " << tile->getTileData().tileX << endl;
    int padding = tile->getTileData().tileH * 0.05;
    int posX = tile->getTileData().tileX + padding;
    int posY = tile->getTileData().tileY + padding;
    int W = tile->getTileData().tileW - 2 * padding;
    int H = tile->getTileData().tileH - 2 * padding;

    SDL_Rect pngSheetRect = {125, 25, 58, 94};
    SDL_Rect destplayerRect = {posX, posY, W, H};
    /*
    if (getTeam() == "Team1")
        SDL_SetRenderDrawColor(renderer, 250, 0, 0, 250);
    else if (getTeam() == "Team2")
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 250, 250);
        // cout << getTeam();
    }

    SDL_RenderFillRect(renderer, &playerRect);
    // Set Tile draw Color
    // SDL_SetRenderDrawColor(renderer, 250,0,0,250);
    // SDL_RenderDrawRect(renderer, &playerRect);
    */

    SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, pm.getSurface());
    if (t != NULL)
        SDL_RenderCopy(renderer, t, &pngSheetRect, &destplayerRect);
    SDL_DestroyTexture(t);
}