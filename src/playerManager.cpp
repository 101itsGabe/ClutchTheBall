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
    playerSheet = IMG_Load("src/images/pngsheet.png");
    if (playerSheet == NULL)
    {
        cout << "player sheet is null :(" << endl;
    }
    else
    {
        cout << "Player sheet IS NOT NULL" << endl;
    }

    for (int i = 0; i < numPlayers; i++)
    {
        Player p;
        playerList.emplace_back(p);
    }
}
PlayerManager::~PlayerManager()
{
    if (playerSheet != nullptr)
    {
        SDL_FreeSurface(playerSheet);
        playerSheet = nullptr; // Optional: Set to nullptr to avoid potential issues with double freeing
    }
}

vector<Player> &PlayerManager::getPlayerList()
{
    return playerList;
}

SDL_Surface *PlayerManager::getSurface()
{
    return playerSheet;
}

void PlayerManager::RenderPlayers(SDL_Renderer *renderer, vector<Tile> tiles)
{
    SDL_Surface *copy = getSurface();
    cout << "COPY I TOOK YOUR BITCH AND BODY" << endl;
    if (!getPlayerList().empty())
    {
        for (Player &p : getPlayerList())
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
            }
            if (copy != nullptr)
            {
                SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, copy);
                if (t != nullptr)
                {
                    cout << "inside before render copy" << endl;
                    SDL_RenderCopy(renderer, t, &pngSheetRect, &destplayerRect);
                }
                else
                {
                    cout << "Well well well texture IS null" << endl;
                }
                SDL_DestroyTexture(t);
            }
        }
        SDL_FreeSurface(copy);
    }
}
