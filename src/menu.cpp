#include "menu.h"
#include "SDL.h"
#include <iostream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

Menu::Menu() {}

Menu::Menu(int windowWidth, int windowHeight)
{
    menuData.menuX = windowWidth / 2.5;
    menuData.menuY = windowHeight / 6;
    menuData.menuW = windowWidth * 0.25;
    menuData.menuH = windowHeight * 0.40;
}

string Menu::mouseCheck(int mX, int mY)
{
    for (TextData &md : textData)
    {
        if (md.menuX < mX && md.menuY < mY && (md.menuW + md.menuX) > mX && (md.menuH + md.menuY) > mY)
        {
            return md.name;
        }
    }
    return "";
}

MenuData Menu::getMenuData()
{
    return menuData;
}

void Menu::RenderText(SDL_Renderer *renderer, TTF_Font *font)
{
    //vector<string> textList = {"Shoot", "Move", "Pass"};
    int numItems = menuText.size();
    int offsetConst = (menuData.menuH * 0.4) / numItems;
    SDL_Color color = {0, 0, 0};
    for (string &text : menuText)
    {
        if (font != NULL)
        {
            SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
            if (textSurface != NULL)
            {
                SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                if (textTexture != NULL)
                {
                    SDL_Rect textRect;
                    if (menuText[0] == text)
                        textRect = {menuData.menuX, menuData.menuY, menuData.menuW / 2, (int)((menuData.menuH / 2) / menuText.size())};
                    else
                        textRect = {menuData.menuX, menuData.menuY + offsetConst, menuData.menuW / 2, (int)((menuData.menuH / 2) / menuText.size())};
                    
                    TextData curText = {text, textRect.x, textRect.y, textRect.w, textRect.h};
                    textData.emplace_back(curText);
                    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
                    const char *rendererError = SDL_GetError();
                    if (strlen(rendererError) > 0)
                    {
                        cout << SDL_GetError() << endl;
                    }
                    SDL_FreeSurface(textSurface);
                    SDL_DestroyTexture(textTexture);
                    offsetConst += offsetConst;
                }
            }
        }
    }

}

vector<TextData> &Menu::getTextData()
{
    return textData;
}

void Menu::setData(Player *p, vector<Tile> *tList, int windowWidth)
{
    int pTile = p->GetTile();
    Tile curTile;
    for (Tile &t : *tList)
    {
        if (t.getTileId() == pTile)
        {
            curTile = t;
            break;
        }
    }

    if (curTile.getTileData().tileX > windowWidth / 2)
        menuData.menuX = windowWidth / 4;
    else
        menuData.menuX = windowWidth / 1.5;
}

void Menu::setText(vector<string> tlist){
        for(string& s: tlist){
            menuText.emplace_back(s);
        }
}