#include "gameManager.h"
#include <iostream>
#include <vector>
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
    bool team = true;
    SetUpPointVecs();
    for (Player &p : pl)
    {
        if (team)
        {
            Team1.emplace_back(p);
            p.setTeam("Team1");
            cout << "Set on team1 : " << p.getTeam() << "\n";
            team = false;
        }
        else
        {
            Team2.emplace_back(p);
            p.setTeam("Team2");
            cout << "Set on team2: " << p.getTeam() << "\n";
            team = true;
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
    auto it = std::find(ThreePointerSpots.begin(), ThreePointerSpots.end(), t);
    auto it2 = std::find(TwoPointerSpots.begin(), TwoPointerSpots.end(), t);

    if (it != ThreePointerSpots.end())
    {
        // std::cout << t << " is found in the vector." << std::endl;
        return 3;
    }
    else if (it2 != TwoPointerSpots.end())
    {
        // cout << t << "is found in 2PointVector" << endl;
        return 2;
    }

    return 0;
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
int GameManager::madeShot(Tile *tile, Player *player)
{
    // if true then 3 point shot, false 2 point
    bool or32 = false;
    if (player != NULL)
    {
        auto it = std::find(ThreePointerSpots.begin(), ThreePointerSpots.end(), player->GetTile());
        auto it2 = std::find(TwoPointerSpots.begin(), TwoPointerSpots.end(), player->GetTile());

        if (it != ThreePointerSpots.end())
        {
            cout << "3P: " << *it << endl;
            or32 = true;
        }
        if (it2 != TwoPointerSpots.end())
        {
            cout << "2P: " << *it << endl;
            or32 = false;
        }
    }

    std::mt19937 gen(std::time(0));                  // Initialize with current time as seed
    std::uniform_int_distribution<int> dist(1, 100); // Define a distribution

    int r = dist(gen); // Generate a random number
    cout << r << endl;
    if (or32)
    {
        if (r < player->getStats().ThreePointer)
        {
            cout << "GIMMI THREEEEEEE" << endl;
            return 3;
        }
        return 0;
    }
    else if (!or32)
    {
        if (r < player->getStats().ThreePointer)
        {
            cout << "AND MPS GOOD for another 2" << endl;
            return 2;
        }
        return 0;
    }

    return 0;
}

void GameManager::RenderShotPercent(SDL_Renderer *renderer, TTF_Font *font, int windowWidth, int windowHeight, Player *p)
{
    SDL_Color color = {0, 150, 30};
    if (p != NULL)
    {
        string chanceText = "Shot %:" + to_string(p->getStats().ThreePointer);
        SDL_Surface *surface = TTF_RenderText_Solid(font, chanceText.c_str(), color);
        if (surface != NULL)
        {
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            if (texture != NULL)
            {
                SDL_Rect textRect = {(int)round(windowWidth * 0.89), (int)round(windowHeight * 0.80), (int)round(windowWidth * 0.10), (int)round(windowHeight * 0.08)};
                SDL_RenderCopy(renderer, texture, nullptr, &textRect);
                SDL_DestroyTexture(texture);
            }
        }
        SDL_FreeSurface(surface);
    }
}
