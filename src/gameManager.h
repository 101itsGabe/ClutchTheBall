#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>
#include <player.h>
#include <playerManager.h>
#include <random>
#include <ctime>

using namespace std;

class GameManager
{
private:
    int TeamScore1, TeamScore2;
    vector<Player> Team1;
    vector<Player> Team2;
    vector<int> ThreePointerSpots;
    vector<int> TwoPointerSpots;

public:
    GameManager();
    GameManager(vector<Player> &);
    void NewGame();
    void AddTeamScore1(int);
    void AddTeamScore2(int);
    void SetUpPointVecs();
    void RenderScore(SDL_Renderer *, TTF_Font *, int, int);
    void RenderShotPercent(SDL_Renderer *, TTF_Font *, int, int, Player *);

    int madeShot(Tile *, Player *);
    int check3(int);
    string WhichTeam(Player *p);
};
#endif
