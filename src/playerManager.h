#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H
#include <vector>
#include <SDL.h>
#include "player.h"

class PlayerManager
{
private:
    vector<Player> playerList;
    SDL_Surface *playerSheet;

public:
    PlayerManager();
    PlayerManager(int);

    // void addPlayer(Player );
    // void removePlayer(Player);
    void PlayerManager::RenderPlayer(SDL_Renderer *renderer, Tile *tile, PlayerManager pm);

    vector<Player> &getPlayerList();
    SDL_Surface *getSurface();
};

#endif