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

void PlayerManager::RenderPlayers(SDL_Renderer *renderer, vector<Tile> tiles)
{
    for (Player &p : playerList)
    {
        Tile tile = tiles[p.GetTile()];
        int padding = tile.getTileData().tileH * 0.05;
        int posX = tile.getTileData().tileX + padding;
        int posY = tile.getTileData().tileY + padding;
        int W = tile.getTileData().tileW - 2 * padding;
        int H = tile.getTileData().tileH - 2 * padding;

        SDL_Rect pngSheetRect = {125, 25, 58, 94};
        SDL_Rect destplayerRect = {posX, posY, W, H};

        if (p.getTeam() == "Team1")
            SDL_SetRenderDrawColor(renderer, 250, 0, 0, 250);
        else if (p.getTeam() == "Team2")
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 250, 250);
            // cout << getTeam();
        }

        SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, getSurface());
        if (t != NULL)
            SDL_RenderCopy(renderer, t, &pngSheetRect, &destplayerRect);
        SDL_DestroyTexture(t);
    }
}
