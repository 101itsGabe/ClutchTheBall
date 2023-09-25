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
    ~PlayerManager();
    PlayerManager(int);

    // void addPlayer(Player );
    // void removePlayer(Player);
    void RenderPlayers(SDL_Renderer *, vector<Tile>*);
    vector<Player> &getPlayerList();
    //SDL_Surface& getSurface();
};

#endif