#include "tile.h"
#include <iostream>


using namespace std;


Tile::Tile(){
    tileColor={255,255,255,255};
}

Tile::Tile(int row, int col, int id)
{
    x = row;
    y = col;
    tileId = id;
}

string const Tile::getImagePath(){
    return imgPath;
}

int Tile::getTileId(){
    return tileId;
}

int Tile::getX() const{
    return x;
}


int Tile::getY() const {
    return y;
}



void Tile::setCoords(int posX, int posY, int w, int h){
    data.tileX = posX;
    data.tileY = posY;
    data.tileW = w;
    data.tileH = h;
}

//Check if Mouse is inside tile x and y
//adding X and width to get the exact spot
bool Tile::getMouseCheck(int mX, int mY){
    //cout << "inside GetMouseCheck dataTileX: " << data.tileX << endl;
    //cout << "inside GetMouseCheck mX: " << mX << endl;

    if(data.tileX < mX && data.tileY < mY && (data.tileW + data.tileX) > mX && (data.tileH + data.tileY) > mY)
        return true;
    else
        return false;
}

//Set SDL_Color
void Tile::setColor(SDL_Color c){
    tileColor = c;
}

SDL_Color Tile::getColor(){
    return tileColor;
}

TileData Tile::getTileData(){
    return data;
}


bool Tile::isOccupied() const{
    return ifOccupied;
}

void Tile::setOccupied(bool i){
    ifOccupied = i;
}

SDL_Surface* Tile::getTileSurface(){
    return tileSurface;
}

void Tile::setTileSurface(SDL_Surface* ts){
    tileSurface = ts;
}