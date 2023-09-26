#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "tile.h"
#include <SDL.h>
#include <string>

struct Stats
{
    int ThreePointer, TwoPointer, Defense;
};

struct ImgRect
{
    int x, y, w, h;
};

// For now player will be a red square
class Player
{
private:
    string imgPath, team;
    int curTile;
    bool curClicked;
    Stats stats;
    ImgRect imgRect;

public:
    Player();
    Player(int);

    void SetTile(int);
    void setClicked(bool);
    void setTeam(string);
    void setImgPath(string);

    int GetTile();
    bool getClicked();
    string getTeam();
    Stats getStats();
};

#endif