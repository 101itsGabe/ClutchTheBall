#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <SDL.h>
using namespace std;

struct TileData{
    int tileX;
    int tileY;
    int tileW;
    int tileH;
};

class Tile {
    private:
        int x; //for array
        int y; //for array
        int tileId;
        bool ifOccupied;
        string imgPath;
        SDL_Color tileColor;
        SDL_Surface* tileSurface;
        TileData data;
    public:

    Tile();
    Tile(int, int, int);
    const string getImagePath();
    int getX() const;
    int getY() const;
    SDL_Color getColor();
    SDL_Surface* getTileSurface();
    TileData getTileData();
    bool isOccupied() const;
    int getTileId();

    void setOccupied(bool);
    void setCoords(int,int,int,int);
    void setColor(SDL_Color);
    void setTileSurface(SDL_Surface*);
    
    //Check position
    bool getMouseCheck(int,int);

    
};

#endif