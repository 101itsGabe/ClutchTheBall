#include "playerManager.h"
#include <SDL.h>
using namespace std;

PlayerManager::PlayerManager()
{
}

PlayerManager::PlayerManager(int numPlayers)
{
    playerSheet = IMG_Load("./src/images/pngsheet.png");
    playerList = new vector<Player>;
    for (int i = 0; i < numPlayers; i++)
    {
        Player p;
        playerList->emplace_back(p);
    }
}
PlayerManager::~PlayerManager()
{
    if (playerSheet != nullptr)
    {
        SDL_FreeSurface(playerSheet);
        playerSheet = nullptr; // Optional: Set to nullptr to avoid potential issues with double freeing
    }

    delete playerList;
}

vector<Player> *PlayerManager::getPlayerList()
{
    return playerList;
}

void PlayerManager::RenderPlayers(SDL_Renderer *renderer, vector<Tile> *tiles)
{

    int sheetX = 124, sheetY = 30, sheetW = 59, sheetH = 85;
    int row = 0;
    // SDL_Surface *copy2 = IMG_Load("./src/images/pngsheet.png");
    for (Player &p : *getPlayerList())
    {
        Tile curTile = (*tiles)[p.GetTile()];
        int padding = curTile.getTileData().tileH * 0.05;
        int posX = curTile.getTileData().tileX + padding;
        int posY = curTile.getTileData().tileY + padding;
        int W = curTile.getTileData().tileW - 2 * padding;
        int H = curTile.getTileData().tileH - 2 * padding;

        sheetX += 60;
        if (row == 4)
        {
            row = 0;
            sheetX = 124;
            sheetY += 85;
        }
        else
            row++;
        SDL_Rect pngSheetRect = {sheetX, sheetY, sheetW, sheetH};
        SDL_Rect destplayerRect = {posX, posY, W, H};
        SDL_Texture *curText = SDL_CreateTextureFromSurface(renderer, playerSheet);
        if (curText)
        {
            SDL_RenderCopy(renderer, curText, &pngSheetRect, &destplayerRect);
        }
        SDL_DestroyTexture(curText);
        // Set blend mode for transparency
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

        // Draw a transparent red rectangle
        if (p.getTeam() == "Team1")
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128); // RGBA color with alpha = 128
        else
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 128); // RGBA color with alpha = 128
        SDL_Rect rect = {posX, posY, W, H};                   // x, y, width, height
        SDL_RenderFillRect(renderer, &rect);

        // Reset blend mode to default
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    }

    // SDL_FreeSurface(copy2);
}
