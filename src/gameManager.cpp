#include "gameManager.h"
#include <iostream>
#include <vector>
#include <climits>
#include <chrono>
#include <algorithm>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <cmath>
#include <playerManager.h>

using namespace std;

GameManager::GameManager()
{
    TeamScore1 = 0;
    TeamScore2 = 0;
    SetUpPointVecs();
}
GameManager::GameManager(vector<Player> &pl)
{
    TeamScore1 = 0;
    TeamScore2 = 0;
    int count1 = 0;
    int count2 = 0;
    bool team = true;
    SetUpPointVecs();
    for (Player &p : pl)
    {
        if (team)
        {
            Team1.emplace_back(p);
            p.setTeam("Team1");
            p.SetTile(T1StartingPoints[count1]);
            team = false;
            count1++;
        }
        else
        {
            p = AiPlayer(p.GetTile());
            Team2.emplace_back();
            p.setTeam("Team2");
            p.SetTile(T2StartingPoints[count2]);
            team = true;
            count2++;
        }
    }
}

string GameManager::WhichTeam(Player *player)
{
    for (Player &p : Team1)
    {
        if (p.GetTile() == player->GetTile())
        {
            return "Team1";
        }
    }
    for (Player &p : Team2)
    {
        if (p.GetTile() == player->GetTile())
        {
            return "Team2";
        }
    }
    return "None";
}

void GameManager::SetUpPointVecs()
{
    T1StartingPoints = {
        54,
        68,
        84,
    };
    T2StartingPoints = {66, 50, 80};
    HoopTile1 = 60;
    HoopTile2 = 74;

    TwoPointerSpots = {15, 16, 17, 18, 30, 31, 32, 33, 34, 45,
                       46, 47, 48, 49, 61, 62, 63, 64, 75, 76, 77, 78, 79, 9, 91,
                       92, 94, 94, 105, 106, 107, 108};
}

void GameManager::NewGame()
{
    TeamScore1 = 0;
    TeamScore2 = 0;
}

void GameManager::AddTeamScore1(int s)
{
    TeamScore1 += s;
}

void GameManager::AddTeamScore2(int s)
{
    TeamScore2 += s;
}

int GameManager::check3(int t)
{
    auto it2 = std::find(TwoPointerSpots.begin(), TwoPointerSpots.end(), t);

    if (it2 != TwoPointerSpots.end())
    {
        // std::cout << t << " is found in the vector." << std::endl;
        return 2;
    }
    else if (t == HoopTile1 || t == HoopTile2)
    {
        return 1;
    }
    else
        return 3;
}

void GameManager::RenderScore(SDL_Renderer *renderer, TTF_Font *font, int windowWidth, int windowHeight)
{
    SDL_Color color = {0, 0, 0};
    SDL_Surface *surface = TTF_RenderText_Solid(font, to_string(TeamScore1).c_str(), color);
    if (surface != NULL)
    {
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture != NULL)
        {
            SDL_Rect textRect = {(int)round(windowWidth * 0.05), (int)round(windowHeight * 0.01), (int)round(windowWidth * 0.1), (int)round(windowHeight * 0.1)};
            SDL_RenderCopy(renderer, texture, nullptr, &textRect);
            SDL_DestroyTexture(texture);
        }
    }
    SDL_FreeSurface(surface);

    surface = TTF_RenderText_Solid(font, to_string(TeamScore2).c_str(), color);
    if (surface != NULL)
    {
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture != NULL)
        {
            SDL_Rect textRect = {(int)round(windowWidth * 0.85), (int)round(windowHeight * 0.01), (int)round(windowWidth * 0.1), (int)round(windowHeight * 0.1)};
            SDL_RenderCopy(renderer, texture, nullptr, &textRect);
            SDL_DestroyTexture(texture);
        }
    }
    SDL_FreeSurface(surface);
}

// returns the number of points
int GameManager::madeShot(Tile *tile, Player *player, vector<Player> pList)
{
    // if true then 3 point shot, false 2 point

    bool or32 = false;
    if (player != NULL)
    {
        // auto it = std::find(ThreePointerSpots.begin(), ThreePointerSpots.end(), player->GetTile());
        auto it2 = std::find(TwoPointerSpots.begin(), TwoPointerSpots.end(), player->GetTile());

        if (it2 != TwoPointerSpots.end())
        {
            cout << "2P: " << *it2 << endl;
            or32 = false;
        }
        else
        {
            or32 = true;
        }
    }

    int defense = ifDefense(*player, pList);
    std::random_device rd;                                                                         // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count() + rd()); // Combine current time with random_device
    std::uniform_int_distribution<int> dist(1, 100);                                               // Define a distribution

    int r = dist(gen); // Generate a random number
    cout << "Random Num: " << r << endl;
    if (or32)
    {
        if (r < (player->getStats().ThreePointer - defense))
        {
            cout << "GIMMI THREEEEEEE" << endl;
            return 3;
        }
        return 0;
    }
    else if (!or32)
    {
        if (r < (player->getStats().TwoPointer - defense))
        {
            cout << "AND MPS GOOD for another 2" << endl;
            return 2;
        }
        return 0;
    }

    return 0;
}

void GameManager::RenderShotPercent(SDL_Renderer *renderer, TTF_Font *font, int windowWidth, int windowHeight, Player *p, vector<Player> *pList)
{
    SDL_Color color = {0, 255, 30};
    if (p != NULL)
    {

        int defense = ifDefense(*p, *pList);
        auto it = find(TwoPointerSpots.begin(), TwoPointerSpots.end(), p->GetTile());
        string chanceText = "Shot: ";
        if (it != TwoPointerSpots.end())
            chanceText += to_string(p->getStats().TwoPointer - defense) + "%";
        else
            chanceText += to_string(p->getStats().ThreePointer - defense) + "%";
        SDL_Surface *surface = TTF_RenderText_Solid(font, chanceText.c_str(), color);
        if (surface != NULL)
        {
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            if (texture != NULL)
            {
                SDL_Rect textRect = {(int)round(windowWidth * 0.89), (int)round(windowHeight * 0.90), (int)round(windowWidth * 0.10), (int)round(windowHeight * 0.08)};
                SDL_RenderCopy(renderer, texture, nullptr, &textRect);
                SDL_DestroyTexture(texture);
            }
        }
        SDL_FreeSurface(surface);
    }
}

void GameManager::SetBallPlayer(Player &p)
{
    ballPlayer = &p;
}

int GameManager::ifDefense(Player &player, vector<Player> pList)
{
    // Need to implement hoop logic for which team is on which side
    int pTile = player.GetTile();
    int closestDefenderDistance = INT_MAX; // Initialize with a large value
    int closestDefenderDefense = 0;
    for (Player &p : pList)
    {
        int curTile = p.GetTile();
        if (p.getTeam() == "Team2")
        {
            int temp = p.getStats().Defense;
            const int numCols = 15;
            const int numRows = 9;

            int playerRow = pTile / numCols;
            int playerCol = pTile % numCols;
            int defenderRow = curTile / numCols;
            int defenderCol = curTile % numCols;
            int hoop1Row = HoopTile1 / numCols;
            int hoop1Col = HoopTile1 % numCols;

            int rowDiff = abs(playerRow - defenderRow);
            int colDiff = abs(playerCol - defenderCol);
            int hoopRowDif = abs(hoop1Row - playerRow);
            int hoopColDiff = abs(hoop1Col - playerCol);

            int maxDistance = (numCols - 1) / 2 + (numRows - 1) / 2; // Maximum distance in this grid
            int defense = maxDistance - (rowDiff + colDiff) + temp;

            // THIS DONT WORK
            if (defenderCol < playerCol)
            {
                if (rowDiff + colDiff < closestDefenderDistance)
                {
                    closestDefenderDistance = rowDiff + colDiff;
                    if(hoopRowDif + hoopColDiff < closestDefenderDistance){
                        closestDefenderDefense = 0;
                    }
                    if (closestDefenderDistance == 2)
                    {
                        closestDefenderDefense = defense / 2;
                    }
                    else
                        closestDefenderDefense = defense;
                }
            }
            else{
                closestDefenderDefense = 0;
            }
        }
    }
    if (closestDefenderDistance > 2)
        return 0;
    if (closestDefenderDefense <= INT_MAX)
        return closestDefenderDefense;
    else
        return 0;
}

void GameManager::MoveAI(vector<Player> *pList)
{
    Uint32 startTime = SDL_GetTicks();
    Uint32 lastTime = startTime;
    const Uint32 interval = 500; // 3 seconds in milliseconds
    // Check if it's time to call the function
    while (true)
    {
        Uint32 currentTime = SDL_GetTicks();

        // Check if it's time to call the function
        if (currentTime - lastTime >= interval)
        {
            for (Player &p : *pList)
            {
                if (p.getTeam() == "Team2")
                {
                    p = Player(p.GetTile());
                    p.SetTile(p.GetTile() - 1);
                }
            }
            break;

            lastTime = currentTime; // Update lastTime for the next interval
        }
    }
}

void GameManager::RenderBall(SDL_Renderer *renderer, vector<Tile> *tList)
{
    if (ballPlayer != NULL)
    {
        Tile tile = (*tList)[ballPlayer->GetTile()];
        SDL_Surface *s = IMG_Load("./src/images/ball.png");
        if (s)
        {
            SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, s);
            if (t)
            {
                SDL_Rect imgRect = {146, 14, 62, 66};
                SDL_Rect destRect = {tile.getTileData().tileX + 5, tile.getTileData().tileY + 5,
                                     tile.getTileData().tileW / 3, tile.getTileData().tileH / 3};
                SDL_RenderCopy(renderer, t, &imgRect, &destRect);
            }
        }
    }
}


int GameManager::getBallTile(){
    return ballPlayer->GetTile();
}


void GameManager::renderAllText(SDL_Renderer *renderer, vector<Tile> *tList, TTF_Font *font){
    
  for(Tile& t: *tList){
    int tileSize = t.getTileData().tileW;
    int tileX = t.getTileData().tileX;
    int tileY = t.getTileData().tileY;

    string tileId;
    int check = check3(t.getTileId());
    if (check == 3)
        tileId = "3P";
    else if (check == 2)
        tileId = "2P";
    else if (check == 1)
        tileId = "H";
    else
        tileId = to_string(t.getTileId());
    SDL_Color textColor = {85, 85, 85};
    if (font != NULL)
    {
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, tileId.c_str(), textColor);
        if (textSurface != NULL)
        {
            SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            if (textTexture != NULL)
            {
                SDL_Rect textRect = {tileX + 16, tileY + 8, tileSize - 40, tileSize - 40};
                SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
                const char *rendererError = SDL_GetError();
                if (strlen(rendererError) > 0)
                {
                    cout << rendererError << endl;
                }
                SDL_DestroyTexture(textTexture);
            }
        }
        SDL_FreeSurface(textSurface);
    }
  }
}

