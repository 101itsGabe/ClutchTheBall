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
}

TileManager::~TileManager()
{
    delete tileList;
}

void TileManager::addTile(Tile &t)
{
    tileList->emplace_back(t);
}

vector<Tile> *TileManager::getTileList()
{
    return tileList;
}

void TileManager::renderTiles(SDL_Renderer *renderer, int windowWidth, int windowHeight){
    
  for(Tile& t: *tileList){
    int tileSize = std::min(windowWidth, windowHeight) / 11;
    int gridWidth = 15 * tileSize; // Total width of the grid
    int gridHeight = 9 * tileSize; // Total height of the grid

    int middleX = (windowWidth - gridWidth) / 2;   // X-coordinate of the top-left corner
    int middleY = (windowHeight - gridHeight) / 2; // Y-coordinate of the top-left corner

    int tileX = t.getX() * tileSize + middleX;
    int tileY = t.getY() * tileSize + middleY;
    // This is going to calc where the exact tile will go on screen
    // This might have to be just the pixels like 64 or something
    t.setCoords(tileX, tileY, tileSize, tileSize); // Set the color for the Tile
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect tileRect = {tileX, tileY, tileSize, tileSize};

    // Render the tile
    SDL_RenderFillRect(renderer, &tileRect);

    // Border Color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    SDL_Rect borderRect = {tileX, tileY, tileSize, tileSize};

    // Render the Border
    SDL_RenderDrawRect(renderer, &borderRect);

    
  }
}

