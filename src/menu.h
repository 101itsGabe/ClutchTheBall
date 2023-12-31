#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include "SDL_ttf.h"
#include "SDL.h"
#include <player.h>
#include <tile.h>

using namespace std;

struct MenuData
{
    int menuX;
    int menuY;
    int menuW;
    int menuH;
};

struct TextData
{
    string name;
    int menuX;
    int menuY;
    int menuW;
    int menuH;
};

class Menu
{
private:
    bool isMouse;
    MenuData menuData;
    vector<TextData> textData;
    vector<string> menuText;

public:
    Menu();
    Menu(int, int);

    string mouseCheck(int, int);
    MenuData getMenuData();
    vector<TextData> &getTextData();

    void RenderText(SDL_Renderer *, TTF_Font *);
    void RenderMenu(SDL_Renderer *, TTF_Font *);
    void setData(Player *, vector<Tile> *, int);
    void setText(vector<string>);
};
#endif
