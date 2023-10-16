#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <player.h>
#include <tile.h>
#include <playerManager.h>
#include <random>
#include <ctime>
#include <aiPlayer.h>

using namespace std;

class GameManager
{
private:
    int TeamScore1, TeamScore2, HoopTile1, HoopTile2;
    vector<Player> Team1;
    vector<Player> Team2;
    vector<int> ThreePointerSpots;
    vector<int> TwoPointerSpots;
    vector<int> T1StartingPoints;
    vector<int> T2StartingPoints;
    Player *ballPlayer;
    int ifDefense(Player &, vector<Player>);
    bool team1turn;
    void SetUpPointVecs();
    int calculateDistance(int, int);

public:
    GameManager();
    GameManager(vector<Player> &);
    void NewGame();
    void AddTeamScore1(int);
    void AddTeamScore2(int);

    void RenderScore(SDL_Renderer *, TTF_Font *, int, int);
    void RenderShotPercent(SDL_Renderer *, TTF_Font *, int, int, Player *, vector<Player> *);
    void SetBallPlayer(Player &);
    void MoveAI(vector<Player> *);
    void RenderBall(SDL_Renderer *, vector<Tile> *);
    void renderAllText(SDL_Renderer *renderer, vector<Tile> *tile, TTF_Font *font);
    void setTurn(bool);

    int getBallTile();
    int madeShot(Tile *, Player *, vector<Player>);
    int check3(int);
    string WhichTeam(Player *p);
};
#endif
