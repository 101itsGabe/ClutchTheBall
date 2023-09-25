#include <iostream>
#include <vector>
#include "tileManager.h"
#include "tile.h"


TileManager::TileManager()
{
    tileList = new vector<Tile>;
    int r = 15;
    int c = 9;
    for (int col = 0; col < c; ++col)
    {
        for (int row = 0; row < r; ++row)
        {
            tileList->emplace_back(row, col, tileList->size());
        }
    }
    cout << "Done Placing" << endl;
}

TileManager::~TileManager(){
    delete tileList;
}

void TileManager::addTile(Tile &t)
{
    tileList->emplace_back(t);
}

vector<Tile>* TileManager::getTileList(){
    return tileList;
}
