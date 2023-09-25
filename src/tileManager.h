#ifndef TILEMANAGER_H
#define TILEMANAGER_H

#include "tile.h"
#include <vector>


class TileManager{
    private:
        vector<Tile>* tileList;
        int tileLen;

    public:
        TileManager();
        ~TileManager();
        void addTile(Tile&);
        void removeTile(Tile*);

        vector<Tile>* getTileList();


};

#endif