#ifndef TILEMANAGER_H
#define TILEMANAGER_H

#include "tile.h"
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>


class TileManager{
    private:
        vector<Tile>* tileList;
        int tileLen;

    public:
        TileManager();
        ~TileManager();
        void addTile(Tile&);
        void removeTile(Tile*);
        void renderTiles(SDL_Renderer *renderer, int windowWidth, int windowHeight);

        vector<Tile>* getTileList();


};

#endif