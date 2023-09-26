#include "player.h"
#include "tile.h"
#include "SDL.h"
#include <SDL_image.h>

Player::Player()
{
    curTile = 0;
    curClicked = false;
    stats.ThreePointer = 33;
    stats.TwoPointer = 66;
    stats.Defense = 10;
}

Player::Player(int t)
{
    curTile = t;
    curClicked = false;
    stats.ThreePointer = 33;
    stats.TwoPointer = 66;
    stats.Defense = 10;
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