#include "player.h"
#include "tile.h"
#include "SDL.h"
#include <SDL_image.h>

Player::Player()
{
    curTile = 0;
    curClicked = false;
    stats.ThreePointer = 33;
    stats.TwoPointer = 33;
}

Player::Player(int t)
{
    curTile = t;
    curClicked = false;
    stats.ThreePointer = 33;
    stats.TwoPointer = 33;
}

void Player::setImgPath(string p)
{
    imgPath = p;
}

void Player::SetTile(int t)
{
    curTile = t;
}

int Player::GetTile()
{
    return curTile;
}

/*
void Player::RenderPlayer(SDL_Renderer *renderer, Tile *tile, PlayerManager pm)
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


    SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, pm.getSurface());
    if (t != NULL)
        SDL_RenderCopy(renderer, t, &pngSheetRect, &destplayerRect);
    SDL_DestroyTexture(t);
}
*/
void Player::setClicked(bool b)
{
    curClicked = b;
}

bool Player::getClicked()
{
    return curClicked;
}

void Player::setTeam(string t)
{
    team = t;
}

string Player::getTeam()
{
    return team;
}

Stats Player::getStats()
{
    return stats;
}